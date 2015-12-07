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
#include <PeltierCalibration.h>
double targetTemp;          // variable containing TAC target temperature
cystatus eepromStatus;
static const uint8 eepromArray[(5*CALIBRATION_TABLE_SIZE)] = {0};
// The calibration tables are organized like so : LSB first -> [3*i] = LSB, [3*i+1] = MSB, [3*i+2]=percentage
static const uint8 SM1eepromArray[(3*CALIBRATION_TABLE_SIZE)] = {0};
static const uint8 SM2eepromArray[(3*CALIBRATION_TABLE_SIZE)] = {0};




void validateEEPROM(int subModuleId)
{
    int i;
    
    if (subModuleId == SubModule1_ID)
    {
        for (i=0; i<10; i++)
        {
            if (SM1calibrationValues[i] != 0)
            {            
                Blue_LED_Write(1u);
                CyDelay(300);
                Blue_LED_Write(0u);
                CyDelay(300); 
            }
        }
    }
    else if(subModuleId == SubModule2_ID)
    {
        for (i=0; i<10; i++)
        {
            if (SM2calibrationValues[i] != 0)
            {            
                Blue_LED_Write(1u);
                CyDelay(300);
                Blue_LED_Write(0u);
                CyDelay(300); 
            }
        }  
    }

    CyDelay(1000);
}

//* Used to read calibration table from EEPROM */
//Return 1 if data is present in the calibration table in the EEPROM, 0 otherwise.
boolean getCalibrationTable(Tac_Submodule* TACPtr)
{
    int i=0;
    
    if (TACPtr->subModuleId == SubModule1_ID)
    {
        volatile const uint8* array1 = (volatile uint8 *) &SM1eepromArray[0]; // array1 devrait pointer vers le début des bits dans l'EEPROM
        for(i = 0; i<CALIBRATION_TABLE_SIZE; i++)
        {
            SM1calibrationValues[i] = (int16)((array1[(3*i)+1] << 8) | array1[(3*i)]); 
            SM1percentageValues[i] = (int8)array1[3*i+2]; 
        }
    }
    else if (TACPtr->subModuleId == SubModule2_ID)
    {
        volatile const uint8* array1 = (volatile uint8 *) &SM2eepromArray[0]; // array1 devrait pointer vers le début des bits dans l'EEPROM
        for(i = 0; i<CALIBRATION_TABLE_SIZE; i++)
        {
            SM2calibrationValues[i] = (int16)((array1[(3*i)+1] << 8) | array1[(3*i)]);
            SM2percentageValues[i] = (int8)array1[3*i+2]; 
        }   
    }  
    // If the 3 first values from the EEPROM are null, the calibration was never done.
    if ((TACPtr->calibrationValuesPtr[0] == 0) && (TACPtr->calibrationValuesPtr[1] == 0) && (TACPtr->calibrationValuesPtr[2] == 0))
    {
        TACPtr->areCalibrationValuesRetrieved = False;
        return 0;
    }
    else
    {
        TACPtr->areCalibrationValuesRetrieved = True;
        return 1;
    }
    /*
    volatile const uint8* array1 = (volatile uint8 *) &eepromArray[0]; // array1 devrait pointer vers le début des bits dans l'EEPROM
   
    int i=0;
    for(i = 0; i<CALIBRATION_TABLE_SIZE; i++)
    {       
        SM1calibrationValues[i] = (int)(array1[(5*i)+3] << 24) | (array1[(5*i)+2] << 16) | (array1[(5*i)+1] << 8) | array1[(5*i)];
        SM1percentageValues[i] = (int8)array1[5*i+4];
    }
    
    // If the two first values from the EEPROM are null, the calibration was never done.
    if ((SM1calibrationValues[0] == 0) & (SM1calibrationValues[1] == 0))
        return 0;
    else
        return 1;  
    */
}
//* Used to set calibration table from EEPROM */
void setCalibrationTable(Tac_Submodule* TACPtr)
{    
    int i = 0;
    uint8_t *array1;
    
    uint8 tempTemperatureAndPercentageArray[3*CALIBRATION_TABLE_SIZE] = {0}; // 4 bytes of temperature datas, 1 byte for corresponding percentage.
    
    if (TACPtr->subModuleId == SubModule1_ID)
    {
        for(i=0; i<CALIBRATION_TABLE_SIZE; i++)
        {
            array1 = (uint8_t*)(&SM1calibrationValues[i]);
            tempTemperatureAndPercentageArray[3*i] = array1[0];     // LSB
            tempTemperatureAndPercentageArray[(3*i)+1] = array1[1]; // MSB
            tempTemperatureAndPercentageArray[(3*i)+2] = (uint8)SM1percentageValues[i]; // Storing a byte to indicate the corresponding % of PWM
        }
        eepromStatus = Em_EEPROM_Write(&tempTemperatureAndPercentageArray[0], &SM1eepromArray[0], 3*CALIBRATION_TABLE_SIZE);
        }
    else if (TACPtr->subModuleId == SubModule2_ID)
    {
        for(i=0; i<CALIBRATION_TABLE_SIZE; i++)
        {
            array1 = (uint8_t*)(&SM2calibrationValues[i]);
            tempTemperatureAndPercentageArray[3*i] = array1[0];     // LSB
            tempTemperatureAndPercentageArray[(3*i)+1] = array1[1]; // MSB
            tempTemperatureAndPercentageArray[(3*i)+2] = (uint8)SM1percentageValues[i]; // Storing a byte to indicate the corresponding % of PWM
        } 
        eepromStatus = Em_EEPROM_Write(&tempTemperatureAndPercentageArray[0], &SM2eepromArray[0], 3*CALIBRATION_TABLE_SIZE);
    }
   
    /*
    int i = 0;
    uint8_t *array1;
    
    uint8 tempTemperatureAndPercentageArray[5*CALIBRATION_TABLE_SIZE] = {0}; // 4 bytes of temperature datas, 1 byte for corresponding percentage.
    
    for(i=0; i<CALIBRATION_TABLE_SIZE; i++)
    {
        array1 = (uint8_t*)(&SM1calibrationValues[i]);
        tempTemperatureAndPercentageArray[5*i] = array1[0];     // LSB
        tempTemperatureAndPercentageArray[(5*i)+1] = array1[1]; 
        tempTemperatureAndPercentageArray[(5*i)+2] = array1[2];
        tempTemperatureAndPercentageArray[(5*i)+3] = array1[3]; // MSB
        tempTemperatureAndPercentageArray[(5*i)+4] = (uint8)SM1percentageValues[i]; // Storing a byte to indicate the corresponding % of PWM
    }	
	eepromStatus = Em_EEPROM_Write(&tempTemperatureAndPercentageArray[0], &eepromArray[0], 5*CALIBRATION_TABLE_SIZE);
    */
}

