// debug
#include <intrin.h>

#include <stdio.h>
#include <iostream>
#include <map>

//glorious hack
#include "rhd2000evalboard.cpp"
#include "rhd2000registers.cpp"
#include "rhd2000datablock.cpp"
#include "okFrontPanelDLL.cpp"

#include "rhd2000evalboard.h"
#include "rhd2000registers.h"
#include "rhd2000datablock.h"
#include "okFrontPanelDLL.h"

#include "mex.h"

//define all the funciton names, we are NOT going to try a map because UGLY

//dev = new okCFrontPanel; //this is really where the deal is at...

typedef unsigned long int uint64_t;
typedef long int int64_t;
typedef short int int16_t;

//map for handling sample rates
std::map<std::string, Rhd2000EvalBoard::AmplifierSampleRate> SampleRateMap = {
    {"SampleRate1000Hz" , Rhd2000EvalBoard::SampleRate1000Hz},
    {"SampleRate1250Hz" , Rhd2000EvalBoard::SampleRate1250Hz},
    {"SampleRate1500Hz" , Rhd2000EvalBoard::SampleRate1500Hz},
    {"SampleRate2000Hz" , Rhd2000EvalBoard::SampleRate2000Hz},
    {"SampleRate2500Hz" , Rhd2000EvalBoard::SampleRate2500Hz},
    {"SampleRate3000Hz" , Rhd2000EvalBoard::SampleRate3000Hz},
    {"SampleRate3333Hz" , Rhd2000EvalBoard::SampleRate3333Hz},
    {"SampleRate4000Hz" , Rhd2000EvalBoard::SampleRate4000Hz},
    {"SampleRate5000Hz" , Rhd2000EvalBoard::SampleRate5000Hz},
    {"SampleRate6250Hz" , Rhd2000EvalBoard::SampleRate6250Hz},
    {"SampleRate8000Hz" , Rhd2000EvalBoard::SampleRate8000Hz},
    {"SampleRate10000Hz" , Rhd2000EvalBoard::SampleRate10000Hz},
    {"SampleRate12500Hz" , Rhd2000EvalBoard::SampleRate12500Hz},
    {"SampleRate15000Hz" , Rhd2000EvalBoard::SampleRate15000Hz},
    {"SampleRate20000Hz" , Rhd2000EvalBoard::SampleRate20000Hz},
    {"SampleRate25000Hz" , Rhd2000EvalBoard::SampleRate25000Hz},
    {"SampleRate30000Hz" , Rhd2000EvalBoard::SampleRate30000Hz}
};

//function names
enum fNames {
    isRunning_e,
    getValue_e,
    setValue_e,
    create_e,
    init_e,
    delete_e,
    SampleRate_e,
    SamplesPerTrigger_e,
    TriggerRepeat_e,
    LogFileName_e
};

std::string isRunning_s = "isRunning";
std::string getValue_s = "getValue"; //deprecated
std::string setValue_s = "setValue";

std::string create_s = "create";
std::string init_s = "init";
std::string delete_s = "delete";

std::string SampleRate_s = "SampleRate";
std::string SamplesPerTrigger_s = "SamplesPerTrigger";
std::string TriggerRepeat_s = "TriggerRepeat";
std::string LogFileName_s = "LogFileName";

//map for function name switch
std::map<std::string, fNames> fNameMap = {
    {isRunning_s , isRunning_e },
    {getValue_s , getValue_e },
    {setValue_s , setValue_e },
    {create_s , create_e },
    {delete_s , delete_e },
    {SampleRate_s , SampleRate_e },
    {SamplesPerTrigger_s , SamplesPerTrigger_e },
    {TriggerRepeat_s , TriggerRepeat_e },
    {LogFileName_s , LogFileName_e },
};

//define the number of arguments each function expects
std::map<std::string, int> NumArgsMap = {
    {isRunning_s , 0},
    {getValue_s , 0},
    {setValue_s , 1},

    {create_s , 0},
    {init_s , 0},
    {delete_s , 0},

    {SampleRate_s , 1},
    {SamplesPerTrigger_s , 1},
    {TriggerRepeat_s , 1},
    {LogFileName_s , 1},
};


//utility functions
std::string indToStr(const mxArray *prhs[], int index){ //todo make this len safe?
    char *string_s = mxArrayToString(prhs[index]);
    std::string str(string_s); //FIXME for some reason mxFree failes on this?
    return string_s;
}

void inputHandler(int nrhs, const mxArray *prhs[]){
    // some day I will figure out the correct way to have this return a value
    // unfortunately the type of the return values might change...
    // but maybe I can create a return type for each input type?
}

