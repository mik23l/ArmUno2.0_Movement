/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    package_queue.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _PACKAGE_QUEUE_H    /* Guard against multiple inclusion */
#define _PACKAGE_QUEUE_H


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
    void PackageInit(Package *pack, DataSource source);
    
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
    void PackageQueueInit();
    
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
    Package PackageReceiveFromQueue(QueueName queue);
    
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
    void PackageQueueSendToBack(Package item, QueueName queue);
    
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
    Package PackageQueueReceiveFromISR(QueueName queue, BaseType_t *pxHigherPriorityTaskWoken);
    
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
    void PackageQueueSendToBackFromISR(Package pack, QueueName queue, BaseType_t *pxHigherPriorityTaskWoken);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _PACKAGE_QUEUE_H */

/* *****************************************************************************
 End of File
 */
