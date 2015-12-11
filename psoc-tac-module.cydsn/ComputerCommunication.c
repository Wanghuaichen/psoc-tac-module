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

#include "ComputerCommunication.h"



void sendTemperatureToCAN(uint8 module, uint16 temperature, int8 command )
{
    CAN_MSG msgToSendBack = {{GET_CURRENT_TEMPERATURE,module,HARDWARE_CAN_ID,0,0,0,0,0},{8},{0xFF}}; // Sets the first bytes of the message.

    msgToSendBack.msgBytes.byte[4] = (uint8)temperature;
    msgToSendBack.msgBytes.byte[5] = (uint8)(temperature>>8);
    msgToSendBack.msgBytes.byte[6] = command;
    sendMessage(&msgToSendBack,0xFF);  
}


void sendDataToCAN(uint8 instruction, uint8 module, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7)
{
    CAN_MSG msg = {{instruction,module,HARDWARE_CAN_ID,byte3,byte4,byte5,byte6,byte7},{8},{0xFF}}; // Sets the first bytes of the message.
    sendMessage(&msg,0xF); 
}

void sendDataToCAN2(uint8 instruction, uint8 byte1, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7)
{
    CAN_MSG msg = {{  instruction,
                      byte1,byte2,byte3,byte4,byte5,byte6,byte7},
                      {8},{0xFF}}; // Sets the first bytes of the message.

    sendMessage(&msg,0xFF);  
}

void sendFloatToCAN(uint8 instruction, uint8 module, float *datafloat)
{
    CAN_MSG msgToSendBack = {{instruction,module,HARDWARE_CAN_ID,0,0,0,0},{8},{0xFF}}; // Sets the first bytes of the message.

	uint8 d[4];
    memcpy(d, datafloat, 4);
	
    msgToSendBack.msgBytes.byte[4] = d[0];
    msgToSendBack.msgBytes.byte[5] = d[1];
    msgToSendBack.msgBytes.byte[6] = d[2];
    msgToSendBack.msgBytes.byte[7] = d[3];
    sendMessage(&msgToSendBack,0xFF); 
}


