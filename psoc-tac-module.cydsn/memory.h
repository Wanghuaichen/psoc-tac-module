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

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <project.h>

// MODULE 0 constant
#define EEPROM_MODULE0_ADRESS_KP    0 // 4bytes for KP
#define EEPROM_MODULE0_ADRESS_KI    4 // 4bytes for KI
#define EEPROM_MODULE0_ADRESS_KD    8 // 4bytes for KD
#define EEPROM_MODULE0_ADRESS_TEMPERATURE_LIMIT_LOW   12 // 2bytes
#define EEPROM_MODULE0_ADRESS_TEMPERATURE_LIMIT_HIGH  14 // 2bytes
#define EEPROM_MODULE0_ADRESS_TEMPERATURE_TARGET 16 // 2bytes

#define EEPROM_MODULE1_ADRESS_KP    0 // 4bytes for KP
#define EEPROM_MODULE1_ADRESS_KI    4 // 4bytes for KI
#define EEPROM_MODULE1_ADRESS_KD    8 // 4bytes for KD
#define EEPROM_MODULE1_ADRESS_TEMPERATURE_LIMIT_LOW   12 // 2bytes
#define EEPROM_MODULE1_ADRESS_TEMPERATURE_LIMIT_HIGH  14 // 2bytes
#define EEPROM_MODULE1_ADRESS_TEMPERATURE_TARGET 16 // 2bytes
    
    
    
    
    
void init_eeprom();

void savePIDToEEPROM(uint8 module, float kp, float ki, float kd);
void loadPIDFromEEPROM(uint8 module,float *kp, float *ki, float *kd);

void saveTemperatureLimitHighToEEPROM(uint8 module, uint16 limit);
uint16 loadTemperatureLimitHighFromEEPROM(uint8 module);

void saveTemperatureLimitLowToEEPROM(uint8 module, uint16 limit);
uint16 loadTemperatureLimitLowFromEEPROM(uint8 module);

void saveTargetTemperatureToEEPROM(uint8 module, uint16 target);
uint16 loadTargetTemperatureFromEEPROM(uint8 module);

#endif

/* [] END OF FILE */
