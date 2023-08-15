/**
 * SFunctionGTDriverUDPMulticastReceive.cpp
 *
 *    ABSTRACT:
 *      The purpose of this sfunction is to call a simple legacy
 *      function during simulation:
 *
 *         void GT_DriverUDPMulticastReceiveStep(uint16 p1, uint32 p4, uint32 p8, uint16 y1[5*p8], uint8 y2[p4*p8], uint32 y3[p8], double y4[p8], uint32 y5[1], uint32 y6[1], int32 y7[1])
 *
 *    Simulink version           : 10.6 (R2022b) 13-May-2022
 *    C++ source code generated on : 15-Aug-2023 09:46:54
 *
 * THIS S-FUNCTION IS GENERATED BY THE LEGACY CODE TOOL AND MAY NOT WORK IF MODIFIED
 */

/**
     %%%-MATLAB_Construction_Commands_Start
     def = legacy_code('initialize');
     def.SFunctionName = 'SFunctionGTDriverUDPMulticastReceive';
     def.OutputFcnSpec = 'void GT_DriverUDPMulticastReceiveStep(uint16 p1, uint32 p4, uint32 p8, uint16 y1[5*p8], uint8 y2[p4*p8], uint32 y3[p8], double y4[p8], uint32 y5[1], uint32 y6[1], int32 y7[1])';
     def.StartFcnSpec = 'void GT_DriverUDPMulticastReceiveInitialize(uint16 p1, uint8 p2[4], uint8 p3[4], uint32 p4, int32 p5, int32 p6, uint8 p7, uint32 p8, uint32 p9, uint8 p10[4], uint8 p11)';
     def.TerminateFcnSpec = 'void GT_DriverUDPMulticastReceiveTerminate()';
     def.HeaderFiles = {'GT_DriverUDPMulticastReceive.hpp'};
     def.SourceFiles = {'GT_DriverUDPMulticastReceive.cpp', 'GT_SimulinkSupport.cpp'};
     def.SampleTime = 'parameterized';
     def.Options.useTlcWithAccel = false;
     def.Options.language = 'C++';
     legacy_code('sfcn_cmex_generate', def);
     legacy_code('compile', def);
     %%%-MATLAB_Construction_Commands_End
 */

/* Must specify the S_FUNCTION_NAME as the name of the S-function */
#define S_FUNCTION_NAME  SFunctionGTDriverUDPMulticastReceive
#define S_FUNCTION_LEVEL 2

/**
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"

/* Ensure that this S-Function is compiled with a C++ compiler */
#ifndef __cplusplus
#error This S-Function must be compiled with a C++ compiler. Enter mex('-setup') in the MATLAB Command Window to configure a C++ compiler.
#endif

/* Specific header file(s) required by the legacy code function */
#include "GT_DriverUDPMulticastReceive.hpp"

#define EDIT_OK(S, P_IDX) \
       (!((ssGetSimMode(S)==SS_SIMMODE_SIZES_CALL_ONLY) && mxIsEmpty(ssGetSFcnParam(S, P_IDX))))

#define SAMPLE_TIME (ssGetSFcnParam(S, 11))


/* Utility function prototypes */
static boolean_T IsRealMatrix(const mxArray *m);

#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)
/* Function: mdlCheckParameters ===========================================
 * Abstract:
 *   mdlCheckParameters verifies new parameter settings whenever parameter
 *   change or are re-evaluated during a simulation. When a simulation is
 *   running, changes to S-function parameters can occur at any time during
 *   the simulation loop.
 */
