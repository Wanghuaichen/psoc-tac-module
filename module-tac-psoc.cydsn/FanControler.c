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

#include "FanControler.h"


extern TACModule tacModule[2];


void changeFanSpeed(uint8 desiredPercentage, uint8 module)
{
    uint8 maxValue;
    uint8 toWrite;
    
    if(desiredPercentage > 2)
    {
        switch (module)
        {
            case (0):
                maxValue = pwmFan_1_ReadPeriod();
                toWrite = (desiredPercentage*(maxValue/100));
                pwmFan_1_WriteCompare(toWrite);
                break; 
            case (1):
                maxValue = pwmFan_2_ReadPeriod();
                toWrite = (desiredPercentage*(maxValue/100));
                pwmFan_2_WriteCompare(toWrite);
                break;
        }
    }
    tacModule[module].fanSpeedPercentage = desiredPercentage;
}


int8 changeFanState(uint8 fanEnableState, uint8 module)
{
    switch (module)
    {
        case (0):
            fanPeltier1_Enable_Write(fanEnableState);            
            break;
        case (1):
            fanPeltier2_Enable_Write(fanEnableState);
            break;
    }
    
    tacModule[module].fanState = fanEnableState;
    return 1;
}


/* [] END OF FILE */
