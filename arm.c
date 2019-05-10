/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    arm.c

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

#include "arm.h"

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
    void ARM_Initialize ( void )

  Remarks:
    See prototype in arm.h.
 */

void ARM_Initialize ( void )
{
    PWM_Initialize();
}


/******************************************************************************
  Function:
    void ARM_Tasks ( void )

  Remarks:
    See prototype in arm.h.
 */

void ARM_Tasks ( void )
{
    dbgOutputLoc(ENTER_ARM_TASK);
    
    PWM_Start();
    
    bool b = false, l = false, r = false, g = false;
    
    ARM_UPDATE base_servo;
    base_servo.servo_id = 0;
    base_servo.current_val = BASE_NEUTRAL;
    base_servo.target_val = BASE_NEUTRAL;
    
    ARM_UPDATE right_servo;
    right_servo.servo_id = 1;
    right_servo.current_val = RIGHT_BEGIN;
    right_servo.target_val = RIGHT_BEGIN;
    
    ARM_UPDATE left_servo;
    left_servo.servo_id = 2;
    left_servo.current_val = LEFT_BEGIN;
    left_servo.target_val = LEFT_BEGIN;
    
    ARM_UPDATE grip_servo;
    grip_servo.servo_id = 3;
    grip_servo.current_val = GRIP_OPEN;
    grip_servo.target_val = GRIP_OPEN;
    
    ARM_UPDATE arm_update;
    
    dbgOutputLoc(TASK_BEFORE_LOOP);
    while(1){
        arm_update = arm_queue_Receive();
                
        if(arm_update.stop == TRUE){
            if(arm_update.servo_id == 0){
                base_servo.target_val = base_servo.current_val;
            }            
        } else {
            if(arm_update.update == TRUE){
                target_change(&base_servo, &right_servo, &left_servo, &grip_servo, &arm_update);  
            } else {}
            
            if(base_servo.current_val != base_servo.target_val){
                servo_compare_base(&base_servo);
                b = true;
            } else {b = false;}
            if(right_servo.current_val != right_servo.target_val){
                servo_compare_right(&right_servo);
                r = true;
            } else {r = false;}
            if(left_servo.current_val != left_servo.target_val){
                servo_compare_left(&left_servo);
                l = true;
            } else {l = false;}
            if(grip_servo.current_val != grip_servo.target_val){
                servo_compare_grip(&grip_servo);
                g = true;
            } else {g = false;}
        }
        
        if(base_servo.current_val == base_servo.target_val){
            if(b){
                ACTION_TYPE action_type;
                action_type.ready = FALSE;
                action_type.action_type = 0;
                action_type.done = TRUE;
                action_type.servo_id = 0;
                movement_queue_SendToBack(action_type);
            }            
        }
        if(right_servo.current_val == right_servo.target_val){
            if(r){
                ACTION_TYPE action_type;
                action_type.ready = FALSE;
                action_type.action_type = 0;
                action_type.done = TRUE;
                action_type.servo_id = 1;
                movement_queue_SendToBack(action_type);
            }                
        }
        if(left_servo.current_val == left_servo.target_val){
            if(l){
                ACTION_TYPE action_type;
                action_type.ready = FALSE;
                action_type.action_type = 0;
                action_type.done = TRUE;
                action_type.servo_id = 2;
                movement_queue_SendToBack(action_type);
            }                
        }
        if(grip_servo.current_val == grip_servo.target_val){
            if(g){
                ACTION_TYPE action_type;
                action_type.ready = FALSE;
                action_type.action_type = 0;
                action_type.done = TRUE;
                action_type.servo_id = 3;
                movement_queue_SendToBack(action_type);
            }                
        }
    }
}

 

/*******************************************************************************
 End of File
 */
