/* ========================================
 *
 * Copyright Biobotus, 2015
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include <math.h>
#include "Defines.h"
#include "CAN_Communication.h"
#include "ComputerCommunication.h"
#include "turbido.h"
#include "Termistor.h"
#include "memory.h"

#include "FanControler.h"
#include "PeltierControler.h"
#include "AgitatorControler.h"
#include "PIDControler.h"

// FIRST DEFINITION OF GLOBAL VARIABLES DEFINED IN Defines.h.
int messageToBeTreatedCount = 0;
int msgToBeTreatedIndex = 0;
int msgToBeStoredIndex = 0;
CAN_MSG receivedMsgs[MAX_MSG_BUFFER_SIZE];

TACModule tacModule[2];

// FIRST DEFINITION SECTION END

volatile uint8 peltier_update_flag = 0; 

// Variables for Turbidity
float Turbidity_mean = 0;
uint16 Turbido_ADC_result = 0;
volatile int newTurbidoDataFlag = 0; 


/*===========================================================================*/
// prototypes
/*===========================================================================*/

/*
 * Used to initiate everything that is related to the TAC module.
 */
void initTACModule();
uint8 treatMessage(uint8 *packet);


CY_ISR(InterruptHandler)
{
    newTurbidoDataFlag = 1;
    Turbido_ADC_result = CY_GET_REG16(ADC_TURBIDO_SAR_WRK_PTR);
}

CY_ISR(pidInterruptHandler)
{
    peltier_update_flag = 1;
    TimerPID_STATUS;
}


void initTimerPID()
{
    isr_pid_StartEx(pidInterruptHandler);
    TimerPID_Start();
}

void initCAN()
{
    // Initializing required components for CAN communication
    CAN_1_Start();
    CAN_1_GlobalIntEnable();
    CAN_Standby_Write(0);
}

/*===========================================================================*/
// Main loop
/*===========================================================================*/
int main()
{

    /* Main principal sequence :
    1- Initialize components (CAN/Uart/thermistors/ADC)
    2- Identify the module to the master
    3- Wait for commands from the master
    4- Main loop :
        4.1 Verify if an instruction was received by looping through all the flags that can be set by the interrupt 
            driven by the CAN bus.        
    */
    
    // Initialize everything for the module, from communication to peripherals.
      
    initCAN();
    init_eeprom();
    initTACModule();
    initTimerPID();
    
    CyGlobalIntEnable;
    
    
    for(;;)
    {
        
        //Verify if a message needs to be treated in the message received buffer.       
        if(messageToBeTreatedCount>0)
        {
            // Treat the last message received and echo it back on the CAN bus as an acknowledgement.
            CAN_MSG msgToTreat = getReceivedMessage(); 
            treatMessage(msgToTreat.msgBytes.byte);
        }
        
        /* Place your application code here. */

        if(newTurbidoDataFlag)
        {
            newTurbidoDataFlag = 0;
            Turbidity_mean = updateTurbidoOutput(Turbido_ADC_result);
        }
        
        // Update the peltier outputs of the module0
        if(peltier_update_flag)
        {
            updatePeltierOutput(0, (double)0.5);
            peltier_update_flag=0;
            sendFloatToCAN(GET_TURBIDITY, 0, &Turbidity_mean);
        }
    }   
    
}
/*===========================================================================*/
// definition
/*===========================================================================*/
void initTACModule()
{
   /*Start all the hardware components required*/
	ADC_Start();    // Convertisseur analogique-numérique
    
    /* Start ADC, AMux, OpAmp components */
    Peltier1_PWM_Ctrl_Start();
    Peltier2_PWM_Ctrl_Start();
    
    // Initializing fan and motor pwm
    pwmAgitator_1_Start();
    pwmAgitator_2_Start();
    pwmFan_1_Start();
    pwmFan_2_Start();
    
    
    //Bloc of code to populate the EEPROM for the first time (DEFAULT VALUES)
    /*savePIDToEEPROM(0, 0.2, 0.01, 0);
    savePIDToEEPROM(1, 0.2, 0.01, 0);
    saveTargetTemperatureToEEPROM(0, 250);
    saveTargetTemperatureToEEPROM(1, 250);
    
    saveTemperatureLimitHighToEEPROM(0, 700);
    saveTemperatureLimitHighToEEPROM(1, 700);
    saveTemperatureLimitLowToEEPROM(0, 0);
    saveTemperatureLimitLowToEEPROM(1, 0);//*/
    
    loadPIDFromEEPROM(0, &tacModule[0].kp, &tacModule[0].ki, &tacModule[0].kd);
    loadPIDFromEEPROM(1, &tacModule[1].kp, &tacModule[1].ki, &tacModule[1].kd);
    tacModule[0].temperatureLimitHigh = loadTemperatureLimitHighFromEEPROM(0);
    tacModule[1].temperatureLimitHigh = loadTemperatureLimitHighFromEEPROM(1);
    
    tacModule[0].targetTemperature = loadTargetTemperatureFromEEPROM(0);
    tacModule[1].targetTemperature = loadTargetTemperatureFromEEPROM(1);
    
    
    // Make sure both Peltier "Enable" signal are set to 0.
    changePeltierModuleState(peltierEnabled,0);
    changePeltierModuleState(peltierEnabled,1);
    
    changeFanState(fanEnabled, 0);
    changeFanState(fanEnabled, 1);
    
    // Initializing required components for Turbidity reading.
    TurbidoISR_StartEx(InterruptHandler);
    initTurbido();
}

