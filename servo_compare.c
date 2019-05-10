/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    servo_compare.c

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

#include "servo_compare.h"


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
    void target_change_base(ARM_UPDATE *servo);

  @Summary
    Update the servo motors to target position.
 */
void servo_compare_base(ARM_UPDATE *servo){
    int diff; 
    diff = servo->current_val - servo->target_val;
    if((abs(diff) < 10)){
        PLIB_OC_PulseWidth16BitSet(OC_ID_1, (uint16_t)servo->target_val);
        servo->current_val = servo->target_val; 
    } else if(diff < 0){
        uint32_t new_val = (servo->current_val) + 10;
        PLIB_OC_PulseWidth16BitSet(OC_ID_1, (uint16_t)new_val);
        servo->current_val = new_val;
    } else if(diff > 0){
        uint32_t new_val = (servo->current_val) - 10;
        PLIB_OC_PulseWidth16BitSet(OC_ID_1, (uint16_t)new_val);
        servo->current_val = new_val;
    } else {} 
}

// *****************************************************************************

/**
  @Function
    void target_change_right(ARM_UPDATE *servo);

  @Summary
    Update the servo motors to target position.
 */
void servo_compare_right(ARM_UPDATE *servo){
    int diff; 
    diff = servo->current_val - servo->target_val;
    if((abs(diff) < 40)){
        PLIB_OC_PulseWidth16BitSet(OC_ID_2, (uint16_t)servo->target_val);
        servo->current_val = servo->target_val;
    } else if(diff < 0){
        uint32_t new_val = (servo->current_val) + 40;
        PLIB_OC_PulseWidth16BitSet(OC_ID_2, (uint16_t)new_val);
        servo->current_val = new_val;
    } else if(diff > 0){
        uint32_t new_val = (servo->current_val) - 40;
        PLIB_OC_PulseWidth16BitSet(OC_ID_2, (uint16_t)new_val);
        servo->current_val = new_val;
    } else {} 
}

// *****************************************************************************

/**
  @Function
    void target_change_left(ARM_UPDATE *servo);

  @Summary
    Update the servo motors to target position.
 */
void servo_compare_left(ARM_UPDATE *servo){
    int diff; 
    diff = servo->current_val - servo->target_val;
    if((abs(diff) < 40)){
        PLIB_OC_PulseWidth16BitSet(OC_ID_3, (uint16_t)servo->target_val);
        servo->current_val = servo->target_val;
    } else if(diff < 0){
        uint32_t new_val = (servo->current_val) + 40;
        PLIB_OC_PulseWidth16BitSet(OC_ID_3, (uint16_t)new_val);
        servo->current_val = new_val;
    } else if(diff > 0){
        uint32_t new_val = (servo->current_val) - 40;
        PLIB_OC_PulseWidth16BitSet(OC_ID_3, (uint16_t)new_val);
        servo->current_val = new_val;
    } else {} 
}

// *****************************************************************************

/**
  @Function
    void target_change_grip(ARM_UPDATE *servo);

  @Summary
    Update the servo motors to target position.
 */
void servo_compare_grip(ARM_UPDATE *servo){
    int diff; 
    diff = servo->current_val - servo->target_val;
     if((abs(diff) < 55)){
        PLIB_OC_PulseWidth16BitSet(OC_ID_4, (uint16_t)servo->target_val);
        servo->current_val = servo->target_val;
    } else if(diff < 0){
        uint32_t new_val = (servo->current_val) + 55;
        PLIB_OC_PulseWidth16BitSet(OC_ID_4, (uint16_t)new_val);
        servo->current_val = new_val;
    } else if(diff > 0){
        uint32_t new_val = (servo->current_val) - 55;
        PLIB_OC_PulseWidth16BitSet(OC_ID_4, (uint16_t)new_val);
        servo->current_val = new_val;
    } else {}
}


/* *****************************************************************************
 End of File
 */
