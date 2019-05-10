/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    pick_move.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "pick_move.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */


// *****************************************************************************

/**
  @Function
    void pick_move(int pick part, uint16_t *dis)

  @Summary
    Brief one-line description of the function.
 */
void pick_move(int *pick_part, uint16_t *dis){
    ARM_UPDATE arm_update;
    arm_update.stop = FALSE;
    arm_update.update = TRUE;
    
    if(((int)(*pick_part)) == 0){
        if(((int)(*dis)) < 12){
            arm_update.servo_id = 1; //right
            arm_update.target_val = RIGHT0_PICK1;
            arm_queue_SendToBack(arm_update);

            arm_update.servo_id = 2; //left
            arm_update.target_val = LEFT0_PICK1;
            arm_queue_SendToBack(arm_update);
        } else if ((((int)(*dis)) > 11) && (((int)(*dis)) < 19)){
            arm_update.servo_id = 1; //right
            arm_update.target_val = RIGHT0_PICK2;
            arm_queue_SendToBack(arm_update);

            arm_update.servo_id = 2; //left
            arm_update.target_val = LEFT0_PICK2;
            arm_queue_SendToBack(arm_update);
        } else if (((int)(*dis)) > 18){
            arm_update.servo_id = 1; //right
            arm_update.target_val = RIGHT0_PICK3;
            arm_queue_SendToBack(arm_update);

            arm_update.servo_id = 2; //left
            arm_update.target_val = LEFT0_PICK3;
            arm_queue_SendToBack(arm_update);
        }
    } else if(((int)(*pick_part)) == 1){
        if(((int)(*dis)) < 12){
            arm_update.servo_id = 1; //right
            arm_update.target_val = RIGHT1_PICK1;
            arm_queue_SendToBack(arm_update);

            arm_update.servo_id = 2; //left
            arm_update.target_val = LEFT1_PICK1;
            arm_queue_SendToBack(arm_update);
        } else if ((((int)(*dis)) > 11) && (((int)(*dis)) < 19)){
            arm_update.servo_id = 1; //right
            arm_update.target_val = RIGHT1_PICK2;
            arm_queue_SendToBack(arm_update);

            arm_update.servo_id = 2; //left
            arm_update.target_val = LEFT1_PICK2;
            arm_queue_SendToBack(arm_update);
        } else if (((int)(*dis)) > 18){
            arm_update.servo_id = 1; //right
            arm_update.target_val = RIGHT1_PICK3;
            arm_queue_SendToBack(arm_update);

            arm_update.servo_id = 2; //left
            arm_update.target_val = LEFT1_PICK3;
            arm_queue_SendToBack(arm_update);
        }
    } else if(((int)(*pick_part)) == 2){
        arm_update.servo_id = 3; //grip
        arm_update.target_val = GRIP_CLOSE;
        arm_queue_SendToBack(arm_update);
    } else if(((int)(*pick_part)) == 3){
        if(((int)(*dis)) < 12){
            arm_update.servo_id = 1; //right
            arm_update.target_val = RIGHT0_PICK1;
            arm_queue_SendToBack(arm_update);

            arm_update.servo_id = 2; //left
            arm_update.target_val = LEFT0_PICK1;
            arm_queue_SendToBack(arm_update);
        } else if ((((int)(*dis)) > 11) && (((int)(*dis)) < 19)){
            arm_update.servo_id = 1; //right
            arm_update.target_val = RIGHT0_PICK2;
            arm_queue_SendToBack(arm_update);

            arm_update.servo_id = 2; //left
            arm_update.target_val = LEFT0_PICK2;
            arm_queue_SendToBack(arm_update);
        } else if (((int)(*dis)) > 18){
            arm_update.servo_id = 1; //right
            arm_update.target_val = RIGHT0_PICK3;
            arm_queue_SendToBack(arm_update);

            arm_update.servo_id = 2; //left
            arm_update.target_val = LEFT0_PICK3;
            arm_queue_SendToBack(arm_update);
        }
    } else if(((int)(*pick_part)) == 4){
        arm_update.servo_id = 1; //right
        arm_update.target_val = RIGHT_BEGIN;
        arm_queue_SendToBack(arm_update);
    } else if(((int)(*pick_part)) == 5){
        arm_update.servo_id = 2; //left
        arm_update.target_val = LEFT_BEGIN;
        arm_queue_SendToBack(arm_update);

        arm_update.servo_id = 0; //base
        arm_update.target_val = BASE_NEUTRAL;
        arm_queue_SendToBack(arm_update);
    } else {}
}


/* *****************************************************************************
 End of File
 */
