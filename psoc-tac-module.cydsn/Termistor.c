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
#include "Termistor.h"

extern TACModule tacModule[2];

/*===========================================================================*/
// TODO: Adapt function to select which thermistor we want to read and to modify SM1 or SM2 current temperature.
// Returns temperature * 10. (Ex. real value = 1.5 -> returns 15 degrees celsius)
int16 getThermistorTemp(uint8 module)
{    
    /* Find temperature in Celsius degree using the component API */
    /*int16 temperature = (Thermistor_1_GetTemperature(Thermistor_1_GetResistance(MeasureResistorVoltage(AMUX_1_VREF), MeasureResistorVoltage(AMUX_1_VT))))/10;
    */
    int32 iVtherm, iVref;
    uint32 iRes, iRes_ext;
    int32 currentReading = 0;
    int16 vRef, vTherm;
    
    
    /* Read voltage across thermistor */             
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    vTherm = ADC_CountsTo_mVolts(ADC_GetResult32()); 
    vRef = VDDA*1000-vTherm;
    
    /* Find temperature in Celsius degree using the component API */
    iRes = Thermistor_1_GetResistance(vRef, vTherm);
    currentReading = Thermistor_1_GetTemperature(iRes);
               
    int16 tempToSave = currentReading/10;

    tacModule[module].currentTemperature = tempToSave; 
    
    return tempToSave;
}


int16 getArrayMean(int16* tab, int16 size)
{
    int i = 0;
    int mean = 0;
    for(i = 0; i < size; i++)
    {
        mean += tab[i];
    }
    mean = mean/size;
    return mean; // Multiplication par 10 pour ne pas dépasser les limites du int16
}




/* [] END OF FILE */
