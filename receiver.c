/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    receiver.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "receiver.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************




// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void RECEIVER_Initialize ( void )

  Remarks:
    See prototype in receiver.h.
 */

void RECEIVER_Initialize ( void )
{
    PackageQueueInit();
    UARTQueueInit();
    ServerInitialize();
}


/******************************************************************************
  Function:
    void RECEIVER_Tasks ( void )

  Remarks:
    See prototype in receiver.h.
 */

void RECEIVER_Tasks ( void )
{
    dbgOutputLoc(ENTER_RECEIVER_TASK);
    
    DRV_TMR2_Start();
    ReceiverLog log;
    ResetReceiverLog(&log);
    static char String[512];
    log.JsonPack = String;
    
    dbgOutputLoc(TASK_BEFORE_LOOP);

    while(1)
    {
        UARTMessage Data = ReadResponse();
        HeaderChecker(&Data, &log);
        if(log.DataReady)
        {
            SendJsonMessage(&log);
        }
    }
}


/******************************************************************************
  Function:
    void ResetReceiverLog(ReceiverLog *log)

  Remarks:
    See prototype in receiver.h.
 */

void ResetReceiverLog(ReceiverLog *log)
{
    log -> State = GetVersion;
    log -> SubState = FindLeftCurl;
    log -> DataReady = false;
    log -> Step = StepOne;
    log -> TailPtr = 0;
    log -> CurlCount = 0;
    log -> ByteCount = 0;
}


/******************************************************************************
  Function:
    GetDataHelper(UARTMessage *Data, ReceiverLog *log)

  Remarks:
    See prototype in receiver.h.
 */

GetDataHelper(UARTMessage *Data, ReceiverLog *log)
{
    if(log -> ByteCount >= MAX_BYTE_SIZE)
    {
        SendBadRequest();
        ResetReceiverLog(log);
    }
    else
    {
        log -> ByteCount++;
        switch(log -> SubState)
        {
            case FindLeftCurl:
            {
                if(*Data == '{')
                {
                    log -> SubState = ReceiveData;
                    log -> CurlCount ++;
                    log -> JsonPack[log -> TailPtr] = *Data;
                    log -> TailPtr ++;
                }
            }
            break;
            case ReceiveData:
            {
                if(log -> CurlCount == 0)
                {
                    log -> SubState = FindCarrigeReturn;
                }
                else
                {
                    if(*Data == '{')
                    {
                        log -> CurlCount++;
                    }
                    if(*Data == '}')
                    {
                        log -> CurlCount--;
                    }
                    if(log->TailPtr > 512)
                    {
                        SendBadRequest();
                        ResetReceiverLog(log);
                    }
                    else
                    {
                        log -> JsonPack[log -> TailPtr] = *Data;
                        log -> TailPtr++;
                    }
                }
            }
            break;
            case FindCarrigeReturn:
            {
                log -> DataReady = true;
            }
            break;
        }
    }
}


/******************************************************************************
  Function:
    void GetCodeHelper(UARTMessage *Data, ReceiverLog *log)

  Remarks:
    See prototype in receiver.h.
 */

void GetCodeHelper(UARTMessage *Data, ReceiverLog *log)
{
    if(log -> ByteCount >= MAX_BYTE_SIZE)
    {
        SendBadRequest();
        ResetReceiverLog(log);
    }
    else
    {
        log -> ByteCount++;
        switch(log -> Step)
        {
            case StepOne:
            {
                if(*Data == '4' || *Data == '5')
                {
                    SendBadRequest();
					ResetReceiverLog(log);
                }
                if(*Data == '2')
                {
                    log -> Step = StepTwo;
                }
            }
            break;
            case StepTwo:
            {
                if(*Data == '0')
                {
                    log -> Step = StepTrd;
                }
            }
            break;
            case StepTrd:
            {
                if(*Data == '1')
                {
                    Package GoodRequest;
                    PackageInit(&GoodRequest, Log);
                    GoodRequest.DataLogType = Good;
                    PackageQueueSendToBack(GoodRequest, SenderQueue);
                    ResetReceiverLog(log);
                }
                if(*Data == '0')
                {
                    log -> State = GetData;
                    
                }
            }
        }
    }
}


/******************************************************************************
  Function:
    void GetVersionHelper(UARTMessage *Data, ReceiverLog *log)

  Remarks:
    See prototype in receiver.h.
 */

