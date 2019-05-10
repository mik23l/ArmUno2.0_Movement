/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    arm_queue.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _ARM_QUEUE_H    /* Guard against multiple inclusion */
#define _ARM_QUEUE_H


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

#define FALSE           0
#define TRUE            1
#define QUEUE_LENGTH    10
#define ITEM_SIZEA      sizeof(QueueTypeA)


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    typedef struct{
        bool update;
        bool stop;
        uint32_t target_val;
        int servo_id;
        uint32_t current_val;
    }ARM_UPDATE;

    typedef ARM_UPDATE QueueTypeA;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************


    // *****************************************************************************
    /**
      @Function
        void arm_queue_Initialize()

      @Summary
        Initialize arm_queueA and arm_queueB for sending and receiving.
     */
    void arm_queue_Initialize();
    
    // *****************************************************************************
    /**
      @Function
        void arm_queue_SendToBack(QueueTypeA item)

      @Summary
        Use to send message to arm_queueA from task/thread
     */
    void arm_queue_SendToBack(QueueTypeA item);
    
    // *****************************************************************************
    /**
      @Function
        void arm_queue_SendToBackFromISR()

      @Summary
        Use to send message to arm_queueA from ISR
     */
    void arm_queue_SendToBackFromISR(QueueTypeA *pos);
    
    // *****************************************************************************
    /**
      @Function
        QueueTypeA arm_queue_Receive()

      @Summary
        Used to receive message from arm_queueA in task/thread
     */
    QueueTypeA arm_queue_Receive();


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _ARM_QUEUE_H */

/* *****************************************************************************
 End of File
 */
