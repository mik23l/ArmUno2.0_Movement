/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    adc_interface.c

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

#include "adc_interface.h"


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
    void ADCReadData(BaseType_t *pxHigherPriorityTaskWoken);

  @Summary
    Brief one-line description of the function.
 */
void ADCReadData(BaseType_t *pxHigherPriorityTaskWoken){
    uint16_t result = 0;
    uint16_t i;
    
    for(i =0; i != ADC_NUM_SAMPLE_PER_AVERAGE; ++i)
    {
        result += PLIB_ADC_ResultGetByIndex(ADC_ID_1, i); 
    }
    
    //divided by ADC_NUM_SAMPLE_PER_AVERAGE and precision set
    result = result >> 4;
    //conversion
    result = RangeConversion(&result);
    
    dbgOutputVal(result);
    
    find_queue_SendToBackFromISR(result, pxHigherPriorityTaskWoken);
}

// *****************************************************************************

/**
  @Function
    uint16_t RangeConversion(uint16_t *value);

  @Summary
    Brief one-line description of the function.
 */
uint16_t RangeConversion(uint16_t *value){
    uint16_t result = 255;
    uint16_t lut[13] = {841, 622, 465, 400, 329, 280, 249, 230, 188, 184, 163, 159, 141};
    uint16_t highBound = 0;
    uint16_t lowBound = 0;
    int x;
    if(*value > lut[0])
    {
        result = 4;
    }
    else if(*value < lut[12])
    {
        result =  28;
    }
    else
    {
        int temp = 0;
        for(x = 1; x != sizeof(lut); ++x)
        {
            if(*value > lut[x])
            {
                highBound = lut[x - 1];
                lowBound = lut[x];
                temp = x;
                break;
            }
        }
        int slope = (highBound - lowBound)/2;
        int constant = lowBound + (temp * 2 + 4) * slope;
        result = (constant - *value) / slope;
    }
    return result;
}

// *****************************************************************************

/**
  @Function
    void ADCTriggerSample();

  @Summary
    Brief one-line description of the function.
 */
void ADCTriggerSample(){
    PLIB_ADC_SampleAutoStartEnable(DRV_ADC_ID_1);
}


/* *****************************************************************************
 End of File
 */