void GetVersionHelper(UARTMessage *Data, ReceiverLog *log)
{
    if(log -> ByteCount > MAX_BYTE_SIZE)
    {
        SendBadRequest();
        ResetReceiverLog(log);
    }
    else
    {
        log -> ByteCount++;
        switch(log -> Step)
        {
            case StepOne:
            {
                if(*Data == 'H')
                {
                    log -> Step = StepTwo;
                }
                else
                {
                    log -> ByteCount = 0;
                }
            }
            break;
            case StepTwo:
            {
                if(*Data == 'T')
                {
                    log -> Step = StepTrd;
                }
            }
            break;
            case StepTrd:
            {
                if(*Data == 'T')
                {
                    log -> Step = StepFor;
                }
            }
            break;
            case StepFor:
            {
                if(*Data == 'P')
                {
                    log -> Step = StepFth;
                }
            }
            break;
            case StepFth:
            {
                if(*Data == '/')
                {
                    log -> Step = StepSix;
                }
            }
            break;
            case StepSix:
            {
                if(*Data == '1')
                {
                    log -> Step = StepSvh;
                }
            }
            break;
            case StepSvh:
            {
                if(*Data == '.')
                {
                    log -> Step = StepEth;
                }
            }
            break;
            case StepEth:
            {
                if(*Data == '1')
                {
                    log -> State = GetCode;
                    log -> Step = StepOne;
                }
            }
            break;
            default:
            {
                dbgOutputError(HTTP_RECEIVE_ERROR);
            }
            break;
        }
    }
}


/******************************************************************************
  Function:
    void HeaderChecker(UARTMessage *Data, ReceiverLog *log)

  Remarks:
    See prototype in receiver.h.
 */

void HeaderChecker(UARTMessage *Data, ReceiverLog *log)
{
    switch(log -> State)
    {
        case GetVersion:
        {
            GetVersionHelper(Data, log);
        }
        break;
        case GetCode:
        {
            GetCodeHelper(Data, log);
        }
        break;
        case GetData:
        {
            GetDataHelper(Data, log);
        }
        break;
        default:
        {
            dbgOutputError(HTTP_RECEIVE_ERROR);
        }
        break;
    }
}


/******************************************************************************
  Function:
    void SendJsonMessage(ReceiverLog *log)

  Remarks:
    See prototype in receiver.h.
 */

void SendJsonMessage(ReceiverLog *log)
{
    if(log -> TailPtr >= MAX_JSON_SIZE)
    {
        SendBadRequest();
        ResetReceiverLog(log);
    }
    else
    {
        ParseJson(log);
        ResetReceiverLog(log);
    }
}


/******************************************************************************
  Function:
    void UpdateRover(ReceiverLog *log, jsmntok_t *t, int r)

  Remarks:
    See prototype in receiver.h.
 */

void UpdateRover(ReceiverLog *log, jsmntok_t *t, int r)
{
    Package RoverStatus;
    PackageInit(&RoverStatus, Server);
    RoverStatus.ReadType = Rover_type;
    Package pack;
    PackageInit(&pack, Log);
    pack.DataLogType = SequenceNumber;
    int i;
    bool Check[3];
    Check[0] = false;
    Check[1] = false;
    Check[2] = false;
    for(i = 1; i < r; ++i)
    {
        if(jsoneq(log -> JsonPack, &t[i], "Status"))
        {
            char status[10];
            size_t size = &t[i + 1].end - &t[i + 1].start;
            strncpy(status, log -> JsonPack + t[i + 1].start, size);
            status[size] = '\0';
            Rover_Status temp = atoi(status);
            RoverStatus.RoverStatus = temp;
            Check[0] = true;
        }
        if(jsoneq(log -> JsonPack, &t[i], "SN"))
        {
            char SN[32];
            size_t size = &t[i + 1].end - &t[i + 1].start;
            strncpy(SN, log -> JsonPack + t[i + 1].start, size);
            SN[size] = '\0';
            uint32_t SequenceNum = atoi(SN);
            pack.SequenceNumber = SequenceNum;
            pack.DataReady = true;
            Check[1] = true;
        }
        if(Check[0] && Check[1] && true)
        {
            Check[2] = true;
            break;
        }
    }
    if(!Check[2] && true)
    {
        RoverStatus.Source = Log;
        RoverStatus.DataLogType = Bad;
        PackageQueueSendToBack(RoverStatus, SenderQueue);
    }
    else
    {
        SendGoodRequest();
        PackageQueueSendToBack(RoverStatus,ReceiverQueue);
        PackageQueueSendToBack(pack,SenderQueue);
    }
}


/******************************************************************************
  Function:
    void UpdateSensor(ReceiverLog *log, jsmntok_t *t, int r)

  Remarks:
    See prototype in receiver.h.
 */

