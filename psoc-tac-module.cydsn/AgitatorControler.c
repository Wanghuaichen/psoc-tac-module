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

#include "AgitatorControler.h"


extern TACModule tacModule[2];


void changeAgitatorSpeed(uint8 percentage, uint8 module)
{
    uint16 maxValue;
    uint16 toWrite;
    
    if(percentage > 100)  percentage = 100;
    if(percentage < 0) percentage = 0;
    
    switch (module)
    {
        case 0:
            maxValue = pwmAgitator_1_ReadPeriod();
            toWrite = (percentage*(maxValue/100));
            pwmAgitator_1_WriteCompare(toWrite);
            break;
        case 1:
            maxValue = pwmAgitator_2_ReadPeriod();
            toWrite = (percentage*(maxValue/100));
            pwmAgitator_2_WriteCompare(toWrite);
            break;
    }
    tacModule[module].agitatorSpeed = percentage;
}


int8 changeAgitatorState(uint8 agitatorEnableState, uint8 module)
{    
    switch (module)
    {
        case 0:
            outputAgitator1_Enable_Write(agitatorEnableState);
            break;
        case 1:
            outputAgitator2_Enable_Write(agitatorEnableState);
            break;
    }
    tacModule[module].agitatorState = agitatorEnableState;
    return 1;
}

/* [] END OF FILE */
