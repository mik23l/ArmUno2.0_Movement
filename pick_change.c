/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    pick_change.c

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

#include "pick_change.h"


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
    bool pick_change(int *part, ACTION_TYPE *type, int *done, int *reset_action, uint16_t *dis)

  @Summary
    Brief one-line description of the function.
 */
bool pick_change(int *part, ACTION_TYPE *type, int *done, int *reset_action, uint16_t *dis){
    if(((int)(*part)) == 0){
        if((type->servo_id == 1) || (type->servo_id == 2)){++(*done);} else {}
        if(((int)(*done)) == 2){
            ++(*part);
            *done = 0;
            return true;
        } else {}
    } else if(((int)(*part)) == 1){
        if((type->servo_id == 1) || (type->servo_id == 2)){++(*done);} else {}
        if(((int)(*done)) == 2){
            ++(*part);
            *done = 0;
            return true;
        } else {}
    } else if(((int)(*part)) == 2){
        if(type->servo_id == 3){
            ++(*part);
            return true;
        } else {}
    } else if(((int)(*part)) == 3){
        if((type->servo_id == 1) || (type->servo_id == 2)){++(*done);} else {}
        if(((int)(*done)) == 2){
            ++(*part);
            *done = 0;
            return true;
        } else {}
    } else if(((int)(*part)) == 4){
        if((type->servo_id == 1)){
            ++(*part);
            return true;
        } else {}
    } else if(((int)(*part)) == 5){
        if((type->servo_id == 2)){
            *part = 0;
            *done = 0;
            *reset_action = 0;
            *dis = 0;
            
            Package done_pack;
            done_pack.DataReady = TRUE;
            PackageQueueSendToBack(done_pack,ReceiverQueue);
            return true;
        } else {}
    } else {}
    return false;
}


/* *****************************************************************************
 End of File
 */
