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

#include "PIDControler.h"

void applyCommand(uint8 module, int8 command);


double integral = 0;
double last_error = 0;

extern TACModule tacModule[2];

#define PID_ENABLE_TEMPERATURE 90

// Updates current temperature of the Peltier element by reading the corresponding thermistor.
void updatePeltierOutput(uint8 module, double dt)
{
    double command;
    uint16 target = tacModule[module].targetTemperature;
    double current = getThermistorTemp(module); 
	double error = target - current;
    double kp;
    double x;
    
    if(current < tacModule[module].temperatureLimitHigh)
    {
        if( current > target-PID_ENABLE_TEMPERATURE && current < target+PID_ENABLE_TEMPERATURE)
        {
			integral += error*dt;
		}
			
		double derivative = (error - last_error)/dt;
 		
		x = (fabs(error)/(double)100);
		if(error < 0)
			kp = (double)tacModule[module].kp + x + (x*x*x)/(double)2;
		else
			kp = (double)tacModule[module].kp + 0.01*x + (x*x)/(double)20;
	  
		command = kp * error + (double)tacModule[module].ki * integral + (double)tacModule[module].kd * derivative;
		
		if(command > 100)  command = 100;
		if(command < -100) command = -100;
		
		applyCommand(module, command);
    }
    else 
    {
        // TODO: SEND ERROR MESSAGE (TEMPERATURE LIMIT REACHED)
        changeFanState(fanEnabled, module);
        changeFanSpeed(100,module);
        changePeltierModuleState(peltierDisabled, module);
    }
    
	sendTemperatureToCAN(module, current, (int8)command);
    float i = (float)integral;
	sendFloatToCAN(GET_PID_INTEGRAL, module, &i);
    
    last_error = error;
}


void applyCommand(uint8 module, int8 command)
{
    int8 commandABS;
    commandABS = abs((int8)command);
    
    if(command != commandABS) // COOLING PROCESS
    {
        if(tacModule[module].targetTemperature < 250) // TODO: change 250 to the value of the ambiant temperature from a sensor
        {
            changePeltierModuleCurrentDirection(Cooling, module);
            changePeltierPWMValue(commandABS,module);
        }
        changeFanSpeed(commandABS,module);
    }
    else 					// HEATING PROCESS
    {
        changePeltierModuleCurrentDirection(Heating, module);
		changeFanSpeed(0,module);
		
        changePeltierPWMValue(commandABS,module);
    }
}


void resetPIDSumError()
{
    integral = 0;
}



/* [] END OF FILE */
