/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    uart_queue.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _UART_QUEUE_H    /* Guard against multiple inclusion */
#define _UART_QUEUE_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdbool.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"
#include "variable_define.h"


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
    void UARTQueueInit();

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
    UARTMessage UARTReceiveFromQueue(QueueName queue);
    
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
    void UARTQueueSendToBack(UARTMessage item, QueueName queue);
    
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
    UARTMessage UARTQueueReceiveFromISR(QueueName queue, BaseType_t *pxHigherPriorityTaskWoken);
    
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
    void UARTQueueSendToBackFromISR(UARTMessage pack, QueueName queue, BaseType_t *pxHigherPriorityTaskWoken);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _UART_QUEUE_H */

/* *****************************************************************************
 End of File
 */
