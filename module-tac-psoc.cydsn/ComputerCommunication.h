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

#ifndef __COMPUTER_COM_H__
#define __COMPUTER_COM_H__

#include <device.h>
#include <project.h>
#include <Defines.h>
#include "CAN_Communication.h"


void sendTemperatureToCAN(uint8 module, uint16 temperature, int8 command );
void sendDataToCAN(uint8 module, uint8 instruction, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7);
void sendDataToCAN2(uint8 instruction, uint8 byte1, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7);
void sendFloatToCAN(uint8 instruction, uint8 module, float *datafloat);

#endif