static void mdlCheckParameters(SimStruct *S)
{
    /* Check the parameter 1 */
    if (EDIT_OK(S, 0)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 0, "P1", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 2 */
    if (EDIT_OK(S, 1)) {
        int_T dimsArray[2];
        dimsArray[0] = (int_T)mxGetDimensions(ssGetSFcnParam(S, 1))[0];
        dimsArray[1] = (int_T)mxGetDimensions(ssGetSFcnParam(S, 1))[1];

        /* Parameter 2 must be a vector */
        if ((dimsArray[0] > 1) && (dimsArray[1] > 1)) {
            ssSetErrorStatus(S,"Parameter 2 must be a vector");
            return;
        } /* if */

        /* Parameter 2 must have 4 elements */
        if (((int_T)mxGetNumberOfElements(ssGetSFcnParam(S, 1))) != 4) {
            ssSetErrorStatus(S,"Parameter 2 must have 4 elements");
            return;
        } /* if */

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 1, "P2", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 3 */
    if (EDIT_OK(S, 2)) {
        int_T dimsArray[2];
        dimsArray[0] = (int_T)mxGetDimensions(ssGetSFcnParam(S, 2))[0];
        dimsArray[1] = (int_T)mxGetDimensions(ssGetSFcnParam(S, 2))[1];

        /* Parameter 3 must be a vector */
        if ((dimsArray[0] > 1) && (dimsArray[1] > 1)) {
            ssSetErrorStatus(S,"Parameter 3 must be a vector");
            return;
        } /* if */

        /* Parameter 3 must have 4 elements */
        if (((int_T)mxGetNumberOfElements(ssGetSFcnParam(S, 2))) != 4) {
            ssSetErrorStatus(S,"Parameter 3 must have 4 elements");
            return;
        } /* if */

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 2, "P3", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 4 */
    if (EDIT_OK(S, 3)) {
        int_T dimsArray[2] = {1, 1};

        /* Parameter 4 must be numeric */
        if (!mxIsNumeric(ssGetSFcnParam(S, 3))) {
            ssSetErrorStatus(S,"Parameter 4 must be numeric");
            return;
        } /* if */

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 3, "P4", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 5 */
    if (EDIT_OK(S, 4)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 4, "P5", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 6 */
    if (EDIT_OK(S, 5)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 5, "P6", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 7 */
    if (EDIT_OK(S, 6)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 6, "P7", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 8 */
    if (EDIT_OK(S, 7)) {
        int_T dimsArray[2] = {1, 1};

        /* Parameter 8 must be numeric */
        if (!mxIsNumeric(ssGetSFcnParam(S, 7))) {
            ssSetErrorStatus(S,"Parameter 8 must be numeric");
            return;
        } /* if */

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 7, "P8", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 9 */
    if (EDIT_OK(S, 8)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 8, "P9", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 10 */
    if (EDIT_OK(S, 9)) {
        int_T dimsArray[2];
        dimsArray[0] = (int_T)mxGetDimensions(ssGetSFcnParam(S, 9))[0];
        dimsArray[1] = (int_T)mxGetDimensions(ssGetSFcnParam(S, 9))[1];

        /* Parameter 10 must be a vector */
        if ((dimsArray[0] > 1) && (dimsArray[1] > 1)) {
            ssSetErrorStatus(S,"Parameter 10 must be a vector");
            return;
        } /* if */

        /* Parameter 10 must have 4 elements */
        if (((int_T)mxGetNumberOfElements(ssGetSFcnParam(S, 9))) != 4) {
            ssSetErrorStatus(S,"Parameter 10 must have 4 elements");
            return;
        } /* if */

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 9, "P10", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 11 */
    if (EDIT_OK(S, 10)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 10, "P11", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 12 (sample time) */
    if (EDIT_OK(S, 11)) {
        real_T  *sampleTime = NULL;
        size_t  stArraySize = mxGetM(SAMPLE_TIME) * mxGetN(SAMPLE_TIME);

        /* Sample time must be a real scalar value or 2 element array */
        if (IsRealMatrix(SAMPLE_TIME) && (stArraySize == 1 || stArraySize == 2)) {
            sampleTime = (real_T *) mxGetPr(SAMPLE_TIME);
        } else {
            ssSetErrorStatus(S, "Invalid sample time. Sample time must be a real scalar value or an array of two real values.");
            return;
        } /* if */

        if (sampleTime[0] < 0.0 && sampleTime[0] != -1.0) {
            ssSetErrorStatus(S, "Invalid sample time. Period must be non-negative or -1 (for inherited).");
            return;
        } /* if */

        if (stArraySize == 2 && sampleTime[0] > 0.0 && sampleTime[1] >= sampleTime[0]) {
            ssSetErrorStatus(S, "Invalid sample time. Offset must be smaller than period.");
            return;
        } /* if */

        if (stArraySize == 2 && sampleTime[0] == -1.0 && sampleTime[1] != 0.0) {
            ssSetErrorStatus(S, "Invalid sample time. When period is -1, offset must be 0.");
            return;
        } /* if */

        if (stArraySize == 2 && sampleTime[0] == 0.0 && !(sampleTime[1] == 1.0)) {
            ssSetErrorStatus(S, "Invalid sample time. When period is 0, offset must be 1.");
            return;
        } /* if */
    } /* if */

}
#endif

#define MDL_PROCESS_PARAMETERS
#if defined(MDL_PROCESS_PARAMETERS) && defined(MATLAB_MEX_FILE)
/* Function: mdlProcessParameters =========================================
 * Abstract:
 *   Update run-time parameters.
 */
static void mdlProcessParameters(SimStruct *S)
{
    ssUpdateAllTunableParamsAsRunTimeParams(S);
}
#endif

/* Function: mdlInitializeSizes ===========================================
 * Abstract:
 *   The sizes information is used by Simulink to determine the S-function
 *   block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
    /* Number of expected parameters */
    ssSetNumSFcnParams(S, 12);

    #if defined(MATLAB_MEX_FILE) 
    if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {
        /**
         * If the number of expected input parameters is not equal
         * to the number of parameters entered in the dialog box return.
         * Simulink will generate an error indicating that there is a
         * parameter mismatch.
         */
        mdlCheckParameters(S);
        if (ssGetErrorStatus(S) != NULL) return;
    } else {
        /* Return if number of expected != number of actual parameters */
        return;
    } /* if */
    #endif 

    /* Set the parameter's tunability */
    ssSetSFcnParamTunable(S, 0, 1);
    ssSetSFcnParamTunable(S, 1, 1);
    ssSetSFcnParamTunable(S, 2, 1);
    ssSetSFcnParamTunable(S, 3, 0);
    ssSetSFcnParamTunable(S, 4, 1);
    ssSetSFcnParamTunable(S, 5, 1);
    ssSetSFcnParamTunable(S, 6, 1);
    ssSetSFcnParamTunable(S, 7, 0);
    ssSetSFcnParamTunable(S, 8, 1);
    ssSetSFcnParamTunable(S, 9, 1);
    ssSetSFcnParamTunable(S, 10, 1);
    ssSetSFcnParamTunable(S, 11, 0);

    /* Set the number of work vectors */
    if (!ssSetNumDWork(S, 0)) return;
    ssSetNumPWork(S, 0);

    /* Set the number of input ports */
    if (!ssSetNumInputPorts(S, 0)) return;

    /* Set the number of output ports */
    if (!ssSetNumOutputPorts(S, 7)) return;

    /* Configure the output port 1 */
    ssSetOutputPortDataType(S, 0, SS_UINT16);
    {
        int_T y1Width = 5*(int_T)mxGetScalar(ssGetSFcnParam(S, 7));
        if (y1Width!=DYNAMICALLY_SIZED && y1Width < 1) { ssSetErrorStatus(S, "Output 1: the current width is < 1"); return; }
        ssSetOutputPortWidth(S, 0, y1Width);
    }
    ssSetOutputPortComplexSignal(S, 0, COMPLEX_NO);
    ssSetOutputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
    ssSetOutputPortOutputExprInRTW(S, 0, 0);
    ssSetOutputPortDimensionsMode(S, 0, FIXED_DIMS_MODE);

    /* Configure the output port 2 */
    ssSetOutputPortDataType(S, 1, SS_UINT8);
    {
        int_T y2Width = (int_T)mxGetScalar(ssGetSFcnParam(S, 3))*(int_T)mxGetScalar(ssGetSFcnParam(S, 7));
        if (y2Width!=DYNAMICALLY_SIZED && y2Width < 1) { ssSetErrorStatus(S, "Output 2: the current width is < 1"); return; }
        ssSetOutputPortWidth(S, 1, y2Width);
    }
    ssSetOutputPortComplexSignal(S, 1, COMPLEX_NO);
    ssSetOutputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
    ssSetOutputPortOutputExprInRTW(S, 1, 0);
    ssSetOutputPortDimensionsMode(S, 1, FIXED_DIMS_MODE);

    /* Configure the output port 3 */
    ssSetOutputPortDataType(S, 2, SS_UINT32);
    {
        int_T y3Width = (int_T)mxGetScalar(ssGetSFcnParam(S, 7));
        if (y3Width!=DYNAMICALLY_SIZED && y3Width < 1) { ssSetErrorStatus(S, "Output 3: the current width is < 1"); return; }
        ssSetOutputPortWidth(S, 2, y3Width);
    }
    ssSetOutputPortComplexSignal(S, 2, COMPLEX_NO);
    ssSetOutputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
    ssSetOutputPortOutputExprInRTW(S, 2, 0);
    ssSetOutputPortDimensionsMode(S, 2, FIXED_DIMS_MODE);

    /* Configure the output port 4 */
    ssSetOutputPortDataType(S, 3, SS_DOUBLE);
    {
        int_T y4Width = (int_T)mxGetScalar(ssGetSFcnParam(S, 7));
        if (y4Width!=DYNAMICALLY_SIZED && y4Width < 1) { ssSetErrorStatus(S, "Output 4: the current width is < 1"); return; }
        ssSetOutputPortWidth(S, 3, y4Width);
    }
    ssSetOutputPortComplexSignal(S, 3, COMPLEX_NO);
    ssSetOutputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
    ssSetOutputPortOutputExprInRTW(S, 3, 0);
    ssSetOutputPortDimensionsMode(S, 3, FIXED_DIMS_MODE);

    /* Configure the output port 5 */
    ssSetOutputPortDataType(S, 4, SS_UINT32);
    {
        int_T y5Width = 1;
        ssSetOutputPortWidth(S, 4, y5Width);
    }
    ssSetOutputPortComplexSignal(S, 4, COMPLEX_NO);
    ssSetOutputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
    ssSetOutputPortOutputExprInRTW(S, 4, 0);
    ssSetOutputPortDimensionsMode(S, 4, FIXED_DIMS_MODE);

    /* Configure the output port 6 */
    ssSetOutputPortDataType(S, 5, SS_UINT32);
    {
        int_T y6Width = 1;
        ssSetOutputPortWidth(S, 5, y6Width);
    }
    ssSetOutputPortComplexSignal(S, 5, COMPLEX_NO);
    ssSetOutputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
    ssSetOutputPortOutputExprInRTW(S, 5, 0);
    ssSetOutputPortDimensionsMode(S, 5, FIXED_DIMS_MODE);

    /* Configure the output port 7 */
    ssSetOutputPortDataType(S, 6, SS_INT32);
    {
        int_T y7Width = 1;
        ssSetOutputPortWidth(S, 6, y7Width);
    }
    ssSetOutputPortComplexSignal(S, 6, COMPLEX_NO);
    ssSetOutputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
    ssSetOutputPortOutputExprInRTW(S, 6, 0);
    ssSetOutputPortDimensionsMode(S, 6, FIXED_DIMS_MODE);

    /* Register reserved identifiers to avoid name conflict */
    if (ssRTWGenIsCodeGen(S) || ssGetSimMode(S)==SS_SIMMODE_EXTERNAL) {

        /* Register reserved identifier for  */
        ssRegMdlInfo(S, "GT_DriverUDPMulticastReceiveInitialize", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));

        /* Register reserved identifier for  */
        ssRegMdlInfo(S, "GT_DriverUDPMulticastReceiveStep", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));

        /* Register reserved identifier for  */
        ssRegMdlInfo(S, "GT_DriverUDPMulticastReceiveTerminate", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));

        /* Register reserved identifier for wrappers */
        if (ssRTWGenIsModelReferenceSimTarget(S)) {

            /* Register reserved identifier for  */
            ssRegMdlInfo(S, "GT_DriverUDPMulticastReceiveInitialize_wrapper_Start", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));

            /* Register reserved identifier for  */
            ssRegMdlInfo(S, "GT_DriverUDPMulticastReceiveStep_wrapper_Output", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));

            /* Register reserved identifier for  */
            ssRegMdlInfo(S, "GT_DriverUDPMulticastReceiveTerminate_wrapper_Terminate", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));
        } /* if */
    } /* if */

    /* This S-function can be used in referenced model simulating in normal mode */
    ssSetModelReferenceNormalModeSupport(S, MDL_START_AND_MDL_PROCESS_PARAMS_OK);

    /* Set the number of sample time */
    ssSetNumSampleTimes(S, 1);

    /* Set the compliance for the operating point save/restore. */
    ssSetOperatingPointCompliance(S, USE_DEFAULT_OPERATING_POINT);

    ssSetArrayLayoutForCodeGen(S, SS_ALL);

    /* Set the Simulink version this S-Function has been generated in */
    ssSetSimulinkVersionGeneratedIn(S, "10.6");

    /**
     * All options have the form SS_OPTION_<name> and are documented in
     * matlabroot/simulink/include/simstruc.h. The options should be
     * bitwise or'd together as in
     *    ssSetOptions(S, (SS_OPTION_name1 | SS_OPTION_name2))
     */
    ssSetOptions(S,
        SS_OPTION_CAN_BE_CALLED_CONDITIONALLY |
        SS_OPTION_EXCEPTION_FREE_CODE |
        SS_OPTION_WORKS_WITH_CODE_REUSE |
        SS_OPTION_SFUNCTION_INLINED_FOR_RTW |
        SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME
    );
}

/* Function: mdlInitializeSampleTimes =====================================
 * Abstract:
 *   This function is used to specify the sample time(s) for your
 *   S-function. You must register the same number of sample times as
 *   specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    real_T * sampleTime = (real_T*) (mxGetPr(SAMPLE_TIME));
    size_t  stArraySize = mxGetM(SAMPLE_TIME) * mxGetN(SAMPLE_TIME);

    ssSetSampleTime(S, 0, sampleTime[0]);
    if (stArraySize == 1) {
        ssSetOffsetTime(S, 0, (sampleTime[0] == CONTINUOUS_SAMPLE_TIME ? FIXED_IN_MINOR_STEP_OFFSET: 0.0));
    } else {
        ssSetOffsetTime(S, 0, sampleTime[1]);
    } /* if */

    #if defined(ssSetModelReferenceSampleTimeDefaultInheritance)
    ssSetModelReferenceSampleTimeDefaultInheritance(S);
    #endif
}

#define MDL_SET_WORK_WIDTHS
#if defined(MDL_SET_WORK_WIDTHS) && defined(MATLAB_MEX_FILE)
/* Function: mdlSetWorkWidths =============================================
 * Abstract:
 *   The optional method, mdlSetWorkWidths is called after input port
 *   width, output port width, and sample times of the S-function have
 *   been determined to set any state and work vector sizes which are
 *   a function of the input, output, and/or sample times. 
 *   Run-time parameters are registered in this method using methods 
 *   ssSetNumRunTimeParams, ssSetRunTimeParamInfo, and related methods.
 */
static void mdlSetWorkWidths(SimStruct *S)
{
    /* Set number of run-time parameters */
    if (!ssSetNumRunTimeParams(S, 11)) return;

    /* Register the run-time parameter 1 */
    ssRegDlgParamAsRunTimeParam(S, 0, 0, "p1", ssGetDataTypeId(S, "uint16"));

    /* Register the run-time parameter 2 */
    ssRegDlgParamAsRunTimeParam(S, 1, 1, "p2", ssGetDataTypeId(S, "uint8"));

    /* Register the run-time parameter 3 */
    ssRegDlgParamAsRunTimeParam(S, 2, 2, "p3", ssGetDataTypeId(S, "uint8"));

    /* Register the run-time parameter 4 */
    ssRegDlgParamAsRunTimeParam(S, 3, 3, "p4", ssGetDataTypeId(S, "uint32"));

    /* Register the run-time parameter 5 */
    ssRegDlgParamAsRunTimeParam(S, 4, 4, "p5", ssGetDataTypeId(S, "int32"));

    /* Register the run-time parameter 6 */
    ssRegDlgParamAsRunTimeParam(S, 5, 5, "p6", ssGetDataTypeId(S, "int32"));

    /* Register the run-time parameter 7 */
    ssRegDlgParamAsRunTimeParam(S, 6, 6, "p7", ssGetDataTypeId(S, "uint8"));

    /* Register the run-time parameter 8 */
    ssRegDlgParamAsRunTimeParam(S, 7, 7, "p8", ssGetDataTypeId(S, "uint32"));

    /* Register the run-time parameter 9 */
    ssRegDlgParamAsRunTimeParam(S, 8, 8, "p9", ssGetDataTypeId(S, "uint32"));

    /* Register the run-time parameter 10 */
    ssRegDlgParamAsRunTimeParam(S, 9, 9, "p10", ssGetDataTypeId(S, "uint8"));

    /* Register the run-time parameter 11 */
    ssRegDlgParamAsRunTimeParam(S, 10, 10, "p11", ssGetDataTypeId(S, "uint8"));
}
#endif

#define MDL_START
#if defined(MDL_START)
/* Function: mdlStart =====================================================
 * Abstract:
 *   This function is called once at start of model execution. If you
 *   have states that should be initialized once, this is the place
 *   to do it.
 */
static void mdlStart(SimStruct *S)
{

    /* Get access to Parameter/Input/Output/DWork data */
    uint16_T* p1 = (uint16_T*) ssGetRunTimeParamInfo(S, 0)->data;
    uint8_T* p2 = (uint8_T*) ssGetRunTimeParamInfo(S, 1)->data;
    uint8_T* p3 = (uint8_T*) ssGetRunTimeParamInfo(S, 2)->data;
    uint32_T* p4 = (uint32_T*) ssGetRunTimeParamInfo(S, 3)->data;
    int32_T* p5 = (int32_T*) ssGetRunTimeParamInfo(S, 4)->data;
    int32_T* p6 = (int32_T*) ssGetRunTimeParamInfo(S, 5)->data;
    uint8_T* p7 = (uint8_T*) ssGetRunTimeParamInfo(S, 6)->data;
    uint32_T* p8 = (uint32_T*) ssGetRunTimeParamInfo(S, 7)->data;
    uint32_T* p9 = (uint32_T*) ssGetRunTimeParamInfo(S, 8)->data;
    uint8_T* p10 = (uint8_T*) ssGetRunTimeParamInfo(S, 9)->data;
    uint8_T* p11 = (uint8_T*) ssGetRunTimeParamInfo(S, 10)->data;


    /* Call the legacy code function */
    GT_DriverUDPMulticastReceiveInitialize(*p1, p2, p3, *p4, *p5, *p6, *p7, *p8, *p9, p10, *p11);
}
#endif

/* Function: mdlOutputs ===================================================
 * Abstract:
 *   In this function, you compute the outputs of your S-function
 *   block. Generally outputs are placed in the output vector(s),
 *   ssGetOutputPortSignal.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{

    /* Get access to Parameter/Input/Output/DWork data */
    uint16_T* p1 = (uint16_T*) ssGetRunTimeParamInfo(S, 0)->data;
    uint32_T* p4 = (uint32_T*) ssGetRunTimeParamInfo(S, 3)->data;
    uint32_T* p8 = (uint32_T*) ssGetRunTimeParamInfo(S, 7)->data;
    uint16_T* y1 = (uint16_T*) ssGetOutputPortSignal(S, 0);
    uint8_T* y2 = (uint8_T*) ssGetOutputPortSignal(S, 1);
    uint32_T* y3 = (uint32_T*) ssGetOutputPortSignal(S, 2);
    real_T* y4 = (real_T*) ssGetOutputPortSignal(S, 3);
    uint32_T* y5 = (uint32_T*) ssGetOutputPortSignal(S, 4);
    uint32_T* y6 = (uint32_T*) ssGetOutputPortSignal(S, 5);
    int32_T* y7 = (int32_T*) ssGetOutputPortSignal(S, 6);


    /* Call the legacy code function */
    GT_DriverUDPMulticastReceiveStep(*p1, *p4, *p8, y1, y2, y3, y4, y5, y6, y7);
}

/* Function: mdlTerminate =================================================
 * Abstract:
 *   In this function, you should perform any actions that are necessary
 *   at the termination of a simulation.
 */
static void mdlTerminate(SimStruct *S)
{

    /* Call the legacy code function */
    GT_DriverUDPMulticastReceiveTerminate();
}

#define MDL_RTW
#if defined(MATLAB_MEX_FILE) && defined(MDL_RTW)
/* Function: mdlRTW =======================================================
 * Abstract:
 *   This function is called when Simulink Coder is generating
 *   the model.rtw file.
 */
static void mdlRTW(SimStruct *S)
{
}
#endif

/* Function: IsRealMatrix =================================================
 * Abstract:
 *   Verify that the mxArray is a real (double) finite matrix
 */
boolean_T IsRealMatrix(const mxArray *m)
{
    if (mxIsNumeric(m) && mxIsDouble(m) && !mxIsLogical(m) && !mxIsComplex(m) && !mxIsSparse(m) && !mxIsEmpty(m) && (mxGetNumberOfDimensions(m)==2)) {
        real_T *data = mxGetPr(m);
        size_t  numEl = mxGetNumberOfElements(m);
        size_t  i;

        for (i = 0; i < numEl; i++) {
            if (!mxIsFinite(data[i])) {
                return 0;
            } /* if */
        } /* for */

        return 1;
    } else {
        return 0;
    } /* if */
}

/* Required S-function trailer */
#ifdef    MATLAB_MEX_FILE
# include "simulink.c"
#else
# include "cg_sfun.h"
#endif

