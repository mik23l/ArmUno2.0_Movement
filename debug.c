/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    debug.c

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

#include "debug.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */



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
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void debug_Initialize(void) {
    //Open the UART0 channel for message transfer
    PLIB_USART_BaudRateSet(USART_ID_1, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), 9600);
    PLIB_USART_Enable (USART_ID_1);
    PLIB_USART_TransmitterEnable (USART_ID_1);

    // Initialize Port E for output
    TRISECLR = LOW_BITS;
    PORTECLR = LOW_BITS;
    
    // Initialize Port D for output
    TRISDCLR = LOW_BITS;
    PORTDCLR = LOW_BITS;
    
    // Initialize Port A for led blink
    TRISACLR = LED_BLINK;
    PORTACLR = LED_BLINK;
}

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Output state value to Port E

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void dbgOutputVal(unsigned int outVal) {
    if(outVal > 127) {
        dbgOutputError(DBG_VAL_TOO_LARGE);
    }
    else {
        // Bit-wise and outVal mask and port bits
        unsigned int mask = BIT_MASK & outVal;
        
        // Show outVal on pins
        PORTESET = mask;
        
        // Toggle 8th pin and clear port
        PORTESET = 0x80 | mask;
        PORTECLR = LOW_BITS;
    }
}

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Sends data through TX0 on UART0.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void dbgUARTVal(unsigned char outVal) {
    
    PLIB_USART_TransmitterByteSend (USART_ID_1, outVal);

}

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Output location value to Port D.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void dbgOutputLoc(unsigned int outVal) {
    if(outVal > 127) {
        dbgOutputError(DBG_VAL_TOO_LARGE);
    }
    else {
        // Bit-wise and outVal mask and port bits
        unsigned int mask = BIT_MASK & outVal;
        
        // Show outVal on pins
        PORTDSET = mask;
        
        // Toggle 8th pin and clear port
        PORTDSET = 0x80 | mask;
        PORTDCLR = LOW_BITS;
    }
} 

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Output Error code to the line and flash LED.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void dbgOutputError(unsigned int errorCode) {
    taskDISABLE_INTERRUPTS()
    int count = 0;
    while(1) {
        if(count == LED_BLINK_ON) {
            // Turn LED on
            PORTASET = LED_BLINK; 
            count = 0;
        }
        else if(count == LED_BLINK_OFF) {
            // Turn LED off
            PORTACLR = LED_BLINK;
        }   
         
        dbgOutputVal(errorCode);
        count++;
    }
}


/* *****************************************************************************
 End of File
 */
