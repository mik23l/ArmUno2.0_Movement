/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    drop_move.c

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

#include "drop_move.h"


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
    void drop_move()

  @Summary
    Brief one-line description of the function.
 */
void drop_move(){
    ARM_UPDATE arm_update;
    arm_update.stop = FALSE;
    arm_update.update = TRUE;

    arm_update.servo_id = 1; //right
    arm_update.target_val = RIGHT_DROP1;
    arm_queue_SendToBack(arm_update);

    arm_update.servo_id = 2; //left
    arm_update.target_val = LEFT_DROP1;
    arm_queue_SendToBack(arm_update); 
}

// *****************************************************************************

/**
  @Function
    void drop_try1()

  @Summary
    Brief one-line description of the function.
 */
void drop_try1(){
    ARM_UPDATE arm_update;
    arm_update.stop = FALSE;
    arm_update.update = TRUE;

    arm_update.servo_id = 1; //right
    arm_update.target_val = RIGHT_DROP2;
    arm_queue_SendToBack(arm_update);

    arm_update.servo_id = 2; //left
    arm_update.target_val = LEFT_DROP2;
    arm_queue_SendToBack(arm_update); 
}

// *****************************************************************************

/**
  @Function
    void drop_try1()

  @Summary
    Brief one-line description of the function.
 */
void drop_try2(){
    ARM_UPDATE arm_update;
    arm_update.stop = FALSE;
    arm_update.update = TRUE;

    arm_update.servo_id = 1; //right
    arm_update.target_val = RIGHT_DROP3;
    arm_queue_SendToBack(arm_update);

    arm_update.servo_id = 2; //left
    arm_update.target_val = LEFT_DROP3;
    arm_queue_SendToBack(arm_update); 
}

// *****************************************************************************

/**
  @Function
    void drop_try3()

  @Summary
    Brief one-line description of the function.
 */
void drop_try3(){
    ARM_UPDATE arm_update;
    arm_update.stop = FALSE;
    arm_update.update = TRUE;

    arm_update.servo_id = 1; //right
    arm_update.target_val = RIGHT_BEGIN;
    arm_queue_SendToBack(arm_update);

    arm_update.servo_id = 0; //base
    arm_update.target_val = 2600;
    arm_queue_SendToBack(arm_update); 
}

// *****************************************************************************

/**
  @Function
    void drop_try4()

  @Summary
    Brief one-line description of the function.
 */
void drop_try4(){
    ARM_UPDATE arm_update;
    arm_update.stop = FALSE;
    arm_update.update = TRUE;

    arm_update.servo_id = 1; //right
    arm_update.target_val = RIGHT_BEGIN;
    arm_queue_SendToBack(arm_update);

    arm_update.servo_id = 0; //base
    arm_update.target_val = 4600;
    arm_queue_SendToBack(arm_update); 
}

// *****************************************************************************

/**
  @Function
    void finish_move(int *drop_part)

  @Summary
    Brief one-line description of the function.
 */
void finish_move(int *drop_part){
    ARM_UPDATE arm_update;
    arm_update.stop = FALSE;
    arm_update.update = TRUE;
    
    if(((int)(*drop_part)) == 0){
        arm_update.servo_id = 3; //grip
        arm_update.target_val = GRIP_OPEN;
        arm_queue_SendToBack(arm_update);
    } else if(((int)(*drop_part)) == 1){
        arm_update.servo_id = 1; //right
        arm_update.target_val = RIGHT_BEGIN;
        arm_queue_SendToBack(arm_update);       
        
        arm_update.servo_id = 0; //base
        arm_update.target_val = BASE_NEUTRAL;
        arm_queue_SendToBack(arm_update);
    } else if (((int)(*drop_part)) == 2){
        arm_update.servo_id = 2; //left
        arm_update.target_val = LEFT_BEGIN;
        arm_queue_SendToBack(arm_update);
    }
}


/* *****************************************************************************
 End of File
 */
