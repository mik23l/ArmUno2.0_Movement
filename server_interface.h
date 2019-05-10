/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    server_interface.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _SERVER_INTERFACE_H    /* Guard against multiple inclusion */
#define _SERVER_INTERFACE_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "system_config.h"
#include "system_definitions.h"
#include "string.h"
#include "variable_define.h"
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
        void ServerInitialize();

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
    void ServerInitialize();
    
    // *****************************************************************************
    /**
      @Function
        UARTMessage ReadResponse();

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
    UARTMessage ReadResponse();
    
    // *****************************************************************************
    /**
      @Function
        void GetResponse(BaseType_t *pxHigherPriorityTaskWoken);

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
    void GetResponse(BaseType_t *pxHigherPriorityTaskWoken);
    
    // *****************************************************************************
    /**
      @Function
        void SendRequest(BaseType_t *pxHigherPriorityTaskWoken);

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
    void SendRequest(BaseType_t *pxHigherPriorityTaskWoken);
    
    // *****************************************************************************
    /**
      @Function
        void WriteRequest(RequestType type, DocumentName document, const Package *pack);

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
    void WriteRequest(RequestType type, DocumentName document, const Package *pack);
    
    // *****************************************************************************
    /**
      @Function
        uint32_t MakeCheckSum(const char *String, size_t len);

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
    uint32_t MakeCheckSum(const char *String, size_t len);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SERVER_INTERFACE_H */

/* *****************************************************************************
 End of File
 */