Rhd2000EvalBoard *createObject(void){
    // setup and init the board when we create the intan class
    Rhd2000EvalBoard *evalBoard = new Rhd2000EvalBoard;

    // Open Opal Kelly XEM6010 board.
    //evalBoard->open();
/*
    // Load Rhythm FPGA configuration bitfile (provided by Intan Technologies).
    string bitfilename;
    bitfilename = "main.bit";  // Place main.bit in the executable directory, or add a complete path to file.
    evalBoard->uploadFpgaBitfile(bitfilename);

    // Initialize board.
    evalBoard->initialize();
    evalBoard->setDataSource(0, Rhd2000EvalBoard::PortA1);

    // Select per-channel amplifier sampling rate.
    evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate20000Hz);

    // Now that we have set our sampling rate, we can set the MISO sampling delay
    // which is dependent on the sample rate.  We assume a 3-foot cable.
    evalBoard->setCableLengthFeet(Rhd2000EvalBoard::PortA, 3.0);

    // Let's turn one LED on to indicate that the program is running.
    int ledArray[8] = {1, 0, 0, 0, 0, 0, 0, 0};
    evalBoard->setLedDisplay(ledArray);
*/
    return evalBoard;
}

int initBoard(Rhd2000EvalBoard *evalBoard){
    return evalBoard->open();
}

int deleteObject(Rhd2000EvalBoard *evalBoard){
    delete evalBoard; //FIXME this causes a full on matlab crash
    return 0;
}

Rhd2000EvalBoard *retrieveHandle(const mxArray *prhs[]){
    // get the cpp_handle using mxGetProperty
    //Rhd2000EvalBoard *cpp_handle;
    //cpp_handle = (Rhd2000EvalBoard *)mxGetProperty(prhs[0],0,"cpp_handle");
    //return cpp_handle;
    Rhd2000EvalBoard *pointer = (Rhd2000EvalBoard *)mxGetProperty(prhs[0],0,"cpp_handle"); //FIXME seems we may be loosing the device between rounds and that maybe we we need a handle to is the dll??
    //if (!pointer->isValid()){
        //mxErrMsgTxt("Pointer to evalBoard not valid")
    //}
    //else {
        //return pointer
    //}
    //__debugbreak();
    return pointer;
}

int setSampleRate(Rhd2000EvalBoard *evalBoard, const mxArray *prhs[]){
    //TODO make sure we get the values right
    char *sampleRate_c = mxArrayToString(prhs[3]); //3rd index has the string
    std::string sampleRate_s = sampleRate_c;
    bool out = evalBoard->setSampleRate(SampleRateMap[sampleRate_s]);
    mxFree(sampleRate_c); //TODO move all this type conversion stuff to an input handler
    if (out){
        return 0;
    }
    else {
        return -1;
    }
}

//function to make creating plhs based on type simpler

void *makeOutput(mxArray *plhs[], mxClassID classID){
    mwSize          ndim = 2;
    const mwSize    dims[] = {1,1}; //FIXME this is why we were having troubl writing 

    // welcome to scopes for local variables
    switch(classID){
        case mxUINT64_CLASS:{
            uint64_t *data;
            plhs[0] = mxCreateNumericArray(ndim, dims, classID, mxREAL);
            data = (uint64_t *)mxGetData(plhs[0]);
            return data;
            break;
                            }
        case mxINT16_CLASS:{
            int *data;
            plhs[0] = mxCreateNumericArray(ndim, dims, classID, mxREAL);
            data = (int *)mxGetData(plhs[0]);
            return data;
            break;
                           }
        default:{
            int *data;
            plhs[0] = mxCreateNumericArray(ndim, dims, classID, mxREAL);
            data = (int *)mxGetData(plhs[0]);
            return data;
            break;
                } //16bits
    }

}

// test functions
int setValue(const mxArray *prhsv){ //pointer to right hand side value
    char *funcName = mxArrayToString(prhsv);
    std::string str(funcName);
    return 2;
}

