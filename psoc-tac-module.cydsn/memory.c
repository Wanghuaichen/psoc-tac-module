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
#include "memory.h"


void saveUINT16(uint8 startAddress, uint16 value);
uint16 loadUINT16(uint8 startAdress);

void saveFLOAT(uint8 startAdress, float value);
float loadFLOAT(uint8 startAdress);



void init_eeprom()
{
    EEPROM_Start();
    CyDelayUs(5); // the EEPROM needs 5 μS to start
    
    /*
    It is necessary to acquire the die temperature by calling the EEPROM_UpdateTemperature() 
    function before a series of EEPROM write operations. The EEPROM_UpdateTemperature() 
    function queries SPC for the die temperature and stores it in a global variable, 
    which is used while performing EEPROM write operations. If the application is used 
    in an environment where the die temperature changes 10° C or more, the temperature 
    should be refreshed to adjust the write times for the optimal performance.
    */
    EEPROM_UpdateTemperature();
}



void savePIDToEEPROM(uint8 module, float kp, float ki, float kd)
{
    uint8 startAdress;

    if(module == 0)
        startAdress = EEPROM_MODULE0_ADRESS_KP;
    else
        startAdress = EEPROM_MODULE1_ADRESS_KP;
    
    saveFLOAT(startAdress, kp);
    saveFLOAT(startAdress+4, ki);
    saveFLOAT(startAdress+8, kd);
}

void loadPIDFromEEPROM(uint8 module, float *kp, float *ki, float *kd)
{
    uint8 startAdress;

    if(module == 0)
        startAdress = EEPROM_MODULE0_ADRESS_KP;
    else
        startAdress = EEPROM_MODULE1_ADRESS_KP;
    
    *kp = loadFLOAT(startAdress);
    *ki = loadFLOAT(startAdress+4);
    *kd = loadFLOAT(startAdress+8);
}


void saveTemperatureLimitHighToEEPROM(uint8 module,uint16 limit)
{
    if(module == 0)
        saveUINT16(EEPROM_MODULE0_ADRESS_TEMPERATURE_LIMIT_HIGH, limit);
    else
        saveUINT16(EEPROM_MODULE1_ADRESS_TEMPERATURE_LIMIT_HIGH, limit);
}

uint16 loadTemperatureLimitHighFromEEPROM(uint8 module)
{
    if(module == 0)
        return loadUINT16(EEPROM_MODULE0_ADRESS_TEMPERATURE_LIMIT_HIGH);
    else
        return loadUINT16(EEPROM_MODULE1_ADRESS_TEMPERATURE_LIMIT_HIGH);
}

void saveTemperatureLimitLowToEEPROM(uint8 module,uint16 limit)
{
    if(module == 0)
        saveUINT16(EEPROM_MODULE0_ADRESS_TEMPERATURE_LIMIT_LOW, limit);
    else
        saveUINT16(EEPROM_MODULE1_ADRESS_TEMPERATURE_LIMIT_LOW, limit);
}

uint16 loadTemperatureLimitLowFromEEPROM(uint8 module)
{
    if(module == 0)
        return loadUINT16(EEPROM_MODULE0_ADRESS_TEMPERATURE_LIMIT_LOW);
    else
        return loadUINT16(EEPROM_MODULE1_ADRESS_TEMPERATURE_LIMIT_LOW);
}

void saveTargetTemperatureToEEPROM(uint8 module, uint16 target)
{
    if(module == 0)
        saveUINT16(EEPROM_MODULE0_ADRESS_TEMPERATURE_TARGET, target);
    else
        saveUINT16(EEPROM_MODULE1_ADRESS_TEMPERATURE_TARGET, target);
}

uint16 loadTargetTemperatureFromEEPROM(uint8 module)
{
    if(module == 0)
        return loadUINT16(EEPROM_MODULE0_ADRESS_TEMPERATURE_TARGET);
    else
        return loadUINT16(EEPROM_MODULE1_ADRESS_TEMPERATURE_TARGET);
}



// HELPER FUNCTION

void saveUINT16(uint8 startAdress, uint16 value)
{
    EEPROM_WriteByte((int8)value, startAdress);
    EEPROM_WriteByte((int8)(value>>8), startAdress+1);
}

uint16 loadUINT16(uint8 startAdress)
{
    uint16 value;
    
    value = EEPROM_ReadByte(startAdress+1);
    value = (value<<8) + EEPROM_ReadByte(startAdress);
    
    return value;
}

void saveFLOAT(uint8 startAdress, float value)
{
    uint8 i;
    uint8 k[4];

    memcpy(k, &value, sizeof(float));
    for( i=0; i<4; i++)
        EEPROM_WriteByte(k[i], startAdress+i);
}

float loadFLOAT(uint8 startAdress)
{
    uint8 i;
    uint8 k[4];
    float value;
    
    for( i=0; i<4; i++)
        k[i] = EEPROM_ReadByte(startAdress+i);
        
    memcpy(&value, k, sizeof(float));
    
    return value;
}


/* [] END OF FILE */