void UpdateSensor(ReceiverLog *log, jsmntok_t *t, int r)
{
    Package SensorStatus;
    PackageInit(&SensorStatus, Server);
    SensorStatus.ReadType = Sensor_type;
    Package pack;
    PackageInit(&pack, Log);
    pack.DataLogType = SequenceNumber;
    int i;
    bool Check[5];
    Check[0] = false;
    Check[1] = false;
    Check[2] = false;
    Check[3] = false;
    Check[4] = false;
    for(i = 1; i < r; ++i)
    {
        if(jsoneq(log -> JsonPack, &t[i], "Distance"))
        {
            char distance[20];
            size_t size = &t[i + 1].end - &t[i + 1].start;
            strncpy(distance, log -> JsonPack + t[i + 1].start, size);
            distance[size] = '\0';
            uint16_t temp = atoi(distance);
            SensorStatus.ADC10 = temp;
            Check[0] = true;
        }
        if(jsoneq(log -> JsonPack, &t[i], "Degree"))
        {
            char degree[20];
            size_t size = &t[i + 1].end - &t[i + 1].start;
            strncpy(degree, log -> JsonPack + t[i + 1].start, size);
            degree[size] = '\0';
            uint16_t temp = atoi(degree);
            SensorStatus.ADC20 = temp;
            Check[1] = true;
        }
        if(jsoneq(log -> JsonPack, &t[i], "ItemType"))
        {
            char itemtype[20];
            size_t size = &t[i + 1].end - &t[i + 1].start;
            strncpy(itemtype, log -> JsonPack + t[i + 1].start, size);
            itemtype[size] = '\0';
            uint16_t temp = atoi(itemtype);
            SensorStatus.Item = temp;
            Check[2] = true;
        }
        if(jsoneq(log -> JsonPack, &t[i], "SN"))
        {
            char SN[32];
            size_t size = &t[i + 1].end - &t[i + 1].start;
            strncpy(SN, log -> JsonPack + t[i + 1].start, size);
            SN[size] = '\0';
            uint32_t SequenceNum = atoi(SN);
            pack.SequenceNumber = SequenceNum;
            pack.DataReady = true;
            Check[3] = true;
        }
        if(Check[0] && Check[1] && Check[2] && Check[3] && true)
        {
            Check[4] = true;
            break;
        }
    }
    if(!Check[4] && true)
    {
        SensorStatus.Source = Log;
        SensorStatus.DataLogType = Bad;
        PackageQueueSendToBack(SensorStatus, SenderQueue);
    }
    else
    {
        SendGoodRequest();
        PackageQueueSendToBack(SensorStatus,ReceiverQueue);
        PackageQueueSendToBack(pack,SenderQueue);
    }
}

/******************************************************************************
  Function:
    void UpdateStation(ReceiverLog *log, jsmntok_t *t, int r)

  Remarks:
    See prototype in receiver.h.
 */

