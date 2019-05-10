/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    servo_compare.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _SERVO_COMPARE_H    /* Guard against multiple inclusion */
#define _SERVO_COMPARE_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "arm_queue.h"
#include "peripheral/oc/plib_oc.h"
#include "peripheral/int/plib_int.h"
#include "pwm.h"
#include "movement_queue.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */



    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************



    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************


    // *****************************************************************************
    /**
      @Function
        void target_change_base(ARM_UPDATE *servo);

      @Summary
        Update the servo motors to target position.
     */
    void servo_compare_base(ARM_UPDATE *servo);
    
    // *****************************************************************************
    /**
      @Function
        void target_change_base(ARM_UPDATE *servo);

      @Summary
        Update the servo motors to target position.
     */
    void servo_compare_right(ARM_UPDATE *servo);
    
    // *****************************************************************************
    /**
      @Function
        void target_change_base(ARM_UPDATE *servo);

      @Summary
        Update the servo motors to target position.
     */
    void servo_compare_left(ARM_UPDATE *servo);
    
    // *****************************************************************************
    /**
      @Function
        void target_change_base(ARM_UPDATE *servo);

      @Summary
        Update the servo motors to target position.
     */
    void servo_compare_grip(ARM_UPDATE *servo);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SERVO_COMPARE_H */

/* *****************************************************************************
 End of File
 */