//TODO: -Implement the switch for each instruction -> DONE
//      -Implement function for each intructions
//      -Implement changing of the message
//      -Send back the correct message to the master with the required value.
// This function is used to make the message that is send back to the PC and 
// send it as well as echoing the received message 
uint8 treatMessage(uint8 *packet)
{ 
    int16 tmp;
    uint8 module = packet[INDEX_MODULE_BYTE];
    
    //changeFanSpeed    
    switch (packet[0]) 
    {
        // TODO : Complete this section.        
        case SET_TARGET_TEMPERATURE:
        {   
            tmp = (uint16)(((uint16)packet[3]<<8) | packet[2]);
            tacModule[module].targetTemperature = tmp;
            saveTargetTemperatureToEEPROM(module, tmp);
            resetPIDSumError();
            break;
        }
        case SET_FAN_ENABLE: // To be verified
        {
            changeFanState(packet[2], module);
            break;
        }
        case SET_FAN_SPEED: // To be verified
        {
            changeFanSpeed(packet[2], module);
            break;
        }
        case GET_FAN_STATE: // To be verified
        {
            sendDataToCAN(GET_FAN_STATE, module,tacModule[module].fanState,tacModule[module].fanSpeedPercentage,0,0,0);
            break;
        }
        case GET_CURRENT_TEMPERATURE: // Modify to return the temperature of the desired thermistor.
        {            
            sendDataToCAN(GET_CURRENT_TEMPERATURE, module, 0, tacModule[module].currentTemperature,tacModule[module].currentTemperature>>8,0,0);
            break;
        }
        case SET_AGITATOR_ENABLE: // To be verified.
        {
            changeAgitatorState(packet[2], module);;
            break; 
        }
        case SET_AGITATOR_SPEED: // To be verified.
        {
            changeAgitatorSpeed(packet[2], module);
            break; 
        }
        case GET_AGITATOR_STATE: // To be verified.
        {
            sendDataToCAN(GET_AGITATOR_STATE, module,tacModule[module].agitatorState,tacModule[module].agitatorSpeed, 0,0,0);
            break; 
        }
        case GET_TURBIDITY:
        {
            sendFloatToCAN(GET_TURBIDITY, module, &Turbidity_mean);
            break;
        }
        case SET_TEMPERATURE_PID_PARAM_P:
        {
            memcpy(&tacModule[module].kp, &packet[4], sizeof(float));
            savePIDToEEPROM(module,tacModule[module].kp, tacModule[module].ki, tacModule[module].kd);
            break;
        }
        case SET_TEMPERATURE_PID_PARAM_I:
        {
            memcpy(&tacModule[module].ki, &packet[4], sizeof(float));
            savePIDToEEPROM(module,tacModule[module].kp, tacModule[module].ki, tacModule[module].kd);
            break;
        }
        case SET_TEMPERATURE_PID_PARAM_D:
        {
            memcpy(&tacModule[module].kd, &packet[4], sizeof(float));
            savePIDToEEPROM(module,tacModule[module].kp, tacModule[module].ki, tacModule[module].kd);
            break;
        }
        case GET_TEMPERATURE_PID_PARAM_P:
        {
            sendFloatToCAN(GET_TEMPERATURE_PID_PARAM_P, module, &tacModule[module].kp);
            break;
        }
        case GET_TEMPERATURE_PID_PARAM_I:
        {
            sendFloatToCAN(GET_TEMPERATURE_PID_PARAM_I, module, &tacModule[module].ki);
            break;
        }
        case GET_TEMPERATURE_PID_PARAM_D:
        {
            sendFloatToCAN(GET_TEMPERATURE_PID_PARAM_D, module, &tacModule[module].kd);
            //sendDataToCAN(module,GET_TEMPERATURE_PID_PARAM_D,k[0],k[1],k[2],k[3]);
            break;
        }
        case GET_TARGET_TEMPERATURE:
        {
            sendDataToCAN(GET_TARGET_TEMPERATURE, module , 0,tacModule[module].targetTemperature,tacModule[module].targetTemperature>>8,0,0);
            break;
        }
        case SET_PELTIER_ENABLE:
        {
            changePeltierModuleState(packet[2],module);
            break;   
        }
		case SET_PELTIER_SPEED:
		{
			int8 value = packet[2];
			if(value < 0)
				changePeltierModuleCurrentDirection(Cooling, module);
			else
				changePeltierModuleCurrentDirection(Heating, module);
            changePeltierPWMValue(abs(value),module);
            break;   
		}
        case GET_PELTIER_STATE:
        {
            sendDataToCAN(GET_PELTIER_STATE, module, tacModule[module].peltierState, tacModule[module].pwmCompareValue, 0, 0, 0);
            break;
        }
        case SET_TEMPERATURE_LIMIT_HIGH:
        {
            tacModule[module].temperatureLimitHigh = (packet[3]<<8) | packet[2];
            saveTemperatureLimitHighToEEPROM(module, tacModule[module].temperatureLimitHigh);
            break;
        }
        case GET_TEMPERATURE_LIMIT_HIGH:
        {
            sendDataToCAN(GET_TEMPERATURE_LIMIT_HIGH, module, tacModule[module].temperatureLimitHigh, tacModule[module].temperatureLimitHigh>>8, 0, 0, 0);
            break;
        }
        case SET_TEMPERATURE_LIMIT_LOW:
        {
            tacModule[module].temperatureLimitLow = (packet[3]<<8) | packet[2];
            saveTemperatureLimitLowToEEPROM(module, tacModule[module].temperatureLimitLow);
            break;
        }
        case GET_TEMPERATURE_LIMIT_LOW:
        {
            sendDataToCAN(GET_TEMPERATURE_LIMIT_LOW, module, tacModule[module].temperatureLimitLow, tacModule[module].temperatureLimitLow>>8, 0, 0, 0);
            break;
        }
        case GET_MODEL_FIRMWARE:
            sendDataToCAN2(GET_MODEL_FIRMWARE, HARDWARE_CAN_ID, 'T', 'A', 'C', 'v', '1', '0');
        default:          
          break;
    }

    return 1;
}

