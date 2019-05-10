/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    pwm.c

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

#include "pwm.h"


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
void PWM_Initialize() {
    DRV_TMR0_Initialize();
    
    //DRV_OC0_Initialize(); 
    /* Setup OC0 Instance */
    PLIB_OC_ModeSelect(OC_ID_1, OC_COMPARE_PWM_MODE_WITHOUT_FAULT_PROTECTION);
    PLIB_OC_BufferSizeSelect(OC_ID_1, OC_BUFFER_SIZE_16BIT);
    PLIB_OC_TimerSelect(OC_ID_1, OC_TIMER_16BIT_TMR2);
    PLIB_OC_Buffer16BitSet(OC_ID_1, 0);
    PLIB_OC_PulseWidth16BitSet(OC_ID_1, BASE_NEUTRAL);
    
    //DRV_OC1_Initialize();
    /* Setup OC0 Instance */
    PLIB_OC_ModeSelect(OC_ID_2, OC_COMPARE_PWM_MODE_WITHOUT_FAULT_PROTECTION);
    PLIB_OC_BufferSizeSelect(OC_ID_2, OC_BUFFER_SIZE_16BIT);
    PLIB_OC_TimerSelect(OC_ID_2, OC_TIMER_16BIT_TMR2);
    PLIB_OC_Buffer16BitSet(OC_ID_2, 0);
    PLIB_OC_PulseWidth16BitSet(OC_ID_2, RIGHT_BEGIN);
    
    //DRV_OC2_Initialize();
    /* Setup OC0 Instance */
    PLIB_OC_ModeSelect(OC_ID_3, OC_COMPARE_PWM_MODE_WITHOUT_FAULT_PROTECTION);
    PLIB_OC_BufferSizeSelect(OC_ID_3, OC_BUFFER_SIZE_16BIT);
    PLIB_OC_TimerSelect(OC_ID_3, OC_TIMER_16BIT_TMR2);
    PLIB_OC_Buffer16BitSet(OC_ID_3, 0);
    PLIB_OC_PulseWidth16BitSet(OC_ID_3, LEFT_BEGIN);
    
    //DRV_OC3_Initialize();
    /* Setup OC0 Instance */
    PLIB_OC_ModeSelect(OC_ID_4, OC_COMPARE_PWM_MODE_WITHOUT_FAULT_PROTECTION);
    PLIB_OC_BufferSizeSelect(OC_ID_4, OC_BUFFER_SIZE_16BIT);
    PLIB_OC_TimerSelect(OC_ID_4, OC_TIMER_16BIT_TMR2);
    PLIB_OC_Buffer16BitSet(OC_ID_4, 0);
    PLIB_OC_PulseWidth16BitSet(OC_ID_4, GRIP_OPEN);
}

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void PWM_Start() {
    DRV_TMR0_Start(); //Start timer2
    PLIB_OC_Enable(OC_ID_1); //Start OC0
    PLIB_OC_Enable(OC_ID_2); //Start OC1
    PLIB_OC_Enable(OC_ID_3); //Start OC2
    PLIB_OC_Enable(OC_ID_4); //Start OC3
}

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void PWM_Stop() {
    DRV_TMR0_Stop(); //Stop timer2
    PLIB_OC_Disable(OC_ID_1); //Stop OC0
    PLIB_OC_Disable(OC_ID_2); //Stop OC1
    PLIB_OC_Disable(OC_ID_3); //Stop OC2
    PLIB_OC_Disable(OC_ID_4); //Stop OC3
}


/* *****************************************************************************
 End of File
 */
