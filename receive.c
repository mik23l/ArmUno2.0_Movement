/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    receive.c

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

#include "receive.h"

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
    void RECEIVE_Initialize ( void )

  Remarks:
    See prototype in receive.h.
 */

void RECEIVE_Initialize ( void )
{
    movement_queue_Initialize();
}


/******************************************************************************
  Function:
    void RECEIVE_Tasks ( void )

  Remarks:
    See prototype in receive.h.
 */

void RECEIVE_Tasks ( void )
{
    dbgOutputLoc(ENTER_RECEIVE_TASK);
    
    Package package;
    Package current_field;
    current_field.DataReady = FALSE;
   
    Package ArmStatus;
    PackageInit(&ArmStatus, Board);
    ArmStatus.DataReady = TRUE;
    ArmStatus.ArmStatus = ready_pick;
    PackageQueueSendToBack(ArmStatus,DataInterQueue);
    
    int current_arm_state = 1;
    
    int drop_try = 0;
    
    dbgOutputLoc(TASK_BEFORE_LOOP);
    while(1){
        package = PackageReceiveFromQueue(ReceiverQueue);
        
        if(package.ReadType == Rover_type){
            current_field.RoverStatus = package.RoverStatus;
        } else if(package.ReadType == Station_type){
            current_field.KitchenTable = package.KitchenTable;
            if((package.KitchenTable == 1) && (package.ItemColor != 0)){
                current_field.ItemColor = package.ItemColor;
            }            
            current_field.TableOne = package.TableOne;
            current_field.TableTwo = package.TableTwo;
            current_field.TableThree = package.TableThree;
        } else if(package.DataReady){
            current_field.DataReady = package.DataReady;
        } else{}
        
        update_arm(&current_field, &current_arm_state, &drop_try);
    }
}

/******************************************************************************
  Function:
    void update_arm ( Package *package, int *current_arm )

  Remarks:
    See prototype in receive.h.
 */

void update_arm (Package *package, int *current_arm, int *drop_try)
{
    Package ArmStatus;
    PackageInit(&ArmStatus, Board);
    ArmStatus.DataReady = TRUE;
    
    ACTION_TYPE action_pick;
    action_pick.ready = FALSE;
    action_pick.action_type = 1;
    
    ACTION_TYPE action_drop;
    action_drop.ready = TRUE;
    action_drop.action_type = 2;
    
    ACTION_TYPE action_finish;
    action_finish.ready = TRUE;
    action_finish.action_type = 3;   
    
    ACTION_TYPE action_try1;
    action_try1.ready = TRUE;
    action_try1.action_type = 4; 
    
    ACTION_TYPE action_try2;
    action_try2.ready = TRUE;
    action_try2.action_type = 5; 
    
    ACTION_TYPE action_rotate1;
    action_rotate1.ready = TRUE;
    action_rotate1.action_type = 6; 
    
    ACTION_TYPE action_rotate2;
    action_rotate2.ready = TRUE;
    action_rotate2.action_type = 7; 
    
    if(((int)(*current_arm)) == 1){
        if((package->RoverStatus == ready) && (package->KitchenTable == 1)){          
            find_queue_SendToBack(1);
            ArmStatus.ArmStatus = picking_up;
            PackageQueueSendToBack(ArmStatus,DataInterQueue);
            *current_arm = 2;
            movement_queue_SendToBack(action_pick);
        }
    } else if(((int)(*current_arm)) == 2){
        if((package->DataReady) && (package->KitchenTable == 0)){
            ArmStatus.ArmStatus = ready_drop;
            PackageQueueSendToBack(ArmStatus,DataInterQueue);
            *current_arm = 3;
            package->DataReady = false;
        } else if ((package->DataReady) && (package->KitchenTable != 0)){
            ArmStatus.ArmStatus = too_far;
            PackageQueueSendToBack(ArmStatus,DataInterQueue);            
            package->DataReady = false;
            movement_queue_SendToBack(action_finish);
            *current_arm = 1;
        }
    } else if(((int)(*current_arm)) == 3){
        if((package->RoverStatus == ready)){
            ArmStatus.ArmStatus = dropping_off;
            PackageQueueSendToBack(ArmStatus,DataInterQueue);
            *current_arm = 4;
            movement_queue_SendToBack(action_drop);
        }
    } else if(((int)(*current_arm)) == 4){
        if(package->DataReady){
            bool checkItem = false;
            if(package->ItemColor == 1){
                if(package->TableOne == 1){
                    checkItem = true;
                }
            } else if(package->ItemColor == 2){
                if(package->TableTwo == 1){
                    checkItem = true;
                }
            } else if(package->ItemColor == 3){
                if(package->TableThree == 1){
                    checkItem = true;
                }
            } else{}

            if(checkItem){
                *current_arm = 7;
                movement_queue_SendToBack(action_finish);
            }  else {                
                *current_arm = 5;
                movement_queue_SendToBack(action_try1);               
            }
            package->DataReady = false;
        }        
    } else if(((int)(*current_arm)) == 5){
        if(package->DataReady){
            bool checkItem = false;
            if(package->ItemColor == 1){
                if(package->TableOne == 1){
                    checkItem = true;
                }
            } else if(package->ItemColor == 2){
                if(package->TableTwo == 1){
                    checkItem = true;
                }
            } else if(package->ItemColor == 3){
                if(package->TableThree == 1){
                    checkItem = true;
                }
            } else{}

            if(checkItem){
                *current_arm = 7;
                movement_queue_SendToBack(action_finish);
            }  else {
                *current_arm = 6;
                movement_queue_SendToBack(action_try2);
            }
            package->DataReady = false;
        }        
    } else if(((int)(*current_arm)) == 6){
        if(package->DataReady){
            bool checkItem = false;
            if(package->ItemColor == 1){
                if(package->TableOne == 1){
                    checkItem = true;
                }
            } else if(package->ItemColor == 2){
                if(package->TableTwo == 1){
                    checkItem = true;
                }
            } else if(package->ItemColor == 3){
                if(package->TableThree == 1){
                    checkItem = true;
                }
            } else{}

            if(checkItem){
                *current_arm = 7;
                movement_queue_SendToBack(action_finish);
            }  else {
                *current_arm = 4;
                movement_queue_SendToBack(action_drop);
                ++(*drop_try);
                if(((int)(*drop_try)) == 3){
                    *current_arm = 5;
                    movement_queue_SendToBack(action_rotate1);
                } else if ((*drop_try) == 5){
                    *current_arm = 5;
                    movement_queue_SendToBack(action_rotate2);
                    *drop_try = 0;
                } 
            }
            package->DataReady = false;
        }        
    } else if(((int)(*current_arm)) == 7){
        if(package->DataReady){
            ArmStatus.ArmStatus = ready_pick;
            PackageQueueSendToBack(ArmStatus,DataInterQueue);
            *current_arm = 1;
            package->DataReady = false;
        }
    } else {}    
}

 

/*******************************************************************************
 End of File
 */
