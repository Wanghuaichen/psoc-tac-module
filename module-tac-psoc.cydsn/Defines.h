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
#ifndef ___DEFINES_H___
#define ___DEFINES_H___

#include <project.h>
#include <CyLib.h>

//Device ID
#define DEVICE_ID                           (0x00)  // Unique ID for the device on the platform (to change between different devices)
#define HARDWARE_CAN_ID                      0x70   // HARDWARE FILTER ID
    
// Variables specific to the TAC Module
#define TEMP_CONTROL_P_FACTOR		        (8u)	// Used to adjust setpoint curve
#define MAX_TEMPERATURE_DEVIANCE            (10)    // Stored as temperature * 10. (real value = 1.0 degrees celsius)
#define MAX_TARGET_TEMPERATURE              (370)   // Stored as temperature * 10. (real value = 37 degrees celsius) (Only the initial max value)
#define MAX_DELTA_TEMP                      (500)   // Acceptable tolerance (in 1/1000 degrees C)

#define NUMBER_OF_READINGS                  2      // Number of readings to average on when function "getThermistorTemp" is called

#define PELTIER_PWM_START_VALUE             (-90)   // Starting value (in %) of Peltier output calibration
#define PELTIER_PWM_END_VALUE               (100)    // Last pwm (in %) value for calibration
#define PELTIER_PWM_INCREMENT_VALUE         (10)    // Increment (in %) between calibration points
#define NB_HIT                              (10)    // Ajout Kevin TODO: Plz comment accordingly
#define NB_STABLE_VALUE_REQUIRED            (7)    // Desired number of stable measures to set correspondance between voltage and temperature reading 
#define TEMP_TOLERANCE                      (3)     // Symbolize a tolerance of +- x/10 degree celsius as temperatures are registred as 10 times their real values.
#define CY_DELAY_MS_FOR_STABLE_TEMP         (5000)

#define PELTIER_COOL				        (0x01)  // In the control register, the cooling bit is set at position 0.	
#define PELTIER_HEAT				        (0x02)  // In the control register, the heating bit is set at position 1.
#define BEST_HEATING_PWM_PERCENTAGE         (100)
#define BEST_COOLING_PWM_PERCENTAGE         (80)
#define PELTIER_MIN_PWM                     (25)    // Minimal percentage at which we can control the Peltier element
#define PELTIER_MAX_PWM                     (80)    // Maximal percentage at which we can control the Peltier element

#define VDDA                                (5)     // VDDA is the main analog voltage

#define SubModule1_ID                       (0)
#define SubModule2_ID                       (1)
#define PELTIER1_ENABLE_MSK                 (0x01)  // Enable mask for the control register. To set the bit, | with the mask, to clear it, &~ with the mask.
#define PELTIER2_ENABLE_MSK                 (0x02)  // Enable mask for the control register. To set the bit, | with the mask, to clear it, &~ with the mask.

#define MASTER_CLOCK_FREQ                   (24000000)  //Used to divide the interrupt of update turbidity for the update pelteir 
//CAN Instruction list
#define GET_CURRENT_TEMPERATURE             0  // Instruction to send back the actual temperature
    
#define SET_TARGET_TEMPERATURE              1  // Instruction to set temperature, needs a value
#define GET_TARGET_TEMPERATURE              2
    
#define SET_TEMPERATURE_LIMIT_HIGH          3
#define GET_TEMPERATURE_LIMIT_HIGH          4

#define SET_TEMPERATURE_LIMIT_LOW           5
#define GET_TEMPERATURE_LIMIT_LOW           6  
 
#define SET_AGITATOR_ENABLE					7
#define SET_AGITATOR_SPEED                  8  // Instruction to set motor speed, needs a value
#define GET_AGITATOR_STATE                  9  // Instruction to disable desired agitator
    
#define SET_FAN_ENABLE						10
#define SET_FAN_SPEED                       11  // Instruction to enable desired fan
#define GET_FAN_STATE                       12  // Instruction to disable desired fan

#define SET_PELTIER_ENABLE 					13
#define SET_PELTIER_SPEED                   14
#define GET_PELTIER_STATE                   15  // Instruction to disable desired Peltier module

#define GET_TURBIDITY                       16  // Instruction to send back the actual turbidity value

#define SET_TEMPERATURE_PID_PARAM_P         17
#define SET_TEMPERATURE_PID_PARAM_I         18
#define SET_TEMPERATURE_PID_PARAM_D         19
#define GET_TEMPERATURE_PID_PARAM_P         20
#define GET_TEMPERATURE_PID_PARAM_I         21
#define GET_TEMPERATURE_PID_PARAM_D         22
    
#define GET_PID_INTEGRAL	                23
#define GET_MODEL_FIRMWARE                  254
    
    
//CAN possible answers
#define BAD_COMMAND                         24  // To send if the instruction received is not recognized
#define BAD_VALUE                           25  // To send if the value is not inside defined limits
#define CALIBRATION_STOPPED                 26
#define CALIBRATION_SUCCEEDED               27
#define TARGET_TEMPERATURE_REACHED          28  // Instruction to indicate to the master that we reached the target temperature
#define TEMPERATURE_MAINTAIN_STOPPED        29
#define BAD_SUBMODULE_NUMBER                30


typedef enum {agitatorDisabled=0, agitatorEnabled=1} AgitatorStateType;
typedef enum {fanDisabled=0, fanEnabled=1} FanStateType;
typedef enum {peltierDisabled=0, peltierEnabled=1} PeltierStateType;
typedef enum {Maintaining_heat,Waiting_drop, Maintaining_cool, Waiting_overshoot, Waiting} TemperatureModeType;
typedef enum {NotSet=0x02, Cooling=0x01, Heating=0x00} CurrentDirectionType;
typedef enum {OutDated=0x00, UpToDate=0x01} PwmFromCalibrationStatusType;
typedef enum {False=0x00, True=0x01} Boolean;

// Structure of TAC submodule
typedef struct
{    
    uint16 maxTemperatureDeviation; // Stored as real temperature * 10
    
    PeltierStateType peltierState;
    
    int16 targetTemperature; // Stored as real temperature * 10
    int16 currentTemperature; // Stored as real temperature * 10
    TemperatureModeType temperatureMode;
    CurrentDirectionType currentDirection;
    
    uint16 pwmCompareValue;
    uint8 desiredPwmPercentage;
    uint8 actualPwmPercentage;
    uint16 pwmPeriodValue;
    
    uint8 agitatorSpeed;
    AgitatorStateType agitatorState;
    
    uint8 fanSpeedPercentage;
    FanStateType fanState;
    
    uint16 temperatureLimitHigh;
    uint16 temperatureLimitLow;
    float kp, ki, kd;
    
    // turbidity
    float Turbidity_mean;
    
}TACModule;


#endif

/* [] END OF FILE */
