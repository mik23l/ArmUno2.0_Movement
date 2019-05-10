/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    check_target.c

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

#include "check_target.h"


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
    void check_target(uint32_t *right, uint32_t *left, uint32_t *grip, ARM_UPDATE *right_, ARM_UPDATE *left_, ARM_UPDATE *grip_, ARM_UPDATE *new_target)

  @Summary
    Brief one-line description of the function.
 */
bool check_target(uint32_t *right, uint32_t *left, uint32_t *grip, ARM_UPDATE *right_, ARM_UPDATE *left_, ARM_UPDATE *grip_, ARM_UPDATE *new_target){
    switch(new_target->servo_id)
    {
        case 0:
            return false;
            break;
        case 1:
            if((right_->current_val != right_->target_val) && (right_->target_val != new_target->target_val)){
                right = new_target->target_val;
                return true;
            } else {}
            break;
        case 2:
            if(left_->target_val != new_target->target_val){
                left = new_target->target_val;
                return true;
            } else {}
            break;
        case 3:
            if(grip_->target_val != new_target->target_val){
                grip = new_target->target_val;
                return true;
            } else {}
            break;
        default:
            dbgOutputError(SYSTEM_STOP);
            break;
    }
}


/* *****************************************************************************
 End of File
 */
