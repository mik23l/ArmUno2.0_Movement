/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    uart_queue.c

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

#include "uart_queue.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

QueueHandle_t Request_Queue;
QueueHandle_t Response_Queue;
QueueHandle_t GetJson_Queue;
QueueHandle_t PutJson_Queue;


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
    void UARTQueueInit();

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
void UARTQueueInit(){
    Request_Queue = NULL;
    Response_Queue = NULL;
    GetJson_Queue = NULL;
    PutJson_Queue = NULL;
    Request_Queue =  xQueueCreate(20, UARTMessageSize);
	if (Request_Queue == 0) {
		dbgOutputError(UART_TQ_BUILD_FAILED);
	}
    Response_Queue =  xQueueCreate(20, UARTMessageSize);
	if (Response_Queue == 0) {
		dbgOutputError(UART_RQ_BUILD_FAILED);
	}
    GetJson_Queue =  xQueueCreate(20, UARTMessageSize);
	if (GetJson_Queue == 0) {
		dbgOutputError(UART_RQ_BUILD_FAILED);
	}
    PutJson_Queue =  xQueueCreate(20, UARTMessageSize);
	if (PutJson_Queue == 0) {
		dbgOutputError(UART_TQ_BUILD_FAILED);
	}
}

// *****************************************************************************