void UpdateStation(ReceiverLog *log, jsmntok_t *t, int r)
{
    Package StationStatus;
    PackageInit(&StationStatus, Server);
    StationStatus.ReadType = Station_type;
    Package pack;
    PackageInit(&pack, Log);
    pack.DataLogType = SequenceNumber;
    int i;
    bool Check[6];
    Check[0] = false;
    Check[1] = false;
    Check[2] = false;
    Check[3] = false;
    Check[4] = false;
    Check[5] = false;
    Check[6] = false;
    for(i = 1; i < r; ++i)
    {
        if(jsoneq(log -> JsonPack, &t[i], "ObjectColor"))
        {
            char color[20];
            size_t size = &t[i + 1].end - &t[i + 1].start;
            strncpy(color, log -> JsonPack + t[i + 1].start, size);
            color[size] = '\0';
            uint16_t temp = atoi(color);
            StationStatus.ItemColor = temp;
            Check[0] = true;
        }
        if(jsoneq(log -> JsonPack, &t[i], "KitchenTableOccupied"))
        {
            char kitchen[20];
            size_t size = &t[i + 1].end - &t[i + 1].start;
            strncpy(kitchen, log -> JsonPack + t[i + 1].start, size);
            kitchen[size] = '\0';
            uint16_t temp = atoi(kitchen);
            StationStatus.KitchenTable = temp;
            Check[1] = true;
        }
        if(jsoneq(log -> JsonPack, &t[i], "TableOneOccupied"))
        {
            char one[20];
            size_t size = &t[i + 1].end - &t[i + 1].start;
            strncpy(one, log -> JsonPack + t[i + 1].start, size);
            one[size] = '\0';
            uint16_t temp = atoi(one);
            StationStatus.TableOne = temp;
            Check[2] = true;
        }
        if(jsoneq(log -> JsonPack, &t[i], "TableTwoOccupied"))
        {
            char two[20];
            size_t size = &t[i + 1].end - &t[i + 1].start;
            strncpy(two, log -> JsonPack + t[i + 1].start, size);
            two[size] = '\0';
            uint16_t temp = atoi(two);
            StationStatus.TableTwo = temp;
            Check[3] = true;
        }
        if(jsoneq(log -> JsonPack, &t[i], "TableThreeOccupied"))
        {
            char three[20];
            size_t size = &t[i + 1].end - &t[i + 1].start;
            strncpy(three, log -> JsonPack + t[i + 1].start, size);
            three[size] = '\0';
            uint16_t temp = atoi(three);
            StationStatus.TableThree = temp;
            Check[4] = true;
        }
        if(jsoneq(log -> JsonPack, &t[i], "SN"))
        {
            char SN[32];
            size_t size = &t[i + 1].end - &t[i + 1].start;
            strncpy(SN, log -> JsonPack + t[i + 1].start, size);
            SN[size] = '\0';
            uint32_t SequenceNum = atoi(SN);
            pack.SequenceNumber = SequenceNum;
            pack.DataReady = true;
            Check[5] = true;
        }
        if(Check[0] && Check[1] && Check[2] && Check[3] && Check[4] && Check[5] && true)
        {
            Check[6] = true;
            break;
        }
    }
    if(!Check[6] && true)
    {
        StationStatus.Source = Log;
        StationStatus.DataLogType = Bad;
        PackageQueueSendToBack(StationStatus, SenderQueue);
    }
    else
    {
        SendGoodRequest();
        PackageQueueSendToBack(StationStatus,ReceiverQueue);
        PackageQueueSendToBack(pack,SenderQueue);
    }
}


/******************************************************************************
  Function:
    void JsonToPackage(ReceiverLog *log, jsmntok_t *t, int r)

  Remarks:
    See prototype in receiver.h.
 */

void JsonToPackage(ReceiverLog *log, jsmntok_t *t, int r)
{
    int i;
    bool CheckSensor = false;
    bool CheckRover = false;
    bool CheckStation = false;
    for(i = 1; i < r; ++i)
    {
        if (jsoneq(log -> JsonPack, &t[i], "name"))
        {
            if(jsoneq(log -> JsonPack, &t[i + 1], "rover"))
            {
                CheckRover = true;  
                break;
            } 
            else if(jsoneq(log -> JsonPack, &t[i + 1], "sensor"))
            {
                CheckSensor = true;
                break;
            } 
            else if(jsoneq(log -> JsonPack, &t[i + 1], "station"))
            {
                CheckStation = true;
                break;
            }
        }
    }
        
    if(CheckSensor) {UpdateSensor(log, t, r);} 
    else if(CheckRover) {UpdateRover(log, t, r);}
    else if(CheckStation) {UpdateStation(log, t, r);}
    else {SendBadRequest();}
} 


/******************************************************************************
  Function:
    void ParseJson(ReceiverLog *log)

  Remarks:
    See prototype in receiver.h.
 */

void ParseJson(ReceiverLog *log)
{
    int r;
	jsmn_parser p;
	jsmntok_t t[128]; /* We expect no more than 128 tokens */

	jsmn_init(&p);
	r = jsmn_parse(&p, log, t, sizeof(t)/sizeof(t[0]));
	if (r < 0) {
		SendBadRequest();
	}
    /* Assume the top-level element is an object */
	else if (r < 1 || t[0].type != JSMN_OBJECT) {
		SendBadRequest();
	}
    else
    {
        JsonToPackage(log, t, r);
    }
}


/******************************************************************************
  Function:
    void SendBadRequest()

  Remarks:
    See prototype in receiver.h.
 */

void SendBadRequest()
{
    Package BadRequest;
    PackageInit(&BadRequest, Log);
    BadRequest.DataLogType = Bad;
    PackageQueueSendToBack(BadRequest, SenderQueue);
}


/******************************************************************************
  Function:
    void SendGoodRequest()

  Remarks:
    See prototype in receiver.h.
 */

void SendGoodRequest()
{
    Package GoodRequest;
    PackageInit(&GoodRequest, Log);
    GoodRequest.DataLogType = Good;
    PackageQueueSendToBack(GoodRequest, SenderQueue);
}

 

/*******************************************************************************
 End of File
 */
