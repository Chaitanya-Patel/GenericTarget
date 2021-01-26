% Make sure you have installed the SimpleDoc MATLAB package.
% https://github.com/RobertDamerius/SimpleDoc

% Set title and directories
title           = 'Generic Target';
inputDirectory  = 'text';
outputDirectory = 'html';

% Use a custom navigation bar layout
layoutNavBar = [
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.none);
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Overview', 'index.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.none);
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.text, 'GETTING STARTED');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Install Generic Target Toolbox', 'installtoolbox.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Prepare Target Computer', 'preparetarget.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Create and Deploy a Model', 'createanddeploy.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.none);
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.text, 'HOW THE APPLICATION WORKS');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Application Overview', 'application.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'UDP Object Manager', 'udpobjectmanager.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Multicast UDP Object Manager', 'multicastudpobjectmanager.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Signal Manager', 'signalmanager.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.none);
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Text Log', 'textlog.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Autogenerated Interface Class', 'simulinkinterface.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Thread Overview', 'threads.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Timing & Scheduling', 'timingscheduling.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.none);
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.text, 'HOW THE DEPLOYMENT WORKS');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Overview', 'buildoverview.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Deployment Process', 'buildanddeploy.html');
    SimpleDoc.NavEntry(SimpleDoc.NavEntryType.link, 'Target Software Directory', 'framework.html');
];

% Generate HTML documentation
SimpleDoc.Make(title, inputDirectory, outputDirectory, layoutNavBar, false);

% View documentation in MATLAB browser
open([outputDirectory filesep 'index.html']);
