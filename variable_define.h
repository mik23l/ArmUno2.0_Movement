/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    variable_define.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _VARIABLE_DEFINE_H    /* Guard against multiple inclusion */
#define _VARIABLE_DEFINE_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

#define UARTMessage uint8_t
#define UARTMessageSize   sizeof(UARTMessage)
#define MAX_BYTE_SIZE  1024
#define MAX_JSON_SIZE  512
#define ServoPulseWidth uint16_t
#define ServoPulseWidthSize sizeof(ServoPulseWidth)
#define PackageSize sizeof(Package)
#define BAUDRATE_SERVER 57600
#define BRGVAL_SERVER ((FP/BAUDRATE_SERVER)/16)-1
#define JsonMessageSize sizeof(JsonMessage)
#define ADC_NUM_SAMPLE_PER_AVERAGE 16


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    typedef enum
    {
        ReceiverQueue = 0,
        RequestQueue = 1,
        ResponseQueue = 2,
        SenderQueue = 3,
        GetJsonQueue = 4,
        PutJsonQueue = 5,
        DataInterQueue = 8
    }QueueName;
    
    typedef enum
    {
        GetVersion = 0,
        GetCode = 1,
        GetData = 2
    }ReceiverState;
    
    typedef enum
    {
        FindLeftCurl = 0,
        ReceiveData = 1,
        FindCarrigeReturn = 2
    }ReceiverSubState;
    
    typedef enum
    {
        StepOne = 0,
        StepTwo = 1,
        StepTrd = 2,
        StepFor = 3,
        StepFth = 4,
        StepSix = 5,
        StepSvh = 6,
        StepEth = 7
    }HeaderStep;
    
    typedef struct
    {
        ReceiverState State;
        ReceiverSubState SubState;
        bool DataReady;
        HeaderStep Step;
        int TailPtr;
        int CurlCount;
        uint32_t ByteCount;
        char* JsonPack;
    }ReceiverLog;
    
    typedef enum
    {
        centimeter = 0,
        inch = 1
    }units;
    
    typedef enum
    {
        Unknown = 0,
        Table1 = 1,
        Table2 = 2,
        Table3 = 3,
        Kitchen = 4,
        BoundaryMarker = 5
    }ItemType;
    
    typedef enum
    {
        run = 1,
        stop = 0,
        ready = 3,
        unknown_status = 2
    }Rover_Status;
    
    typedef enum
    {
        ready_pick = 0,
        picking_up = 1,
        ready_drop = 2,
        dropping_off = 3,
        too_far = 5,
        unknown_state = 4
    }Arm_Status;
    
    typedef enum
    {
        Server = 2,
        Board = 3,
        Log = 4
    }DataSource;
    
    typedef enum
    {
        Good = 0,
        Bad = 1,
        SequenceNumber = 2,
    }LogType;
    
    typedef enum
    {
        Rover_type = 0,
        Sensor_type = 1,
        Station_type = 2,
        unknown_type = 3
    }Read_Type;
    
    typedef struct
    {
        uint16_t ADC10;
        uint16_t ADC20;
        units    ADCUnit;
        ItemType Item;
        Arm_Status ArmStatus;
        Rover_Status RoverStatus;
        int KitchenTable;
        int TableOne;
        int TableTwo;
        int TableThree;
        int ItemColor;
        Read_Type ReadType;
        DataSource Source;
        bool DataReady;
        int CorrectResponse;
        int BadResponse;
        int MissedResponse;
        int RequestSent;
        uint32_t SequenceNumber;
        LogType DataLogType;
    }Package;
    
    typedef enum
    {
        GET = 0,
        PUT = 1
    }RequestType;
    
    typedef enum
    {
        Sensor = 0,
        Rover = 1,
        Arms = 2,
        Station = 3,
        DataLog = 4
    }DocumentName;
    
    typedef struct
    {
        int GoodResponse;
        int BadResponse;
        int MissedResponse;
        int SentRequest;
        uint32_t SequenceNumber;
        uint32_t RoverSequenceNumber;
        int Pulse;
    }ServerLog;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************




    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _VARIABLE_DEFINE_H */

/* *****************************************************************************
 End of File
 */
