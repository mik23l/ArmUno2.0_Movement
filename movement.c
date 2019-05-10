/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    movement.c

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

#include "movement.h"

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
    void MOVEMENT_Initialize ( void )

  Remarks:
    See prototype in movement.h.
 */

void MOVEMENT_Initialize ( void )
{
    arm_queue_Initialize();
}


/******************************************************************************
  Function:
    void MOVEMENT_Tasks ( void )

  Remarks:
    See prototype in movement.h.
 */

void MOVEMENT_Tasks ( void )
{
    dbgOutputLoc(ENTER_MOVEMENT_TASK);
    
    DRV_TMR1_Start();
    
    ACTION_TYPE action_type;
    
    bool ready = FALSE;
    int action = 0;
    uint16_t distance = 0;
    
    int pick_part = 0;
    int drop_part = 0;
    
    int done_count = 0;
    
    int radar_count = 0;
    
    dbgOutputLoc(TASK_BEFORE_LOOP);
    while(1){
        action_type = movement_queue_Receive();
        if(action_type.ready == TRUE){
            ready = TRUE;
            distance = action_type.distance;
            radar_count = 0;
        } else {}
        if(action_type.action_type == 1){
            action = 1;
            if(ready){
                radar_count = 0;
            } else if(radar_count == 0) {
                radar_count = 1;
                radar(&radar_count);
            } else {}
        } else if(action_type.action_type == 2){
            action = 2;
        } else if(action_type.action_type == 3){
            action = 3;
        } else if(action_type.action_type == 4){
            action = 4;
        } else if(action_type.action_type == 5){
            action = 5;
        } else if(action_type.action_type == 6){
            action = 6;
        } else if(action_type.action_type == 7){
            action = 7;
        } else {}
        if(((radar_count != 0) && (action_type.done == TRUE))){
            if((action_type.servo_id == 0)){
                radar(&radar_count);
            }            
        }
        if(ready && (action != 0)){
            if(action == 1){ //pick up
                pick_move(&pick_part, &distance);
            } else if (action == 2){ //drop off
                drop_move();
            } else if (action == 3){ //finish drop
                finish_move(&drop_part);
            } else if (action == 4){ //drop try1
                drop_try1();
            } else if (action == 5){ //drop try2
                drop_try2();
            } else if (action == 6){ //drop try3
                drop_try3();
            } else if (action == 7){ //drop try4
                drop_try4();
            } else{}
            ready = FALSE;
        } else{}
        if((action_type.done == TRUE) && (action != 0) && (radar_count == 0)){
            if(action == 1){ //pick up
                if(pick_change(&pick_part, &action_type, &done_count, &action, &distance)){
                    if(pick_part != 0){
                        pick_move(&pick_part, &distance);
                    }                    
                }                
            } else if (action == 2){ //drop off
                if((action_type.servo_id == 1) || (action_type.servo_id == 2)){
                    ++done_count;
                } else {}
                if(done_count == 2){
                    done_count = 0;
                    action = 0;
                    Package done_pack;
                    done_pack.DataReady = TRUE;
                    PackageQueueSendToBack(done_pack,ReceiverQueue);
                } else {}                
            } else if (action == 3){ //finish drop
                if(drop_change(&drop_part, &action_type, &done_count, &action)){
                    if(drop_part != 0){
                        finish_move(&drop_part);
                    }
                }
            } else if (action == 4){ //drop try1
                if((action_type.servo_id == 1) || (action_type.servo_id == 2)){
                    ++done_count;
                } else {}
                if(done_count == 2){
                    done_count = 0;
                    action = 0;
                    Package done_pack;
                    done_pack.DataReady = TRUE;
                    PackageQueueSendToBack(done_pack,ReceiverQueue);
                } else {}                
            } else if (action == 5){ //drop try2
                if((action_type.servo_id == 1) || (action_type.servo_id == 2)){
                    ++done_count;
                } else {}
                if(done_count == 2){
                    done_count = 0;
                    action = 0;
                    Package done_pack;
                    done_pack.DataReady = TRUE;
                    PackageQueueSendToBack(done_pack,ReceiverQueue);
                } else {}                
            } else if (action == 6){ //drop try3
                if((action_type.servo_id == 1) || (action_type.servo_id == 0)){
                    ++done_count;
                } else {}
                if(done_count == 2){
                    done_count = 0;
                    action = 0;
                    Package done_pack;
                    done_pack.DataReady = TRUE;
                    PackageQueueSendToBack(done_pack,ReceiverQueue);
                } else {}                
            } else if (action == 7){ //drop try4
                if((action_type.servo_id == 1) || (action_type.servo_id == 0)){
                    ++done_count;
                } else {}
                if(done_count == 2){
                    done_count = 0;
                    action = 0;
                    Package done_pack;
                    done_pack.DataReady = TRUE;
                    PackageQueueSendToBack(done_pack,ReceiverQueue);
                } else {}                
            } else{}
        } else {}
    }
}

/*******************************************************************************
  Function:
    void radar ( int *current )

  Remarks:
    See prototype in movement.h.
 */

void radar ( int *current )
{
    ARM_UPDATE arm_update;
    arm_update.update = TRUE;
    arm_update.stop = FALSE;
    arm_update.servo_id = 0; //base
            
    switch(*current){
        case 1:
            arm_update.target_val = RADAR1;
            arm_queue_SendToBack(arm_update);
            *current = 2;
            break;
        case 2:
            arm_update.target_val = RADAR2;
            arm_queue_SendToBack(arm_update);
            *current = 3;
            break;
        case 3:
            arm_update.target_val = RADAR3;
            arm_queue_SendToBack(arm_update);
            *current = 4;
            break;
        case 4:
            arm_update.target_val = RADAR4;
            arm_queue_SendToBack(arm_update);
            *current = 5;
            break;
        case 5:
            arm_update.target_val = RADAR5;
            arm_queue_SendToBack(arm_update);
            *current = 6;
            break;
        case 6:
            arm_update.target_val = RADAR6;
            arm_queue_SendToBack(arm_update);
            *current = 0;
            
            Package done_pack;
            done_pack.DataReady = TRUE;
            PackageQueueSendToBack(done_pack,ReceiverQueue);
            break;
        default:
            break;
    }
}
    
 

/*******************************************************************************
 End of File
 */
