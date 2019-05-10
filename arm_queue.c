/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    arm_queue.c

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

#include "arm_queue.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

QueueHandle_t arm_queueA;


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
    void arm_queue_Initialize()

  @Summary
    Initialize arm_queueA and arm_queueB for sending and receiving.
 */
void arm_queue_Initialize(){
    arm_queueA = xQueueCreate(QUEUE_LENGTH, ITEM_SIZEA);
    if(arm_queueA == NULL){
        //arm_queueA was not created
    } else {}
}

// *****************************************************************************

/**
  @Function
    void arm_queue_SendToBack(QueueTypeA item)

  @Summary
    Use to send message to arm_queueA from task/thread
 */
void arm_queue_SendToBack(QueueTypeA item){
    dbgOutputLoc(TASK_BEFORE_SEND_QUEUE);
    
    if(arm_queueA != 0){
        if(xQueueSendToBack(arm_queueA, (void*) &item, (TickType_t)portMAX_DELAY) == pdTRUE){
           dbgOutputLoc(TASK_AFTER_SEND_QUEUE);
        } else {
            //failed to send message 
        }
    } else {
        //failed to send message
    }    
}

// *****************************************************************************

/**
  @Function
    void arm_queue_SendToBackFromISR(QueueTypeA *pos)

  @Summary
    Use to send message to arm_queueA from ISR
 */
void arm_queue_SendToBackFromISR(QueueTypeA *pos){
    dbgOutputLoc(ISR_BEFORE_SEND_QUEUE);
    
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    
    if(arm_queueA != 0){
        if(xQueueSendToBackFromISR(arm_queueA, pos, &pxHigherPriorityTaskWoken) == pdTRUE){
           dbgOutputLoc(ISR_AFTER_SEND_QUEUE);
        } else {
            //failed to send message 
        }
    } else {
        //failed to send message
    }    
}

// *****************************************************************************

/**
  @Function
    QueueTypeA arm_queue_Receive()

  @Summary
    Used to receive message from arm_queueA in task/thread
 */
QueueTypeA arm_queue_Receive(){
    dbgOutputLoc(TASK_BEFORE_RECEIVE_QUEUE);
    
    QueueTypeA tempVal;
    
    if(arm_queueA != 0){
        if(xQueueReceive(arm_queueA, &(tempVal), (TickType_t)portMAX_DELAY) == pdTRUE){
           dbgOutputLoc(TASK_AFTER_RECEIVE_QUEUE);
        } else {
            //failed to receive message 
        }
    } else {
        //failed to receive message
    }   
    
    return tempVal;
}


/* *****************************************************************************
 End of File
 */
