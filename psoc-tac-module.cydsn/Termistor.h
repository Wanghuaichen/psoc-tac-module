/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef __TERMISTOR_H__
#define __TERMISTOR_H__
    
#include <project.h>
#include <Defines.h>
    
/**
 * This function simplifies temperature reading from thermistor
 * by controlling ADC and AMux usage accordingly
 */
int16 getThermistorTemp(uint8 module);

int16 getArrayMean(int16* tab, int16 size);

#endif

/* [] END OF FILE */
