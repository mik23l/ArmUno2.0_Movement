/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    debug.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DEBUG_H    /* Guard against multiple inclusion */
#define _DEBUG_H


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
#include "peripheral/usart/plib_usart.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

// Baud Rate defines
#define FP 80000000
#define BAUDRATE 9600
#define BRGVAL ((FP/BAUDRATE)/16)-1

// Location Codes
#define DLOC_UART_ISR_BEGIN         35
#define ENTER_ARM_TASK              1
#define ENTER_FIND_TASK             2
#define ENTER_MOVEMENT_TASK         3
#define ENTER_RECEIVE_TASK          4
#define ENTER_SEND_TASK             5
#define ENTER_RECEIVER_TASK         28
#define TASK_BEFORE_LOOP            6
#define TASK_BEFORE_SEND_QUEUE      7
#define TASK_AFTER_SEND_QUEUE       8
#define TASK_BEFORE_RECEIVE_QUEUE   9
#define TASK_AFTER_RECEIVE_QUEUE    10
#define ENTER_ISR                   11
#define LEAVE_ISR                   12
#define ISR_BEFORE_SEND_QUEUE       13
#define ISR_AFTER_SEND_QUEUE        14
#define ISR_BEFORE_RECEIVE_QUEUE    15
#define ISR_AFTER_RECEIVE_QUEUE     16
#define BEFORE_UART_READ            31
#define AFTER_UART_READ             32
#define BEFORE_UART_WRITE           33
#define AFTER_UART_WRITE            34

// Error Codes
#define DBG_VAL_TOO_LARGE       20
#define Q_BUILD_FAILED          21
#define Q_ADD_FAILED            22
#define Q_POP_FAILED            23
#define UART_ERROR              24
#define UART_RQ_BUILD_FAILED    25
#define UART_TQ_BUILD_FAILED    26
#define WRONG_QUEUE             27
#define HTTP_RECEIVE_ERROR      29
#define JSON_PARSE_FAILED       30
#define ERROR_DOC_NAME          36
#define PACK_TO_JSON_FAIL       37
#define OBJECT_NOT_FOUND        38
#define SERVERLOG_FAIL          39
#define SYSTEM_STOP             99

#define LOW_BITS        0xFF
#define BIT_MASK        0x7F
#define LED_BLINK       0x08
#define LED_BLINK_ON    1000000
#define LED_BLINK_OFF   500000
    
#define EMPTY_REQUEST 0xfe

// Suppress warnings
#define _SUPPRESS_PLIB_WARNING


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
        int ExampleFunctionName ( int param1, int param2 ) 

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
    void debug_Initialize();
    
    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

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
    void dbgOutputVal(unsigned int outVal);
    
    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

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
    void dbgUARTVal(unsigned char outVal);
    
    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

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
    void dbgOutputLoc(unsigned int outVal);
    
    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

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
    void dbgOutputError(unsigned int errorCode);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DEBUG_H */

/* *****************************************************************************
 End of File
 */
