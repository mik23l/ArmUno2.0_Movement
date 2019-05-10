/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    find.c

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

#include "find.h"

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
    void FIND_Initialize ( void )

  Remarks:
    See prototype in find.h.
 */

void FIND_Initialize ( void )
{
    find_queue_Initialize();
    
    DRV_ADC_Initialize();
    DRV_ADC_Open();
    DRV_ADC_Start();
    
    DRV_TMR3_Start();
}


/******************************************************************************
  Function:
    void FIND_Tasks ( void )

  Remarks:
    See prototype in find.h.
 */

void FIND_Tasks ( void )
{    
    dbgOutputLoc(ENTER_FIND_TASK);
    
    ACTION_TYPE action_type;
    action_type.ready = TRUE;
    action_type.action_type = 0;
    action_type.distance = 0;
    action_type.done = FALSE;
    
    ARM_UPDATE arm_stop;
    arm_stop.servo_id = 0;
    arm_stop.update = FALSE;
    arm_stop.stop = TRUE; 
    
    uint16_t distance;
    uint16_t total_dis = 0;
    
    int found_count = 0;
    
    bool find_dis = FALSE;
    
    dbgOutputLoc(TASK_BEFORE_LOOP);
    while(1){
        distance = find_queue_Receive();    
        
        if(distance == 1){
            find_dis = TRUE;
        }
        
        if(find_dis){
            if(distance > 4 && distance < 18){
                found_count++;
                total_dis = total_dis + distance;
            }
            
            if(found_count > 5){
                arm_queue_SendToBack(arm_stop);
                action_type.distance = total_dis / 6;
                movement_queue_SendToBack(action_type);
                found_count = 0;
                total_dis = 0;
                find_dis = FALSE;
            }
        }
    }
}

 

/*******************************************************************************
 End of File
 */
