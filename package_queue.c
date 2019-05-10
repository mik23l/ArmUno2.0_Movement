/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    package_queue.c

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

#include "package_queue.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

QueueHandle_t Receiver_Queue;
QueueHandle_t Sender_Queue;
QueueHandle_t DataInter_Queue;


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
    void PackageInit(Package *pack, DataSource source);

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
void PackageInit(Package *pack, DataSource source){
    pack -> ADC10 = 0;
    pack -> ADC20 = 0;
    pack -> ADCUnit = centimeter;
    pack -> Item = Unknown;
    pack -> ArmStatus = unknown_state;
    pack -> RoverStatus = unknown_status;
    pack -> KitchenTable = 0;
    pack -> TableOne = 0;
    pack -> TableTwo = 0;
    pack -> TableThree = 0;
    pack -> ItemColor = 0;
    pack -> ReadType = unknown_type;
    pack -> Source = source;
    pack -> DataReady = false;
    pack -> CorrectResponse = 0;
    pack -> BadResponse = 0;
    pack -> MissedResponse = 0;
    pack -> RequestSent = 0;
    pack -> SequenceNumber = 0;
}

// *****************************************************************************

/**
  @Function
    void PackageQueueInit();

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
void PackageQueueInit(){
    Receiver_Queue = NULL;
	Receiver_Queue =  xQueueCreate(10, PackageSize);
	if (Receiver_Queue == 0) {
		dbgOutputError(Q_BUILD_FAILED);
	}
    Sender_Queue = NULL;
	Sender_Queue =  xQueueCreate(10, PackageSize);
	if (Sender_Queue == 0) {
		dbgOutputError(Q_BUILD_FAILED);
	}
    DataInter_Queue = NULL;
	DataInter_Queue =  xQueueCreate(10, PackageSize);
	if (DataInter_Queue == 0) {
		dbgOutputError(Q_BUILD_FAILED);
	}
}

// *****************************************************************************

/**
  @Function
    Package xPackageReceiveFromQueue(QueueHandle_t Queue)

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
Package xPackageReceiveFromQueue(QueueHandle_t Queue)
{
	dbgOutputLoc(TASK_BEFORE_RECEIVE_QUEUE);
	Package pack;
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

/**
  @Function
    Package xPackageQueueReceiveFromISR(QueueHandle_t Queue, BaseType_t *pxHigherPriorityTaskWoken)

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
Package xPackageQueueReceiveFromISR(QueueHandle_t Queue, BaseType_t *pxHigherPriorityTaskWoken)
{
    dbgOutputLoc(TASK_BEFORE_RECEIVE_QUEUE);
	Package pack;
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
            if(Queue != DataInter_Queue)
            {
                dbgOutputError(Q_POP_FAILED);
            }
            else
            {
                pack.ArmStatus = unknown_state;
                pack.Source = Board;
                pack.DataReady = false;
            }
        }
    }
    return pack;
}

/**
  @Function
    void xPackageQueueSendToBack(Package pack, QueueHandle_t Queue)

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
void xPackageQueueSendToBack(Package pack, QueueHandle_t Queue)
{
	dbgOutputLoc(TASK_BEFORE_SEND_QUEUE);
    if(Queue == 0)
    {
        dbgOutputError(Q_ADD_FAILED);
    }
    if( xQueueSendToBack( Queue,( void * ) &pack,( TickType_t ) portMAX_DELAY ) != pdTRUE) 
    {
        dbgOutputError(Q_ADD_FAILED);
    }
    else
    {
        dbgOutputLoc(TASK_AFTER_SEND_QUEUE);
    }
}

/**
  @Function
    void xPackageQueueSendToBackFromISR(Package pack, QueueHandle_t Queue, BaseType_t *pxHigherPriorityTaskWoken)

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
void xPackageQueueSendToBackFromISR(Package pack, QueueHandle_t Queue, BaseType_t *pxHigherPriorityTaskWoken)
{
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
    Package PackageReceiveFromQueue(QueueName queue);

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
Package PackageReceiveFromQueue(QueueName queue){
    switch(queue)
    {
        case ReceiverQueue:
        {
            return xPackageReceiveFromQueue(Receiver_Queue);
        }
        break;
        case SenderQueue:
        {
            return xPackageReceiveFromQueue(Sender_Queue);
        }
        break;
        case DataInterQueue:
        {
            return xPackageReceiveFromQueue(DataInter_Queue);
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
    void PackageQueueSendToBack(Package item, QueueName queue);

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
void PackageQueueSendToBack(Package pack, QueueName queue){
    switch(queue)
    {
        case ReceiverQueue:
        {
            xPackageQueueSendToBack(pack, Receiver_Queue);
        }
        break;
        case SenderQueue:
        {
            xPackageQueueSendToBack(pack, Sender_Queue);
        }
        break;
        case DataInterQueue:
        {
            xPackageQueueSendToBack(pack, DataInter_Queue);
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
    Package PackageQueueReceiveFromISR(QueueName queue, BaseType_t *pxHigherPriorityTaskWoken);

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
Package PackageQueueReceiveFromISR(QueueName queue, BaseType_t *pxHigherPriorityTaskWoken){
    switch(queue)
    {
        case ReceiverQueue:
        {
            return xPackageQueueReceiveFromISR(Receiver_Queue, pxHigherPriorityTaskWoken);
        }
        break;
        case SenderQueue:
        {
            return xPackageQueueReceiveFromISR(Sender_Queue, pxHigherPriorityTaskWoken);
        }
        break;
        case DataInterQueue:
        {
            return xPackageQueueReceiveFromISR(DataInter_Queue, pxHigherPriorityTaskWoken);
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
    void PackageQueueSendToBackFromISR(Package pack, QueueName queue, BaseType_t *pxHigherPriorityTaskWoken);

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
void PackageQueueSendToBackFromISR(Package pack, QueueName queue, BaseType_t *pxHigherPriorityTaskWoken){
    switch(queue)
    {
        case ReceiverQueue:
        {
            xPackageQueueSendToBackFromISR(pack, Receiver_Queue, pxHigherPriorityTaskWoken);
        }
        break;
        case SenderQueue:
        {
            xPackageQueueSendToBackFromISR(pack, Sender_Queue, pxHigherPriorityTaskWoken);
        }
        break;
        case DataInterQueue:
        {
            xPackageQueueSendToBackFromISR(pack, DataInter_Queue, pxHigherPriorityTaskWoken);
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
