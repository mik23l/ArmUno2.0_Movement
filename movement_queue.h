/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    movement_queue.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _MOVEMENT_QUEUE_H    /* Guard against multiple inclusion */
#define _MOVEMENT_QUEUE_H


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
#define ITEM_SIZE      sizeof(QueueType)


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    typedef struct{
        bool ready;
        int action_type;
        bool done;
        int servo_id;
        uint16_t distance;
    }ACTION_TYPE;

    typedef ACTION_TYPE QueueType;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************


    // *****************************************************************************
    /**
      @Function
        void movement_queue_Initialize()

      @Summary
        Initialize movement_queue for sending and receiving.
     */
    void movement_queue_Initialize();
    
    // *****************************************************************************
    /**
      @Function
        void arm_queue_SendToBack(QueueType item)

      @Summary
        Use to send message to movement_queue from task/thread
     */
    void movement_queue_SendToBack(QueueType item);
    
    // *****************************************************************************
    /**
      @Function
        QueueType arm_queue_Receive()

      @Summary
        Used to receive message from movement_queue in task/thread
     */
    QueueType movement_queue_Receive();


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MOVEMENT_QUEUE_H */

/* *****************************************************************************
 End of File
 */
