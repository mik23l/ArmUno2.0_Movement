/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    find_queue.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _FIND_QUEUE_H    /* Guard against multiple inclusion */
#define _FIND_QUEUE_H


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
#include "FreeRTOS.h"
#include "queue.h"
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
     */
    void find_queue_Initialize();
    
    // *****************************************************************************
    /**
      @Function
        void find_queue_SendToBackFromISR(uint16_t dis, BaseType_t *pxHigherPriorityTaskWoken)

      @Summary
        Use to send message to arm_queueA from ISR
     */
    void find_queue_SendToBackFromISR(uint16_t dis, BaseType_t *pxHigherPriorityTaskWoken);
    
    // *****************************************************************************
    /**
      @Function
        void find_queue_SendToBack(uint16_t dis)

      @Summary
        Use to send message to arm_queueA from ISR
     */
    void find_queue_SendToBack(uint16_t dis);
    
    // *****************************************************************************
    /**
      @Function
        QueueTypeA find_queue_Receive()

      @Summary
        Used to receive message from arm_queueA in task/thread
     */
    uint16_t find_queue_Receive();


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _FIND_QUEUE_H */

/* *****************************************************************************
 End of File
 */