/**
  @Function
    UARTMessage xUARTReceiveFromQueue(QueueHandle_t Queue);

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
UARTMessage xUARTReceiveFromQueue(QueueHandle_t Queue){
	dbgOutputLoc(TASK_BEFORE_RECEIVE_QUEUE);
	UARTMessage pack;
    if(Queue == 0)
    {
        dbgOutputError(Q_POP_FAILED);
    }
    else
    {
        if(xQueueReceive( Queue, &(pack), (TickType_t) portMAX_DELAY) == pdTRUE)
            {
                dbgOutputLoc(TASK_AFTER_RECEIVE_QUEUE);
            }
        else
            {
                dbgOutputError(Q_POP_FAILED);
            }
    }
    return pack;
}

// *****************************************************************************

/**
  @Function
    UARTMessage xUARTQueueReceiveFromISR(QueueHandle_t Queue, BaseType_t *pxHigherPriorityTaskWoken);

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
UARTMessage xUARTQueueReceiveFromISR(QueueHandle_t Queue, BaseType_t *pxHigherPriorityTaskWoken){
    dbgOutputLoc(TASK_BEFORE_RECEIVE_QUEUE);
	UARTMessage pack;
    if(Queue == 0)
    {
        dbgOutputError(Q_POP_FAILED);
    }
    else
    {
        if(xQueueReceiveFromISR( Queue, &(pack), pxHigherPriorityTaskWoken) == pdTRUE)
        {
            dbgOutputLoc(TASK_AFTER_RECEIVE_QUEUE);
        }
        else
        {
            pack = EMPTY_REQUEST;
        }
    }
    return pack;
}

// *****************************************************************************

/**
  @Function
    void xUARTQueueSendToBack(UARTMessage pack, QueueHandle_t Queue)

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
void xUARTQueueSendToBack(UARTMessage pack, QueueHandle_t Queue){
	dbgOutputLoc(TASK_BEFORE_SEND_QUEUE);
    if(Queue == 0)
    {
        dbgOutputError(Q_ADD_FAILED);
    }
    if( xQueueSendToBack( Queue,( void * ) &pack,( TickType_t ) portMAX_DELAY ) != pdTRUE) {
        dbgOutputError(Q_ADD_FAILED);
    }
    else
    {
        dbgOutputLoc(TASK_AFTER_SEND_QUEUE);
    }
}

// *****************************************************************************

/**
  @Function
    void xUARTQueueSendToBackFromISR(UARTMessage pack, QueueHandle_t Queue, BaseType_t *pxHigherPriorityTaskWoken)

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
void xUARTQueueSendToBackFromISR(UARTMessage pack, QueueHandle_t Queue, BaseType_t *pxHigherPriorityTaskWoken){
    dbgOutputLoc(ISR_BEFORE_SEND_QUEUE);
    if(Queue == 0)
    {
        dbgOutputError(Q_ADD_FAILED);
    }
    if(xQueueSendToBackFromISR(Queue, &pack, pxHigherPriorityTaskWoken) == pdTRUE)
        {
            dbgOutputLoc(ISR_AFTER_SEND_QUEUE);
        }
        else
        {
            dbgOutputError(Q_ADD_FAILED);
        }
}

// *****************************************************************************

/**
  @Function
    UARTMessage UARTReceiveFromQueue(QueueName queue);

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
UARTMessage UARTReceiveFromQueue(QueueName queue){
   switch(queue)
    {
        case RequestQueue:
        {
            return xUARTReceiveFromQueue(Request_Queue);
        }
        break;
        case ResponseQueue:
        {
            return xUARTReceiveFromQueue(Response_Queue);
        }
        break;
        case GetJsonQueue:
        {
            return xUARTReceiveFromQueue(GetJson_Queue);
        }
        break;
        case PutJsonQueue:
        {
            return xUARTReceiveFromQueue(PutJson_Queue);
        }
        break;
        default:
        {
            dbgOutputError(WRONG_QUEUE);
        }
    }
}

// *****************************************************************************

/**
  @Function
    void UARTQueueSendToBack(UARTMessage item, QueueName queue);

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
void UARTQueueSendToBack(UARTMessage pack, QueueName queue){
    switch(queue)
    {
        case RequestQueue:
        {
            xUARTQueueSendToBack(pack, Request_Queue);
        }
        break;
        case ResponseQueue:
        {
            xUARTQueueSendToBack(pack, Response_Queue);
        }
        break;
        case GetJsonQueue:
        {
            return xUARTQueueSendToBack(pack, GetJson_Queue);
        }
        break;
        case PutJsonQueue:
        {
            return xUARTQueueSendToBack(pack, PutJson_Queue);
        }
        break;
        default:
        {
            dbgOutputError(WRONG_QUEUE);
        }
    }
}

// *****************************************************************************

/**
  @Function
    UARTMessage UARTQueueReceiveFromISR(QueueName queue, BaseType_t *pxHigherPriorityTaskWoken);

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
UARTMessage UARTQueueReceiveFromISR(QueueName queue, BaseType_t *pxHigherPriorityTaskWoken){
    switch(queue)
    {
        case RequestQueue:
        {
            return xUARTQueueReceiveFromISR(Request_Queue, pxHigherPriorityTaskWoken);
        }
        break;
        case ResponseQueue:
        {
            return xUARTQueueReceiveFromISR(Response_Queue, pxHigherPriorityTaskWoken);
        }
        break;
        case GetJsonQueue:
        {
            return xUARTQueueReceiveFromISR(GetJson_Queue, pxHigherPriorityTaskWoken);
        }
        break;
        case PutJsonQueue:
        {
            return xUARTQueueReceiveFromISR(PutJson_Queue, pxHigherPriorityTaskWoken);
        }
        break;
        default:
        {
            dbgOutputError(WRONG_QUEUE);
        }
    }
}

// *****************************************************************************

/**
  @Function
    void UARTQueueSendToBackFromISR(UARTMessage pack, QueueName queue, BaseType_t *pxHigherPriorityTaskWoken);

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
void UARTQueueSendToBackFromISR(UARTMessage pack, QueueName queue, BaseType_t *pxHigherPriorityTaskWoken){
    switch(queue)
    {
        case RequestQueue:
        {
            xUARTQueueSendToBackFromISR(pack, Request_Queue, pxHigherPriorityTaskWoken);
        }
        break;
        case ResponseQueue:
        {
            xUARTQueueSendToBackFromISR(pack, Response_Queue, pxHigherPriorityTaskWoken);
        }
        break;
        case GetJsonQueue:
        {
            return xUARTQueueSendToBackFromISR(pack, GetJson_Queue, pxHigherPriorityTaskWoken);
        }
        break;
        case PutJsonQueue:
        {
            return xUARTQueueSendToBackFromISR(pack, PutJson_Queue, pxHigherPriorityTaskWoken);
        }
        break;
        default:
        {
            dbgOutputError(WRONG_QUEUE);
        }
    }
}


/* *****************************************************************************
 End of File
 */
