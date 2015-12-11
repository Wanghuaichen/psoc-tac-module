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
#include "TAC_Submodule.h"
#include "PeltierCalibration.h"



void updatePeltierOutput(Tac_Submodule* TACPtr, double CycleTime)//, int16 currentTemp)
{
    // Updates current temperature of the Peltier element by reading the corresponding thermistor.
    TACPtr->currentTemperature = getThermistorTemp(TACPtr);   
    
    //Filling Error and error tab
    int16 tempErr = TACPtr->targetTemperature-TACPtr->currentTemperature;
    double diffErr=0;
    double intErr=0;
    if (*TACPtr->errorTabCounter>=NB_OF_ACC_ERROR)
    {
        *TACPtr->errorTabCounter=0;
    }

    TACPtr->errorTabPtr[*TACPtr->errorTabCounter]=tempErr;
    
    if (*TACPtr->errorTabCounter==0)
    {
        diffErr=(tempErr-TACPtr->errorTabPtr[NB_OF_ACC_ERROR-1])/CycleTime;
    }
    else
    {
        diffErr=(tempErr-TACPtr->errorTabPtr[*TACPtr->errorTabCounter-1])/CycleTime;
    }
    *TACPtr->errorTabCounter+=1;
    intErr=getArraySum(&TACPtr->errorTabPtr[0], NB_OF_ACC_ERROR);
    
    
    
    
    
    // If the module is in waiting mode and the peltier is still on, we shut it off.
    if (TACPtr->temperatureMode == Waiting && TACPtr->peltierState == peltierEnabled)
    {
        changePeltierModuleState(peltierDisabled,TACPtr->subModuleId);
    }
    // Else, if the module is not in waiting mode but the peltier is off, we put it on.
    else if (TACPtr->temperatureMode != Waiting && TACPtr->peltierState == peltierDisabled)
    {
        changePeltierModuleState(peltierEnabled,TACPtr->subModuleId);
    }
    
    double PID_Result = P*tempErr+I*intErr+D*diffErr;
     
    
    // Verify if the user asked to stop temperature maintain Or temperature is between tolerance
    //  If not, go ahead with temperature control
    if (TACPtr->temperatureMode!= Waiting && (tempErr>TEMP_TOLERANCE || tempErr<-TEMP_TOLERANCE))
    { 
        // If we are in temperature control mode, we make sure the fan runs at 100% of its speed.
        if (TACPtr->fanState != fanEnabled || TACPtr->fanSpeedPercentage != 100)
        {
            changeFanState(fanEnabled, TACPtr->subModuleId);
            changeFanSpeed(100,TACPtr->subModuleId);
        } 
        // Heating
        if(PID_Result>0)
        {
            // Make sure that the direction of the current is set to heat
            if(TACPtr->currentDirection != Heating)
            {
                TACPtr->temperatureMode = Maintaining_heat;
                changePeltierModuleCurrentDirection(Heating, TACPtr);                
            }  
            if(PID_Result>=BEST_HEATING_PWM_PERCENTAGE)
            {
                changePeltierPWMValue(BEST_HEATING_PWM_PERCENTAGE,TACPtr->subModuleId);
            }
            else
            {
                changePeltierPWMValue(PID_Result,TACPtr->subModuleId);
            }               
        }
        //Cooling
        else
        {
            //Compensate for the power difference betwwen heating and cooling
            PID_Result= PID_Result*3;
            // Make sure that the direction of the current is set to cool
            if(TACPtr->currentDirection != Cooling)
            {
                TACPtr->temperatureMode = Maintaining_cool;
                changePeltierModuleCurrentDirection(Cooling, TACPtr);                
            }  
            if(PID_Result<=-BEST_COOLING_PWM_PERCENTAGE)
            {
                changePeltierPWMValue(BEST_COOLING_PWM_PERCENTAGE,TACPtr->subModuleId);
            }
            else
            {
                changePeltierPWMValue(-PID_Result,TACPtr->subModuleId);
            } 
        }
    }
    // Switch peltier to wait overshoot
    else
    {
        TACPtr->temperatureMode = Waiting_overshoot;
        changePeltierModuleState(peltierDisabled,TACPtr->subModuleId);
    }
    
   
}

void updatePwmValueFromCalibrationTable(Tac_Submodule* TACPtr)
{
    boolean goodToGo = TACPtr->areCalibrationValuesRetrieved;
    
    // Make sure to get the datas from the calibration table before starting :
    if (goodToGo == False && TACPtr->areCalibrationValuesAvailable == True)
    {
        goodToGo = getCalibrationTable(TACPtr);            
    }    
    
    if (goodToGo == True)
    {
        int x = 0;
        int bestMatchIndex;
        
        int diffFromTarget = 0;
        int precedingDiffFromTarget = 10000000;
        
        int indexWhenOver = 0;
        
        for (x=0; x<CALIBRATION_TABLE_SIZE; x++)
        {
            if (TACPtr->calibrationValuesPtr[x] > TACPtr->targetTemperature)
            {
                indexWhenOver = x;
                break;
            }
        }
        
        double diffWithPrecedentValue = TACPtr->targetTemperature - TACPtr->calibrationValuesPtr[indexWhenOver-1];
        double ratio = diffWithPrecedentValue/(TACPtr->calibrationValuesPtr[indexWhenOver] - TACPtr->calibrationValuesPtr[indexWhenOver-1]);
        double percentageToSaveDouble = TACPtr->percentageValuesPtr[indexWhenOver-1] + ratio*(TACPtr->percentageValuesPtr[indexWhenOver] - TACPtr->percentageValuesPtr[indexWhenOver-1]);
        
        if (percentageToSaveDouble<0)
        {
            TACPtr->temperatureMode = Maintaining_cool;
            changePeltierModuleCurrentDirection(Cooling, TACPtr);
        }
        else
        {
            TACPtr->temperatureMode = Maintaining_heat;
            changePeltierModuleCurrentDirection(Heating, TACPtr);
        }        
        
        uint8 percentageToSave = abs((int8)percentageToSaveDouble);  
        TACPtr->desiredPwmPercentage = percentageToSave;
        TACPtr->pwmValueFromCalibration = UpToDate;
        
    }
}

boolean areCalibrationValuesAvailable(Tac_Submodule* TACPtr)
{
    int i;
    int mean;
    int sum = 0;
    
    for (i=0; i<10; i++)
    {        
        sum += TACPtr->calibrationValuesPtr[i];        
    }
    mean = sum/10;
    
    if (mean==0)
    {
        TACPtr->areCalibrationValuesAvailable = False;
        return False;
    }
    else
    {
        TACPtr->areCalibrationValuesAvailable = True;
        return True;
    }
}

// Returns the mean value of all data found in "tab"

double getArraySum(int16* tab, int16 size)
{
    int i = 0;
    double sum = 0;
    for(i = 0; i < size; i++)
    {
        sum += tab[i];
    }
    return sum; 
}




/* [] END OF FILE */
