/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    find_queue.c

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

#include "find_queue.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

QueueHandle_t find_queueA;


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
    int ExampleFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.
 */
void find_queue_Initialize(){
	find_queueA = NULL;
    find_queueA = xQueueCreate(10, sizeof(uint16_t));
    if(find_queueA == 0){
        //find_queueA was not created
    } else {}
}

// *****************************************************************************

/**
  @Function
    void find_queue_SendToBackFromISR()

  @Summary
    Use to send message to arm_queueA from ISR
 */
void find_queue_SendToBackFromISR(uint16_t dis, BaseType_t *pxHigherPriorityTaskWoken){
    dbgOutputLoc(ISR_BEFORE_SEND_QUEUE);
    if(find_queueA == 0) {
        dbgOutputError(Q_ADD_FAILED);
    }
    if(xQueueSendToBackFromISR(find_queueA, &dis, pxHigherPriorityTaskWoken) == pdTRUE) {
		dbgOutputLoc(ISR_AFTER_SEND_QUEUE);
	}
	else {
		dbgOutputError(Q_ADD_FAILED);
	}   
}

// *****************************************************************************

/**
  @Function
    void find_queue_SendToBack(uint16_t dis)

  @Summary
    Use to send message to arm_queueA from ISR
 */
void find_queue_SendToBack(uint16_t dis){
    dbgOutputLoc(TASK_BEFORE_SEND_QUEUE);
    
    if(find_queueA != 0){
        if(xQueueSendToBack(find_queueA, (void*) &dis, (TickType_t)portMAX_DELAY) == pdTRUE){
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
    QueueTypeA find_queue_Receive()

  @Summary
    Used to receive message from arm_queueA in task/thread
 */
uint16_t find_queue_Receive(){
    dbgOutputLoc(TASK_BEFORE_RECEIVE_QUEUE);
	
    uint16_t result;
    
    if(find_queueA == 0) {
        dbgOutputError(Q_POP_FAILED);
    }
    else {
        if(xQueueReceive( find_queueA, &(result), (TickType_t) portMAX_DELAY) == pdTRUE) {
            dbgOutputLoc(TASK_AFTER_RECEIVE_QUEUE);
        }
        else {
            dbgOutputError(Q_POP_FAILED);
        }
    }
    return result;
}


/* *****************************************************************************
 End of File
 */