uint8 calibration(Tac_Submodule* TACPtr)
{
    if (TACPtr->subModuleId==SubModule1_ID || TACPtr->subModuleId==SubModule2_ID)
    {
        // Set the fan to 100%
        // Wait for temperature to be stable (ambiant temperature) with no Peltier output
        // Start by cooling, from the lowest PWM value to the highest
        // Register all values
        // Put the Peltier off and wait for return to ambiant temperature
        // Start heating slowly then increment the PWM gradually registering all values at the same time        
        
        // Set the fan to 100%
        changeFanSpeed(100,TACPtr->subModuleId);
        changeFanState(fanEnabled, TACPtr->subModuleId);
        
        // Make sure that the Peltier element is not active :
        changePeltierModuleState(peltierDisabled, TACPtr->subModuleId); // Signal inH_1 and inH_2 high to enable Peltier driver 1.
        
        // Wait for temperature to be stable (ambiant temperature)
        int16 ambientTemperature = getStableTemp(TACPtr);

                
        // Initialize range of PWM percentage to be used :
        int8 pwmStartValue = PELTIER_PWM_INCREMENT_VALUE;
        int8 pwmEndValue = BEST_COOLING_PWM_PERCENTAGE;
        int pwmPercentageIncrement = (int)PELTIER_PWM_INCREMENT_VALUE;
        int pwmPercentageBeeingSent = pwmStartValue;
        
        // Placing the Peltier in cooling mode :
        changePeltierModuleCurrentDirection(Cooling, TACPtr);
        changePeltierModuleState(peltierEnabled, TACPtr->subModuleId);
        
        int32 calibrationValueCount = 0;
        int16 currentTemp = 0;
        
        int numberOfCoolingDatas = (pwmEndValue-pwmStartValue)/pwmPercentageIncrement + 1;
        
        int16 tempTable[CALIBRATION_TABLE_SIZE];
        
        // Start by cooling, from the lowest PWM value to the highest
        int i;
        for (i=numberOfCoolingDatas-1; i>-1; i--)
        {               
            if (STOP_CALIBRATION_FLAG != 0)
            {
                STOP_CALIBRATION_FLAG = 0;
                return CALIBRATION_STOPPED;
            }
            
            // Modify the desired PWM value.
            changePeltierPWMValue(pwmPercentageBeeingSent, TACPtr->subModuleId);
            currentTemp = getStableTemp(TACPtr);
            
            // Save calibration values in table.
            TACPtr->calibrationValuesPtr[i] = currentTemp;
            TACPtr->percentageValuesPtr[i] = pwmPercentageBeeingSent;

    		//Preparing the next value to send to the PWM to respect the % increment.
    		pwmPercentageBeeingSent += pwmPercentageIncrement;
        }       
        
        // Put the Peltier off and wait for return to ambiant temperature
        changePeltierModuleState(peltierDisabled, TACPtr->subModuleId);
        TACPtr->calibrationValuesPtr[numberOfCoolingDatas] = getStableTemp(TACPtr);
        TACPtr->percentageValuesPtr[numberOfCoolingDatas] = 0;        
        
        // Initialize range of PWM percentage to be used :
        pwmStartValue = PELTIER_PWM_INCREMENT_VALUE;
        pwmEndValue = BEST_HEATING_PWM_PERCENTAGE;
        pwmPercentageBeeingSent = pwmStartValue;
        
        changePeltierModuleCurrentDirection(Heating, TACPtr);
        changePeltierModuleState(peltierEnabled, TACPtr->subModuleId);
        
        // Start heating slowly then increment the PWM gradually registering all values at the same time
        for (i=numberOfCoolingDatas+1; i<CALIBRATION_TABLE_SIZE; i++)
        {
            if (STOP_CALIBRATION_FLAG != 0)
            {
                STOP_CALIBRATION_FLAG = 0;
                return CALIBRATION_STOPPED;
            }
            
            if (TACPtr->currentTemperature < TACPtr->maxTargetTemperature)
            {
                // Modify the desired PWM value.
                changePeltierPWMValue(pwmPercentageBeeingSent, TACPtr->subModuleId);
                currentTemp = getStableTemp(TACPtr);
                
                // Save calibration values in table.
                TACPtr->calibrationValuesPtr[i] = currentTemp;
                TACPtr->percentageValuesPtr[i] = pwmPercentageBeeingSent;

        		//Preparing the next value to send to the PWM to respect the % increment.
        		pwmPercentageBeeingSent += pwmPercentageIncrement;
            }
            else
            {
                break;
            }
        }
        changePeltierModuleState(peltierDisabled,TACPtr->subModuleId); // Sets Signal inH_1 and inH_2 of Peltier Module 1 to 0.  
        setCalibrationTable(TACPtr);
        return 1;        
    }
    else
    {
        // If not using the sub module 1 nor 2, tell it to the master as I don't know where we are heading with all this.
        return BAD_SUBMODULE_NUMBER;
    }
}
int16 getStableTemp(Tac_Submodule* TACPtr)
{
    int16 currentTemp = 0;
    int16 pastTemp = 0;
    int8 tolerance_hit = 0;     // Will contain the number of times a reading was +- tolerance from past reading
    int16 deltaValue = 0; 
    
    while(tolerance_hit < NB_STABLE_VALUE_REQUIRED && currentTemp <= TACPtr->maxTargetTemperature)
    {                
        if (STOP_CALIBRATION_FLAG != 0)
        {
            STOP_CALIBRATION_FLAG = 0;
            return CALIBRATION_STOPPED;
        }   
        
         // Partie température
        currentTemp = getThermistorTemp(TACPtr);
        deltaValue = abs(currentTemp - pastTemp);        
        
        // Ajout Kevin
        if (deltaValue < TEMP_TOLERANCE)
        {
            tolerance_hit ++;
        }
        else
        {
            tolerance_hit = 0;
            pastTemp = currentTemp;
        }
          
        CyDelay(CY_DELAY_MS_FOR_STABLE_TEMP);    // CRUCIAL: Wait before reading next temperature    
    }
    
    return currentTemp;
}