void doFunction(std::string name, mxArray *plhs[], const mxArray *prhs[]){
    Rhd2000EvalBoard *evalBoard = retrieveHandle(prhs);
    bool running = evalBoard->isRunning();

    char *pewp=new char[name.size()+1];
    pewp[name.size()]=0;
    memcpy(pewp,name.c_str(),name.size());
    mexPrintf(pewp);
    mexPrintf("\n");

    switch (fNameMap[name]){
        case isRunning_e:{
                        int *data = (int *)makeOutput(plhs, mxINT16_CLASS);
                        if (running)
                            data[0] = 1;
                        else
                            data[0] = -3;
                        break;
                         }
        case getValue_e:{
                        int *data = (int *)makeOutput(plhs, mxINT16_CLASS);
                        data[0] = 1;
                        break;
                        }
        case setValue_e:{
                        int *data = (int *)makeOutput(plhs, mxINT16_CLASS);
                        data[0] = setValue(prhs[1]);
                        break;
                        }
        case create_e:{
                        uint64_t *data = (uint64_t *)makeOutput(plhs, mxUINT64_CLASS);
                        data[0] = reinterpret_cast<uint64_t>(createObject());
                        break;
                      }
        case init_e:{
                        int *data = (int *)makeOutput(plhs, mxINT16_CLASS);
                        data[0] = initBoard(evalBoard);
                        break;
                    }
        case delete_e:{
                        deleteObject(evalBoard);
                        break;
                      }

        case SampleRate_e:{
                        int *data = (int *)makeOutput(plhs,mxINT16_CLASS);
                        data[0] = setSampleRate(evalBoard, prhs);
                        break;
                          }
        case SamplesPerTrigger_e:{
                        int *data = (int *)makeOutput(plhs,mxINT16_CLASS);
                        SamplesPerTrigger_s;
                        break;
                                 }
        case TriggerRepeat_e:{
                        int *data = (int *)makeOutput(plhs,mxINT16_CLASS);
                        TriggerRepeat_s; //gonna need something persistent here...
                        break;
                             }
        case LogFileName_e:{
                        int *data = (int *)makeOutput(plhs,mxINT16_CLASS);
                        LogFileName_s;
                        break;
                           }
        default :{
                        int *data = (int *)makeOutput(plhs,mxINT16_CLASS);
                        data[0] = -1;
                        break;
                 }
    }
}


//plhs format
//[int ErrorValue, return value 1, ... , return value n]

/*
 * nlhs = n expected output mxArrays // number left hand size
 * plhs = array of pointers to the expected output mxArrays //pointer left hand side
 * nrhs = number of input mxArrays
 * prhs = array of pointers to input mxArrays #apparently don't change prhs values
 */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){


    /* Check for proper number of input and output arguments */
    if (nrhs < 2) {
        mexErrMsgIdAndTxt( "MATLAB:mxisfinite:invalidNumInputs",
                "One input argument required.");
    }
    if(nlhs > 1){
        mexErrMsgIdAndTxt( "MATLAB:mxisfinite:maxlhs",
                "Too many output arguments.");
    }
    
    /* Check data type of input argument */
    if (!(mxIsClass(prhs[0],"intan"))){
        mexErrMsgIdAndTxt( "MATLAB:mxisfinite:invalidInputType",
                "First input argument must be of type intan.");
    }
    if (!(mxIsChar(prhs[1]))){
        mexErrMsgIdAndTxt( "MATLAB:mxisfinite:invalidInputType",
                "Second input argument must be of type char.");
    }	
    
    /* Check argument counts */
    if (mxIsEmpty(prhs[0])) {
        mexWarnMsgIdAndTxt("MATLAB:mxisfinite:empty",
                "Input argument 1 is empty\n");
    }
    else if (mxIsEmpty(prhs[1])) {
        mexWarnMsgIdAndTxt("MATLAB:mxisfinite:empty",
                "Input argument 2 is empty\n");
    }

    char *funcName = mxArrayToString(prhs[1]); //prhs[0] was causing the access violation
    std::string sFN = funcName;

    /* now THIS is stupid
    int test = 10;
    mexPrintf("%s \n", test);
    */

    //mexPrintf("%s \n", NumArgsMap);
    //mexPrintf("%s \n", SampleRate_s);
    //mexPrintf("%s \n", NumArgsMap[SampleRate_s]); //why is this null?
    //mexPrintf("%s \n", NumArgsMap[sFN]);

    char *pewp=new char[sFN.size()+1];
    pewp[sFN.size()]=0;
    memcpy(pewp,sFN.c_str(),sFN.size());
    mexPrintf("what: ",pewp);

    //check the map to see if we have the correct number of args
    if ( NumArgsMap[sFN] != (nrhs - 2) ){ //FIXME this compaprison is broken >_<
        int *data = (int *)makeOutput(plhs,mxINT16_CLASS);
        //data[0] = (nrhs - 2);
        data[0] = -1;

        //data[0] = NumArgsMap[SampleRate_s];
        //data[0] = NumArgsMap[sFN];
        //mexErrMsgIdAndTxt("MATLAB:mxisfinite:invalidNumInputs",
               //"Number of inputs does not match for function.");
    }
    else {
        mexPrintf("this and 'what:' should NEVER appear together\n");
        doFunction(sFN, plhs, prhs);
    }

    mxFree(funcName);
    //expects the name of a function follow by any arguments to pass to it

}


//get the name of the function

//make sure nlhs matches

//use mxGetProperty to retrieve the cpp_handle value so we don't have to pass it in



const char *mexFunctionName(void);
