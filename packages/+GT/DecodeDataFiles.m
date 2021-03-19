function data = DecodeDataFiles(dataFileNames)
    %GT.DecodeDataFiles Decode raw data file(s) recorded by the generic target application into a structure of timeseries.
    % 
    % PARAMETERS
    % dataFileNames ... A string or a cell array of strings indicating the raw data files that contains the data recorded by the generic target application for one ID, e.g. 'id0_0' or {'id0_0','id0_1'}.
    % 
    % RETURN
    % data ... The data structure containing timeseries for all recorded signals.
    % 
    % REVISION HISTORY
    % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    % Version     Author                 Changes
    % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    % 20210319    Robert Damerius        Initial release.
    % 
    % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    % Check for correct input
    if(ischar(dataFileNames))
        dataFileNames = {dataFileNames};
    end
    assert(iscell(dataFileNames) && ((1 == size(dataFileNames,1)) || (1 == size(dataFileNames,2))), 'GT.DecodeDataFiles(): Input "dataFileNames" must be a string or a cell array of strings!');
    for i = 1:length(dataFileNames)
        assert(ischar(dataFileNames{i}), 'GT.DecodeDataFiles(): Input "dataFileNames" must be a string or a cell array of strings!');
    end

    % Fallback output
    data = struct();
    if(isempty(dataFileNames))
        return;
    end

    % Decode/check all headers and make sure that all headers are equal
    tic();
    fprintf('[DECODE] Decoding and checking headers of all input files:\n');
    header = struct.empty();
    numBytesSampleData = uint64(0);
    for i = 1:length(dataFileNames)
        fprintf('         "%s"\n',dataFileNames{i});
        [success,h,chunkSizeSampleData] = DecodeHeader(dataFileNames{i});
        numBytesSampleData = numBytesSampleData + chunkSizeSampleData;
        if(~success)
            error(['Failed to decode target data file "' dataFileNames{i} '"!']);
        end
        if(isempty(header))
            header = h;
        else
            equal = strcmp(header.id, h.id);
            equal = equal & (header.offsetSampleData == h.offsetSampleData);
            equal = equal & (header.numSignals == h.numSignals);
            equal = equal & strcmp(header.labels, h.labels);
            equal = equal & (header.numBytesPerSample == h.numBytesPerSample);
            equal = equal & strcmp(header.dimensions, h.dimensions);
            equal = equal & strcmp(header.dataTypes, h.dataTypes);
            equal = equal & (header.bigEndian == h.bigEndian);
            if(~equal)
                error(['All target data files must have the same header, but header of file "' dataFileNames{i} '" is different than header of file "' dataFileNames{1} '"!']);
            end
        end
    end

    % Decoding header information
    fprintf('[DECODE] Decoding header information ... ');
    [success, signalNames, dimensions, dataTypes] = ConvertHeader(header);
    if(~success)
        error('Failed to read signal names, dimensions and/or dataTypes from header!');
    end
    fprintf('OK\n');

    % Endianess of this machine
    [~,~,tmp] = computer;
    thisBigEndian = ('B' == tmp);

    % Open all files and write all binary data to one byte stream
    fprintf('[DECODE] Allocating memory for binary sample data (%s bytes) ... ',num2str(numBytesSampleData));
    bytes = uint8(zeros(numBytesSampleData,1));
    fprintf('OK\n[DECODE] Reading binary sample data from all input files:\n');
    idx1 = uint64(1);
    for i = 1:length(dataFileNames)
        fprintf('         "%s"\n',dataFileNames{i});
        fp = fopen(dataFileNames{i},'r');
        fseek(fp, 0, 'eof');
        fileDataSize = uint64(ftell(fp));
        if(fileDataSize < uint64(header.offsetSampleData))
            error(['Invalid header of file "' dataFileNames{i} '"! Could not read sample data!']);
        end
        sampleDataSize = fileDataSize - uint64(header.offsetSampleData);
        fseek(fp, header.offsetSampleData, 'bof');
        bytes(idx1:idx1+sampleDataSize-uint64(1)) = uint8(fread(fp,sampleDataSize));
        fclose(fp);
        idx1 = idx1 + sampleDataSize;
    end

    % Check if size of read binary data is a multiple of the size of one sample data buffer
    numberOfSamples = uint64(floor(numBytesSampleData / (uint64(8) + uint64(header.numBytesPerSample))));
    if((numberOfSamples * (uint64(8) + uint64(header.numBytesPerSample))) ~= numBytesSampleData)
        warning('Incomplete sample data. The last sample my be missing.');
    end
    fprintf('[DECODE] Found %s samples!\n',num2str(numberOfSamples));

    % Decoding timestamps
    fprintf('[DECODE] Decoding timestamps ... ');
    timeVec = nan(numberOfSamples,1);
    idx1 = uint64(1);
    stride = uint64(8 + header.numBytesPerSample);
    for i = 1:numberOfSamples
        timeVec(i) = typecast(bytes(idx1:(idx1+uint64(7))), 'double');
        idx1 = idx1 + stride;
    end
    if(thisBigEndian ~= header.bigEndian)
        timeVec = swapbytes(timeVec);
    end
    fprintf('OK\n');

    % Decode sample data
    fprintf('[DECODE] Decoding signals ... 000 %%');
    offsetSignalData = uint64(9);
    prevProgress = int32(0);
    for k = 1:header.numSignals
        % Get dimension, name, type
        dim = uint64(dimensions{k});
        name = signalNames{k};
        type = dataTypes{k};
        if(strcmp(type,'boolean') || strcmp(type,'logical'))
            type = 'uint8';
        end

        % Show progress
        progress = int32(floor(100.0 * (double(k - 1) / double(header.numSignals))));
        if(progress ~= prevProgress)
            prevProgress = progress;
            fprintf('\b\b\b\b\b%03d %%',progress);
        end

        % Get strings for dimension creation and dimension assignment
        strDim = strrep(regexprep(num2str(dim),' +',' '),' ',',');
        strDimAssign = repmat(':,',[1 length(dim)]);

        % Create empty data vector (either scalar or multi-dimensional)
        if(1 == length(dim)) % scalar signal
            eval(['dataVals = ',type,'(zeros(',num2str(numberOfSamples),',1));']);
        else % multidimensional signal
            eval(['dataVals = ',type,'(zeros(',strDim,',',num2str(numberOfSamples),'));']);
        end

        % Decode this signal from all samples
        idx1 = offsetSignalData;
        sizeOfSignal = GetSizeOfSignal(dim,type);
        for i = 1:numberOfSamples
            v = typecast(bytes(idx1:(idx1 + sizeOfSignal - uint64(1))), type);
            if(length(dim) > 1) % multi-dimensional signal
                eval(['dataVals(',strDimAssign,'i) = reshape(v, dim);']);
            else % scalar signal
                dataVals(i) = v;
            end
            idx1 = idx1 + stride;
        end
        offsetSignalData = offsetSignalData + sizeOfSignal;

        % Check for correct endianess
        if(thisBigEndian ~= header.bigEndian)
            dataVals = swapbytes(dataVals);
        end

        % Put timeVec,dataVals into time series struct
        layerNames = split(name,'.');
        ts = timeseries(dataVals,timeVec,'Name',layerNames{end});
        eval(['data.',name,' = ts;']);
    end
    fprintf('\b\b\b\b\bOK\n[DECODE] Decoding finished after %f seconds\n\n',toc());
