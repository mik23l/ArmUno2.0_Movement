/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    adc_interface.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _ADC_INTERFACE_H    /* Guard against multiple inclusion */
#define _ADC_INTERFACE_H


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
#include "variable_define.h"
#include "debug.h"
#include "find_queue.h"
#include "package_queue.h"


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
        void ADCReadData(BaseType_t *pxHigherPriorityTaskWoken);

      @Summary
        Brief one-line description of the function.
     */
    void ADCReadData(BaseType_t *pxHigherPriorityTaskWoken);
    
    // *****************************************************************************
    /**
      @Function
        uint16_t RangeConversion(uint16_t *value);

      @Summary
        Brief one-line description of the function.
     */
    uint16_t RangeConversion(uint16_t *value);
    
    // *****************************************************************************
    /**
      @Function
        void ADCTriggerSample();

      @Summary
        Brief one-line description of the function.
     */
    void ADCTriggerSample();   


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _ADC_INTERFACE_H */

/* *****************************************************************************
 End of File
 */
