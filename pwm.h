/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    pwm.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _PWM_H    /* Guard against multiple inclusion */
#define _PWM_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "system/common/sys_common.h"
#include "peripheral/oc/plib_oc.h"
#include "peripheral/int/plib_int.h"
#include "debug.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

#define DRV_OC_Open(drvIndex, intent) (drvIndex)
#define DRV_OC_Close(handle)
    
#define BASE_LEFT       6100
#define BASE_NEUTRAL    3650
#define BASE_RIGHT      1500
#define RIGHT_OUT       6100
#define RIGHT_NEUTRAL   3750
#define RIGHT_IN        2250
#define RIGHT_BEGIN     3500
#define LEFT_UP         5000
#define LEFT_NEUTRAL    3500
#define LEFT_DOWN       2300
#define LEFT_BEGIN      2600
#define GRIP_OPEN       6000
#define GRIP_NEUTRAL    4000
#define GRIP_CLOSE      4350
#define GRIP_MIN        3750

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
        int ExampleFunctionName ( int param1, int param2 ) 

      @Summary
        Brief one-line description of the function.

      @Description
        Full description, explaining the purpose and usage of the function.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
     */
    void PWM_Initialize();
    
    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

      @Summary
        Brief one-line description of the function.

      @Description
        Full description, explaining the purpose and usage of the function.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
     */
    void PWM_Start();
    
    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

      @Summary
        Brief one-line description of the function.

      @Description
        Full description, explaining the purpose and usage of the function.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
     */
    void PWM_Stop();


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _PWM_H */

/* *****************************************************************************
 End of File
 */
