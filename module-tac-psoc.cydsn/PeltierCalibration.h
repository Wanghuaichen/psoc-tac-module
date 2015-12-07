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
#include <project.h>
#include "measurement.h"
#include "Defines.h"
#include "CAN_Communication.h"
#include "TAC_Submodule.h"
#include "ComputerCommunication.h"

extern int16 SM1calibrationValues[CALIBRATION_TABLE_SIZE]; // used to test eeprom read/write operations
extern uint8 SM1percentageValues[CALIBRATION_TABLE_SIZE];
extern int16 SM2calibrationValues[CALIBRATION_TABLE_SIZE]; // used to test eeprom read/write operations
extern uint8 SM2percentageValues[CALIBRATION_TABLE_SIZE];

cystatus testWritingInEEPROM();

//* Used to read calibration table from EEPROM
//Return 1 if data is present in the calibration table in the EEPROM, 0 otherwise.*/
boolean getCalibrationTable(Tac_Submodule* TACPtr);

//* Used to set calibration table from EEPROM */
void setCalibrationTable(Tac_Submodule* TACPtr); //(int32* temperatureSourceArray, int8* percentageSourceArray);


// Used to validate that the EEPROM is working correctly.
void validateEEPROM();

/**
 * Used to calibrate TAC for Voltage - Temperature
 * correspondence. Creates a voltage/temperature
 * table
 *
 * FR: Permet d'effectuer une calibration quant à la 
 *   correspondance entre une température à une 
 *   tension donnée, créer un tableau Voltage/Température
 */
uint8 calibration(Tac_Submodule* TACPtr);

/**
 * Used to calculate the mean value from past temperature readings
 */
//int16 getArrayMean(int16* tab, int16 size);

/**
* Control the H-Bridge connected to the Peltier elements
*   @param function represents what the peltier should do, heat, cool, or stop
*   @param diff value between 0 and 100 corresponding to the ratio of power to output for the Motor/Peltier
*   which corresponds to 25 to 75% of duty cycle for the dev board.
*/
void peltierControl(int function, int diff, uint8 moduleNumber, int targetTemperature);
/**
 * Simply used to determine if we need to heat or cool depending
 * on the actual temperature vs target temperature
 *   @param actualTemperature Used to compare against targetTemp
 */
void controlTemperature(float actualTemperature, uint8 moduleNumber, int16 targetTemperature);

/**
 * Set the temperature target for TAC module
 *  @param temp: the target temperature, in Degrees C 
 */
void setTargetTemperature(double temp);

/**
 * Change TAC's fan speed
 * @param percentage: Pretty self-explanatory, will be mapped to actual PWM compare value
 */
//void changeFanSpeed(uint8 percentage, uint8 moduleNumber);
//uint8 getFanSpeed(uint8 moduleNumber);
//int8 changeFanState(uint8 fanEnableState, uint8 moduleNumber);

/**
 * Change agitator motor speed
 * @param percentage: Pretty self-explanatory, will be mapped to actual PWM compare value
 */
void changeAgitatorSpeed(uint8 percentage, uint8 moduleNumber);
uint8 getAgitatorSpeed(uint8 moduleNumber);
int8 changeAgitatorState(uint8 agitatorEnableState, uint8 moduleNumber);

//uint8 changePeltierPWMValue(int8 desiredPercentage, uint8 subModuleID);
uint8 updateSMPeriodValue();

//typedef enum {COOL, HEAT} Current_Direction_enum;

//uint8 changePeltierModuleState(uint8 peltierEnableState, uint8 moduleNumber);
//uint8 changePeltierModuleCurrentDirection(uint8 Direction, uint8 moduleNumber);
//uint8 changePeltierModuleCurrentDirection(currentDirection_type Direction, uint8 moduleNumber);
//uint8 changePeltierModuleCurrentDirection(currentDirection_type Direction, Tac_Submodule* TACPtr);
int16 getStableTemp(Tac_Submodule* TACPtr);

void testPWMPeriods();

int16 getTemperature(uint8 moduleNumber);

/*
 *  Loads eeprom calibration values into ram
 */
void loadEepromCalibrationValues();

/* [] END OF FILE */

