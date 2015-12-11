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

#include "PeltierControler.h"

extern TACModule tacModule[2];


uint8 changePeltierPWMValue(int8 desiredPercentage, uint8 module)
{
    uint16 maxPWMPulse=0; 
    uint16 pwmWriteCompareValue=0;
    
    // Remap desired percentage to available Peltier output control range
    float floatDesiredPercentage = abs(desiredPercentage);
    float percentage = floatDesiredPercentage/100;    
    uint8 remappedPercentage = percentage * (PELTIER_MAX_PWM-PELTIER_MIN_PWM) + PELTIER_MIN_PWM;
    
    if (module == 0)
    {
        maxPWMPulse = Peltier1_PWM_Ctrl_ReadPeriod(); 
        pwmWriteCompareValue = (uint16) remappedPercentage*maxPWMPulse/100;
        Peltier1_PWM_Ctrl_WriteCompare(pwmWriteCompareValue);      
    }
    else if(module == 2)
    {
        maxPWMPulse = Peltier2_PWM_Ctrl_ReadPeriod();
        pwmWriteCompareValue = (uint16)remappedPercentage*maxPWMPulse/100;
        Peltier2_PWM_Ctrl_WriteCompare(pwmWriteCompareValue);
    }
    else
    {
        return 0;
    }

    tacModule[module].actualPwmPercentage = desiredPercentage;
    tacModule[module].pwmPeriodValue = maxPWMPulse;
    tacModule[module].pwmCompareValue = pwmWriteCompareValue;    
    
    return 1;
}


uint8 changePeltierModuleState(uint8 peltierEnableState, uint8 module)
{        
    uint8 actualCtrlRegisterValue = Peltier_Enable_Read();
    uint8 valueToWrite;
    uint8 mask;
    
    if(module == 0)
        mask = PELTIER1_ENABLE_MSK;
    else
        mask = PELTIER2_ENABLE_MSK;
    
    tacModule[module].peltierState = peltierEnableState;
    if (peltierEnableState == 0)
    {
        valueToWrite = (actualCtrlRegisterValue) & (~mask);
    }
    else
    {
        valueToWrite = actualCtrlRegisterValue | mask;
    }
    /*
    switch (module)
    {
        case (1):
        {           
            if (peltierEnableState == 0)
            {
                valueToWrite = (actualCtrlRegisterValue) & (~PELTIER1_ENABLE_MSK);
                SM1.peltierState = peltierDisabled;
            }
            else
            {
                valueToWrite = actualCtrlRegisterValue | PELTIER1_ENABLE_MSK;
                SM1.peltierState = peltierEnabled;
            }
            break;
        }
        case (2):
        {
            if (peltierEnableState == 0)
            {
                valueToWrite = (actualCtrlRegisterValue) & (~PELTIER2_ENABLE_MSK);
                SM2.peltierState = peltierDisabled;
            }
            else
            {
                valueToWrite = actualCtrlRegisterValue | PELTIER2_ENABLE_MSK;
                SM2.peltierState = peltierEnabled;
            }
            break;
        }
        default:
            break;
    }*/
    Peltier_Enable_Write(valueToWrite);
    
    return 1;
}


// Direction should be settled to PELTIER_COOL or PELTIER_HEAT
uint8 changePeltierModuleCurrentDirection(CurrentDirectionType direction,  uint8 module)
{   
    if (direction==Heating || direction==Cooling)
    {   
        tacModule[module].currentDirection = direction;
        if(module == 0)
            Peltier1_Ctrl_Write(direction);
        else
            Peltier2_Ctrl_Write(direction);
        
        return 1;
    }
    else
        return 0;    
    
}

/* [] END OF FILE */
