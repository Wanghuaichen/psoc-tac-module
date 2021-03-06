/* ========================================
 *
 * Copyright BioBot Instrumentation, 2015
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF BioBot Instrumentation.
 *
 * WRITTEN BY : Philippe-Antoine Major &
 *              Louis-Vincent Major
 * ========================================
*/

#include "CAN_Communication.h"

// Retrieve the messages in the order they were received by the master. (FIFO)
CAN_MSG getReceivedMessage()
{
    //struct RX_Msg msgToTreat = receivedMessages[msgToBeTreatedIndex];
    CAN_MSG msgToTreat = receivedMsgs[msgToBeTreatedIndex];
   
    msgToBeTreatedIndex = (msgToBeTreatedIndex+1) % MAX_MSG_BUFFER_SIZE;
   
    // A message was treated, we decrement the counter of messages to be treated.
    messageToBeTreatedCount += -1;
    
    return msgToTreat;
}

// Send a message on the CAN Bus.
int8 sendMessage(CAN_MSG* msgPtr, uint32 CAN_ID)
{
    CAN_1_TX_MSG msgToSend;
    
    msgToSend.id = CAN_ID;   
    msgToSend.rtr = MSG_RTR;
    msgToSend.ide = MSG_IDE;
    msgToSend.irq = MSG_IRQ;
    msgToSend.msg = &msgPtr->msgBytes;
    msgToSend.dlc = msgPtr->DLC;
    
    CAN_1_SendMsg(&msgToSend);
    return 1;
}

int8 echoBackToMaster(CAN_MSG* msgPtr)
{
    CAN_1_TX_MSG msgToSendBack;
    // Setting all the parameters for the message to send back.    
    msgToSendBack.id = MASTER_ID;
    msgToSendBack.rtr = MSG_RTR;
    msgToSendBack.ide = MSG_IDE;
    msgToSendBack.irq = MSG_IRQ;
    msgToSendBack.dlc = msgPtr->DLC;
    msgToSendBack.msg = &msgPtr->msgBytes; 
    
    CAN_1_SendMsg(&msgToSendBack);
    
    return 1;
}

/* [] END OF FILE */