end

function [success,header,chunkSizeSampleData] = DecodeHeader(filename)
    % Set default output
    success = false;
    header.id = char.empty;
    header.offsetSampleData = uint32(0);
    header.numSignals = uint32(0);
    header.labels = '';
    header.numBytesPerSample = uint32(0);
    header.dimensions = '';
    header.dataTypes = '';
    header.bigEndian = false;
    chunkSizeSampleData = uint64(0);

    % Open file
    fp = fopen(filename,'r');
    if(fp < 0), return; end

    % Read header ID
    bytes = uint8(fread(fp,5));
    if(5 ~= length(bytes)), fclose(fp); return; end
    header.id = char(reshape(bytes,[1 5]));

    % Read sample data offset
    bytes = uint8(fread(fp,4));
    header.offsetSampleData = uint32(bitor(bitor(bitshift(uint32(bytes(1)),24),bitshift(uint32(bytes(2)),16)),bitor(bitshift(uint32(bytes(3)),8),uint32(bytes(4)))));

    % Read remaining header bytes and get chunk size of sample data
    if(header.offsetSampleData < uint32(9)), fclose(fp); return; end
    N = header.offsetSampleData - uint32(9);
    bytes = uint8(fread(fp,N));
    fseek(fp, 0, 'eof');
    chunkSizeSampleData = uint64(ftell(fp)) - uint64(header.offsetSampleData);
    fclose(fp);
    if(N ~= uint32(length(bytes))), return; end

    % Decode endianess indicator for sample data (end of header data)
    if(N < 5), return; end
    if((uint8(1) ~= bytes(end)) && (uint8(128) ~= bytes(end))), return; end
    header.bigEndian = (uint8(128) == bytes(end));

    % Decode header content depending on ID
    switch(header.id)
        case 'GTDBL'
            % Decode numSignals
            header.numSignals = uint32(bitor(bitor(bitshift(uint32(bytes(1)),24),bitshift(uint32(bytes(2)),16)),bitor(bitshift(uint32(bytes(3)),8),uint32(bytes(4)))));
            idx1 = int32(5);

            % Decode labels
            idxZeroTerminator = find(~bytes(idx1:end),1);
            if(isempty(idxZeroTerminator)), return; end
            L = int32(idxZeroTerminator) - int32(1);
            header.labels = char(reshape(bytes(idx1:(idx1 + L - int32(1))),[1 L]));

            % Generate other header fields
            header.numBytesPerSample = header.numSignals * uint32(8);
            header.dimensions = repmat('[1],',[1 header.numSignals]);
            header.dataTypes = repmat('double,',[1 header.numSignals]);
            if(header.numSignals)
                header.dimensions = header.dimensions(1:end-1);
                header.dataTypes = header.dataTypes(1:end-1);
            end
        case 'GTBUS'
            % Decode numBytesPerSample
            header.numBytesPerSample = uint32(bitor(bitor(bitshift(uint32(bytes(1)),24),bitshift(uint32(bytes(2)),16)),bitor(bitshift(uint32(bytes(3)),8),uint32(bytes(4)))));
            idx1 = int32(5);

            % Decode labels
            idxZeroTerminator = find(~bytes(idx1:end),1);
            if(isempty(idxZeroTerminator)), return; end
            L = int32(idxZeroTerminator) - int32(1);
            header.labels = char(reshape(bytes(idx1:(idx1 + L - int32(1))),[1 L]));
            idx1 = idx1 + L + int32(1);

            % Decode dimensions
            idxZeroTerminator = find(~bytes(idx1:end),1);
            if(isempty(idxZeroTerminator)), return; end
            L = int32(idxZeroTerminator) - int32(1);
            header.dimensions = char(reshape(bytes(idx1:(idx1 + L - int32(1))),[1 L]));
            idx1 = idx1 + L + int32(1);

            % Decode dataTypes
            idxZeroTerminator = find(~bytes(idx1:end),1);
            if(isempty(idxZeroTerminator)), return; end
            L = int32(idxZeroTerminator) - int32(1);
            header.dataTypes = char(reshape(bytes(idx1:(idx1 + L - int32(1))),[1 L]));

            % Generate other header fields
            header.numSignals = uint32(count(header.dataTypes,',') + 1);
        otherwise
            return;
    end
    success = true;
