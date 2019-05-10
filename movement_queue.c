/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    movement_queue.c

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

#include "movement_queue.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

QueueHandle_t movement_queue;


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
    void movement_queue_Initialize()

  @Summary
    Initialize movement_queue for sending and receiving.
 */
void movement_queue_Initialize(){
    movement_queue = xQueueCreate(QUEUE_LENGTH, ITEM_SIZE);
    if(movement_queue == NULL){
        //movement_queue was not created
    } else {}
}
 
// *****************************************************************************

/**
  @Function
    void arm_queue_SendToBack(QueueType item)

  @Summary
    Use to send message to movement_queue from task/thread
 */
void movement_queue_SendToBack(QueueType item){
    dbgOutputLoc(TASK_BEFORE_SEND_QUEUE);
    
    if(movement_queue != 0){
        if(xQueueSendToBack(movement_queue, (void*) &item, (TickType_t)portMAX_DELAY) == pdTRUE){
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
    QueueType arm_queue_Receive()

  @Summary
    Used to receive message from movement_queue in task/thread
 */
QueueType movement_queue_Receive(){
    dbgOutputLoc(TASK_BEFORE_RECEIVE_QUEUE);
    
    QueueType tempVal;
    
    if(movement_queue != 0){
        if(xQueueReceive(movement_queue, &(tempVal), (TickType_t)portMAX_DELAY) == pdTRUE){
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
