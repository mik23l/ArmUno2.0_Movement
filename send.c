/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    send.c

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

#include "send.h"

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
    void SEND_Initialize ( void )

  Remarks:
    See prototype in send.h.
 */

void SEND_Initialize ( void )
{
    
}


/******************************************************************************
  Function:
    void SEND_Tasks ( void )

  Remarks:
    See prototype in send.h.
 */

void SEND_Tasks ( void )
{
    dbgOutputLoc(ENTER_SEND_TASK);
    
    static ServerLog log;
    ResetServerLog(&log);
    
    Arm_Status arm_status;
    
    dbgOutputLoc(TASK_BEFORE_LOOP);
    while(1){
        Package Data = PackageReceiveFromQueue(SenderQueue);
        if(Data.ArmStatus != unknown_state){
            arm_status = Data.ArmStatus;
        }
        PackageToJson(&Data, &log, arm_status);
    } 
}


/*******************************************************************************
  Function:
    void ResetServerLog(ServerLog *log)

  Remarks:
    See prototype in send.h.
 */

void ResetServerLog(ServerLog *log)
{
    log -> GoodResponse = 0;
    log -> BadResponse = 0;
    log -> MissedResponse = 0;
    log -> SentRequest = 0;
    log -> SequenceNumber= 0;
    log -> RoverSequenceNumber = 0;
    log -> Pulse = 0;
}


/*******************************************************************************
  Function:
    UpdateLog(Package *Data, ServerLog *log)

  Remarks:
    See prototype in send.h.
 */

UpdateLog(Package *Data, ServerLog *log)
{
    switch(Data -> DataLogType)
    {
        case Good:
        {
            log -> GoodResponse++;
        }
        break;
        case Bad:
        {
            log -> BadResponse++;
        }
        break;
        case SequenceNumber:
        {
            if(Data -> DataReady)
            {
                if(Data -> SequenceNumber != log -> RoverSequenceNumber)
                {
                    if(Data -> SequenceNumber != log -> RoverSequenceNumber - 1)
                    {
                        uint32_t diff = abs(Data -> SequenceNumber - log -> RoverSequenceNumber);
                        log -> MissedResponse += diff;
                    }
                    log -> RoverSequenceNumber = Data -> SequenceNumber;
                }
                log -> RoverSequenceNumber ++;
            }
        }
        break;
        default:
        {
            dbgOutputError(SERVERLOG_FAIL);
        }
        break;
    }
}


/*******************************************************************************
  Function:
    SendData(Package *Data, ServerLog *log)

  Remarks:
    See prototype in send.h.
 */

SendData(Package *Data, ServerLog *log, Arm_Status arm_status)
{
    log -> Pulse++;
    if(log -> Pulse == 20)
    {
        Package pack;
        PackageInit(&pack, Log);
        pack.CorrectResponse = log -> GoodResponse;
        pack.MissedResponse = log -> MissedResponse;
        pack.BadResponse = log -> BadResponse;
        pack.RequestSent = log -> SentRequest;
        WriteRequest(PUT, DataLog, &pack);
        log -> GoodResponse = 0;
        log -> BadResponse = 0;
        log -> MissedResponse = 0;
        log -> SentRequest = 0;
        log -> Pulse = 0;
    }
    else if(log -> Pulse % 2 == 0)
    {
        if(!Data -> DataReady)
        {
            Data -> ArmStatus = arm_status;      
        }
        Data -> SequenceNumber = log -> SequenceNumber;
        WriteRequest(PUT, Arms, Data);
        log -> SequenceNumber++;
        log -> SentRequest ++;
    }
    else if(log -> Pulse % 3  == 0)
    {
        WriteRequest(GET, Rover, Data);
        log -> SentRequest ++;
    }
    else
    {
        WriteRequest(GET, Station, Data);
        log -> SentRequest ++;
    }
}


/*******************************************************************************
  Function:
    void PackageToJson(Package *pack, ServerLog *log)

  Remarks:
    See prototype in send.h.
 */

void PackageToJson(Package *pack, ServerLog *log, Arm_Status arm_status)
{
    switch(pack -> Source)
    {
        case Board:
        {
            SendData(pack, log, arm_status);
        }
        break;
        case Log:
        {
            UpdateLog(pack, log);
        }
        break;
        default:
        {
            dbgOutputError(PACK_TO_JSON_FAIL);
        }
        break;
    }
}

 

/*******************************************************************************
 End of File
 */