/*===========================================================================*/
// Should not be called directly, will be called by "controlTemperature" function
void peltierControl(int function, int diff, uint8 moduleNumber, int targetTemperature)
{
    Tac_Submodule* TacPtr;
    
    if (moduleNumber == SubModule1_ID)
    {
        TacPtr = &SM1;        
    }
    else if(moduleNumber == SubModule2_ID)
    {
        TacPtr = &SM2;
    }
    double controlValue;
    if(function == PELTIER_COOL )
    {
        //double controlValue = (0.3+((0.000625*pow(diff,2))/3.08))*480; // Calculated from desired ramp
        if(diff>10)
        {
            controlValue = 300;
        }
        else
        {
           controlValue = ((4*diff)/0.595)+132; // See excel for reference ramp 
        }        
        int val = (int)controlValue;
        
        // Deactivate the desired Peltier Element.
        changePeltierModuleState(0,moduleNumber); 
        
        // changes PWM value, affecting Peltier's power
        if (moduleNumber == 1)
        {
            Peltier1_PWM_Ctrl_WriteCompare(val);
        }
        else if (moduleNumber == 2)
        {
            Peltier2_PWM_Ctrl_WriteCompare(val);
        }
        
        // Sets the H_bridge to heat or cool depending on the parameter passed
        changePeltierModuleCurrentDirection(function, TacPtr);
        
        // Reactivate the desired Peltier Element.
        changePeltierModuleState(1,TacPtr->subModuleId);
        
        //Peltier_on_Write(0u);   // deactivates peltier element
        //LED_Write(0u);          
        //peltierPWM_WriteCompare(val);       // changes PWM value, affecting Peltier's power
        //peltier_control_Write(function);    // Sets the H_bridge to heat or cool depending on the parameter passed
        ////peltierPWM_Start();
        //Peltier_on_Write(1u);   // Signal inH_1 and inH_2   
    }
    else if(function ==  PELTIER_HEAT)
    {
        //double controlValue = (0.3+((0.000625*pow(diff,2))/2))*480; // Calculated from desired ramp
        if(diff>20)
        {
            controlValue = 384;
        }
        else
        {
           controlValue = ((4*diff)/0.396)+132; // See excel for reference ramp 
        } 
        int val = (int)controlValue;
        
        // Deactivate the desired Peltier Element.
        changePeltierModuleState(0,TacPtr->subModuleId); 
        
        // changes PWM value, affecting Peltier's power
        if (TacPtr->subModuleId == 1)
        {
            Peltier1_PWM_Ctrl_WriteCompare(val);
        }
        else if (TacPtr->subModuleId == 2)
        {
            Peltier2_PWM_Ctrl_WriteCompare(val);
        }
        
        // Sets the H_bridge to heat or cool depending on the parameter passed
        changePeltierModuleCurrentDirection(function, TacPtr);
        
        // Reactivate the desired Peltier Element.
        changePeltierModuleState(1,TacPtr->subModuleId);
        
        //Peltier_on_Write(0u);
        //peltierPWM_WriteCompare(val);
        //peltier_control_Write(function);    // Sets the H_bridge to heat or cool depending on the parameter passed
        ////peltierPWM_Start();
        //Peltier_on_Write(1u);   // Signal inH_1 and inH_2        
    }    
    else if(function == PELTIER_MAINTAIN)   // Never called
    {
        // Deactivate the desired Peltier Element.
        changePeltierModuleState(0,moduleNumber);
        
        if (targetTemperature>25)
        {
            // Sets the H_bridge to heat or cool depending on the parameter passed
            changePeltierModuleCurrentDirection(PELTIER_HEAT, TacPtr);
        }
        else
        {
            // Sets the H_bridge to heat or cool depending on the parameter passed
            changePeltierModuleCurrentDirection(PELTIER_COOL, TacPtr);            
        } 
        
        // changes PWM value, affecting Peltier's power
        if (moduleNumber == 1)
        {
            Peltier1_PWM_Ctrl_WriteCompare(100);
        }
        else if (moduleNumber == 2)
        {
            Peltier2_PWM_Ctrl_WriteCompare(100);
        }
        
        // Reactivate the desired Peltier Element.
        changePeltierModuleState(1,moduleNumber);
        
        /*
        if(targetTemp > 25) // need to apply heat to maintain temperature
        {
            Peltier_on_Write(0u);   // Signal inH_1 and inH_2 
            peltier_control_Write(PELTIER_HEAT);    // Sets the H_bridge to heat or cool depending on the parameter passed
            peltierPWM_WriteCompare(100);   // TODO Calculate this value in function of targetTemp
            Peltier_on_Write(1u);   // Signal inH_1 and inH_2 
        }
        else    // Need to cool 
        {
            Peltier_on_Write(0u);   // Signal inH_1 and inH_2 
            peltier_control_Write(PELTIER_COOL);    // Sets the H_bridge to heat or cool depending on the parameter passed
            peltierPWM_WriteCompare(100); 
            Peltier_on_Write(1u);   // Signal inH_1 and inH_2 
        }*/
    }
}

// Fan functions section





// Agitator functions section


// Peltier functions section




uint8 updateSMPeriodValue()
{    
    SM1.pwmPeriodValue = Peltier1_PWM_Ctrl_ReadPeriod();
    SM2.pwmPeriodValue = Peltier2_PWM_Ctrl_ReadPeriod();

    return 1;
}

void testPWMPeriods()
{
    uint32 desiredFreq = 0; // In KHz.
    uint16 desiredPeriod = 0;
    uint16 actualPeriod = 0;
    
    for (desiredFreq=60000; desiredFreq<80000; desiredFreq+=2000)
    {
        actualPeriod = Peltier1_PWM_Ctrl_ReadPeriod();
        desiredPeriod = 24000000/desiredFreq; //2400/desiredFreq;
        Peltier1_PWM_Ctrl_WritePeriod(desiredPeriod);
        changePeltierPWMValue(80,SM1.subModuleId);
        CyDelay(10000);        
    }
}


/* [] END OF FILE */