end

function [success, signalNames, dimensions, dataTypes] = ConvertHeader(header)
    success = true;
    signalNames = split(header.labels,',');
    strDimensions = strrep(header.dimensions,'[','');
    strDimensions = strrep(strDimensions,']','');
    strDimensions = split(strDimensions,',');
    dimensions = cellfun(@str2num,strDimensions,'UniformOutput',false);
    for i = 1:length(dimensions)
        if(1 == length(dimensions{i}))
            if(dimensions{i} > 1)
                dimensions{i} = [dimensions{i},1];
            end
        end
        if(1 == prod(dimensions{i}))
            dimensions{i} = 1;
        end
    end
    dimensions = reshape(dimensions,[1 length(dimensions)]);
    dataTypes = split(header.dataTypes,',');
    if((length(signalNames) ~= length(dimensions)) || (length(signalNames) ~= length(dataTypes)) || (length(signalNames) ~= header.numSignals))
        success = false;
    end
end

function result = GetSizeOfSignal(dim,type)
    result = uint64(0);
    numValues = uint64(prod(dim));
    switch(type)
        case {'boolean','logical','uint8','int8'}
            result = numValues;
        case {'uint16','int16'}
            result = numValues * uint64(2);
        case {'uint32','int32','single'}
            result = numValues * uint64(4);
        case {'uint64','int64','double'}
            result = numValues * uint64(8);
    end
end

