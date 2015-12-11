/*******************************************************************************
* File Name: UART_drv.c
* Version 2.80
*
* Description:
*  Endpoint 0 Driver for the USBFS Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART.h"
#include "UART_pvt.h"



/***************************************
* Global data allocation
***************************************/

volatile T_UART_EP_CTL_BLOCK UART_EP[UART_MAX_EP];
volatile uint8 UART_configuration;
volatile uint8 UART_interfaceNumber;
volatile uint8 UART_configurationChanged;
volatile uint8 UART_deviceAddress;
volatile uint8 UART_deviceStatus;
volatile uint8 UART_interfaceSetting[UART_MAX_INTERFACES_NUMBER];
volatile uint8 UART_interfaceSetting_last[UART_MAX_INTERFACES_NUMBER];
volatile uint8 UART_interfaceStatus[UART_MAX_INTERFACES_NUMBER];
volatile uint8 UART_device;
const uint8 CYCODE *UART_interfaceClass;


/***************************************
* Local data allocation
***************************************/

volatile uint8 UART_ep0Toggle;
volatile uint8 UART_lastPacketSize;
volatile uint8 UART_transferState;
volatile T_UART_TD UART_currentTD;
volatile uint8 UART_ep0Mode;
volatile uint8 UART_ep0Count;
volatile uint16 UART_transferByteCount;


/*******************************************************************************
* Function Name: UART_ep_0_Interrupt
********************************************************************************
*
* Summary:
*  This Interrupt Service Routine handles Endpoint 0 (Control Pipe) traffic.
*  It dispatches setup requests and handles the data and status stages.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(UART_EP_0_ISR)
{
    uint8 bRegTemp;
    uint8 modifyReg;

    #ifdef UART_EP_0_ISR_ENTRY_CALLBACK
        UART_EP_0_ISR_EntryCallback();
    #endif /* UART_EP_0_ISR_ENTRY_CALLBACK */
    
    bRegTemp = CY_GET_REG8(UART_EP0_CR_PTR);
    if ((bRegTemp & UART_MODE_ACKD) != 0u)
    {
        modifyReg = 1u;
        if ((bRegTemp & UART_MODE_SETUP_RCVD) != 0u)
        {
            if((bRegTemp & UART_MODE_MASK) != UART_MODE_NAK_IN_OUT)
            {
                modifyReg = 0u;                                     /* When mode not NAK_IN_OUT => invalid setup */
            }
            else
            {
                UART_HandleSetup();
                if((UART_ep0Mode & UART_MODE_SETUP_RCVD) != 0u)
                {
                    modifyReg = 0u;                         /* if SETUP bit set -> exit without modifying the mode */
                }

            }
        }
        else if ((bRegTemp & UART_MODE_IN_RCVD) != 0u)
        {
            UART_HandleIN();
        }
        else if ((bRegTemp & UART_MODE_OUT_RCVD) != 0u)
        {
            UART_HandleOUT();
        }
        else
        {
            modifyReg = 0u;
        }
        if(modifyReg != 0u)
        {
            bRegTemp = CY_GET_REG8(UART_EP0_CR_PTR);    /* unlock registers */
            if((bRegTemp & UART_MODE_SETUP_RCVD) == 0u)  /* Check if SETUP bit is not set, otherwise exit */
            {
                /* Update the count register */
                bRegTemp = UART_ep0Toggle | UART_ep0Count;
                CY_SET_REG8(UART_EP0_CNT_PTR, bRegTemp);
                if(bRegTemp == CY_GET_REG8(UART_EP0_CNT_PTR))   /* continue if writing was successful */
                {
                    do
                    {
                        modifyReg = UART_ep0Mode;       /* Init temporary variable */
                        /* Unlock registers */
                        bRegTemp = CY_GET_REG8(UART_EP0_CR_PTR) & UART_MODE_SETUP_RCVD;
                        if(bRegTemp == 0u)                          /* Check if SETUP bit is not set */
                        {
                            /* Set the Mode Register  */
                            CY_SET_REG8(UART_EP0_CR_PTR, UART_ep0Mode);
                            /* Writing check */
                            modifyReg = CY_GET_REG8(UART_EP0_CR_PTR) & UART_MODE_MASK;
                        }
                    }while(modifyReg != UART_ep0Mode);  /* Repeat if writing was not successful */
                }
            }
        }
    }
    #ifdef UART_EP_0_ISR_EXIT_CALLBACK
        UART_EP_0_ISR_ExitCallback();
    #endif /* UART_EP_0_ISR_EXIT_CALLBACK */
}


/*******************************************************************************
* Function Name: UART_HandleSetup
********************************************************************************
*
* Summary:
*  This Routine dispatches requests for the four USB request types
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_HandleSetup(void) 
{
    uint8 requestHandled;

    requestHandled = CY_GET_REG8(UART_EP0_CR_PTR);      /* unlock registers */
    CY_SET_REG8(UART_EP0_CR_PTR, requestHandled);       /* clear setup bit */
    requestHandled = CY_GET_REG8(UART_EP0_CR_PTR);      /* reread register */
    if((requestHandled & UART_MODE_SETUP_RCVD) != 0u)
    {
        UART_ep0Mode = requestHandled;        /* if SETUP bit set -> exit without modifying the mode */
    }
    else
    {
        /* In case the previous transfer did not complete, close it out */
        UART_UpdateStatusBlock(UART_XFER_PREMATURE);

        switch (CY_GET_REG8(UART_bmRequestType) & UART_RQST_TYPE_MASK)
        {
            case UART_RQST_TYPE_STD:
                requestHandled = UART_HandleStandardRqst();
                break;
            case UART_RQST_TYPE_CLS:
                requestHandled = UART_DispatchClassRqst();
                break;
            case UART_RQST_TYPE_VND:
                requestHandled = UART_HandleVendorRqst();
                break;
            default:
                requestHandled = UART_FALSE;
                break;
        }
        if (requestHandled == UART_FALSE)
        {
            UART_ep0Mode = UART_MODE_STALL_IN_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: UART_HandleIN
********************************************************************************
*
* Summary:
*  This routine handles EP0 IN transfers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_HandleIN(void) 
{
    switch (UART_transferState)
    {
        case UART_TRANS_STATE_IDLE:
            break;
        case UART_TRANS_STATE_CONTROL_READ:
            UART_ControlReadDataStage();
            break;
        case UART_TRANS_STATE_CONTROL_WRITE:
            UART_ControlWriteStatusStage();
            break;
        case UART_TRANS_STATE_NO_DATA_CONTROL:
            UART_NoDataControlStatusStage();
            break;
        default:    /* there are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: UART_HandleOUT
********************************************************************************
*
* Summary:
*  This routine handles EP0 OUT transfers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_HandleOUT(void) 
{
    switch (UART_transferState)
    {
        case UART_TRANS_STATE_IDLE:
            break;
        case UART_TRANS_STATE_CONTROL_READ:
            UART_ControlReadStatusStage();
            break;
        case UART_TRANS_STATE_CONTROL_WRITE:
            UART_ControlWriteDataStage();
            break;
        case UART_TRANS_STATE_NO_DATA_CONTROL:
            /* Update the completion block */
            UART_UpdateStatusBlock(UART_XFER_ERROR);
            /* We expect no more data, so stall INs and OUTs */
            UART_ep0Mode = UART_MODE_STALL_IN_OUT;
            break;
        default:    /* There are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: UART_LoadEP0
********************************************************************************
*
* Summary:
*  This routine loads the EP0 data registers for OUT transfers.  It uses the
*  currentTD (previously initialized by the _InitControlWrite function and
*  updated for each OUT transfer, and the bLastPacketSize) to determine how
*  many uint8s to transfer on the current OUT.
*
*  If the number of uint8s remaining is zero and the last transfer was full,
*  we need to send a zero length packet.  Otherwise we send the minimum
*  of the control endpoint size (8) or remaining number of uint8s for the
*  transaction.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  UART_transferByteCount - Update the transfer byte count from the
*     last transaction.
*  UART_ep0Count - counts the data loaded to the SIE memory in
*     current packet.
*  UART_lastPacketSize - remembers the USBFS_ep0Count value for the
*     next packet.
*  UART_transferByteCount - sum of the previous bytes transferred
*     on previous packets(sum of USBFS_lastPacketSize)
*  UART_ep0Toggle - inverted
*  UART_ep0Mode  - prepare for mode register content.
*  UART_transferState - set to TRANS_STATE_CONTROL_READ
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_LoadEP0(void) 
{
    uint8 ep0Count = 0u;

    /* Update the transfer byte count from the last transaction */
    UART_transferByteCount += UART_lastPacketSize;
    /* Now load the next transaction */
    while ((UART_currentTD.count > 0u) && (ep0Count < 8u))
    {
        CY_SET_REG8((reg8 *)(UART_EP0_DR0_IND + ep0Count), *UART_currentTD.pData);
        UART_currentTD.pData = &UART_currentTD.pData[1u];
        ep0Count++;
        UART_currentTD.count--;
    }
    /* Support zero-length packet*/
    if( (UART_lastPacketSize == 8u) || (ep0Count > 0u) )
    {
        /* Update the data toggle */
        UART_ep0Toggle ^= UART_EP0_CNT_DATA_TOGGLE;
        /* Set the Mode Register  */
        UART_ep0Mode = UART_MODE_ACK_IN_STATUS_OUT;
        /* Update the state (or stay the same) */
        UART_transferState = UART_TRANS_STATE_CONTROL_READ;
    }
    else
    {
        /* Expect Status Stage Out */
        UART_ep0Mode = UART_MODE_STATUS_OUT_ONLY;
        /* Update the state (or stay the same) */
        UART_transferState = UART_TRANS_STATE_CONTROL_READ;
    }

    /* Save the packet size for next time */
    UART_lastPacketSize = ep0Count;
    UART_ep0Count = ep0Count;
}


/*******************************************************************************
* Function Name: UART_InitControlRead
********************************************************************************
*
* Summary:
*  Initialize a control read transaction, usable to send data to the host.
*  The following global variables should be initialized before this function
*  called. To send zero length packet use InitZeroLengthControlTransfer
*  function.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  UART_currentTD.count - counts of data to be sent.
*  UART_currentTD.pData - data pointer.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 UART_InitControlRead(void) 
{
    uint16 xferCount;
    if(UART_currentTD.count == 0u)
    {
        (void) UART_InitZeroLengthControlTransfer();
    }
    else
    {
        /* Set up the state machine */
        UART_transferState = UART_TRANS_STATE_CONTROL_READ;
        /* Set the toggle, it gets updated in LoadEP */
        UART_ep0Toggle = 0u;
        /* Initialize the Status Block */
        UART_InitializeStatusBlock();
        xferCount = (((uint16)CY_GET_REG8(UART_lengthHi) << 8u) | (CY_GET_REG8(UART_lengthLo)));

        if (UART_currentTD.count > xferCount)
        {
            UART_currentTD.count = xferCount;
        }
        UART_LoadEP0();
    }

    return(UART_TRUE);
}


/*******************************************************************************
* Function Name: UART_InitZeroLengthControlTransfer
********************************************************************************
*
* Summary:
*  Initialize a zero length data IN transfer.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  UART_ep0Mode  - prepare for mode register content.
*  UART_transferState - set to TRANS_STATE_CONTROL_READ
*  UART_ep0Count - cleared, means the zero-length packet.
*  UART_lastPacketSize - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 UART_InitZeroLengthControlTransfer(void)
                                                
{
    /* Update the state */
    UART_transferState = UART_TRANS_STATE_CONTROL_READ;
    /* Set the data toggle */
    UART_ep0Toggle = UART_EP0_CNT_DATA_TOGGLE;
    /* Set the Mode Register  */
    UART_ep0Mode = UART_MODE_ACK_IN_STATUS_OUT;
    /* Save the packet size for next time */
    UART_lastPacketSize = 0u;
    UART_ep0Count = 0u;

    return(UART_TRUE);
}


/*******************************************************************************
* Function Name: UART_ControlReadDataStage
********************************************************************************
*
* Summary:
*  Handle the Data Stage of a control read transfer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_ControlReadDataStage(void) 

{
    UART_LoadEP0();
}


/*******************************************************************************
* Function Name: UART_ControlReadStatusStage
********************************************************************************
*
* Summary:
*  Handle the Status Stage of a control read transfer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  UART_USBFS_transferByteCount - updated with last packet size.
*  UART_transferState - set to TRANS_STATE_IDLE.
*  UART_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_ControlReadStatusStage(void) 
{
    /* Update the transfer byte count */
    UART_transferByteCount += UART_lastPacketSize;
    /* Go Idle */
    UART_transferState = UART_TRANS_STATE_IDLE;
    /* Update the completion block */
    UART_UpdateStatusBlock(UART_XFER_STATUS_ACK);
    /* We expect no more data, so stall INs and OUTs */
    UART_ep0Mode =  UART_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: UART_InitControlWrite
********************************************************************************
*
* Summary:
*  Initialize a control write transaction
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  UART_USBFS_transferState - set to TRANS_STATE_CONTROL_WRITE
*  UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  UART_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 UART_InitControlWrite(void) 
{
    uint16 xferCount;

    /* Set up the state machine */
    UART_transferState = UART_TRANS_STATE_CONTROL_WRITE;
    /* This might not be necessary */
    UART_ep0Toggle = UART_EP0_CNT_DATA_TOGGLE;
    /* Initialize the Status Block */
    UART_InitializeStatusBlock();

    xferCount = (((uint16)CY_GET_REG8(UART_lengthHi) << 8u) | (CY_GET_REG8(UART_lengthLo)));

    if (UART_currentTD.count > xferCount)
    {
        UART_currentTD.count = xferCount;
    }

    /* Expect Data or Status Stage */
    UART_ep0Mode = UART_MODE_ACK_OUT_STATUS_IN;

    return(UART_TRUE);
}


/*******************************************************************************
* Function Name: UART_ControlWriteDataStage
********************************************************************************
*
* Summary:
*  Handle the Data Stage of a control write transfer
*       1. Get the data (We assume the destination was validated previously)
*       2. Update the count and data toggle
*       3. Update the mode register for the next transaction
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  UART_transferByteCount - Update the transfer byte count from the
*    last transaction.
*  UART_ep0Count - counts the data loaded from the SIE memory
*    in current packet.
*  UART_transferByteCount - sum of the previous bytes transferred
*    on previous packets(sum of USBFS_lastPacketSize)
*  UART_ep0Toggle - inverted
*  UART_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_ControlWriteDataStage(void) 
{
    uint8 ep0Count;
    uint8 regIndex = 0u;

    ep0Count = (CY_GET_REG8(UART_EP0_CNT_PTR) & UART_EPX_CNT0_MASK) -
               UART_EPX_CNTX_CRC_COUNT;

    UART_transferByteCount += ep0Count;

    while ((UART_currentTD.count > 0u) && (ep0Count > 0u))
    {
        *UART_currentTD.pData = CY_GET_REG8((reg8 *)(UART_EP0_DR0_IND + regIndex));
        UART_currentTD.pData = &UART_currentTD.pData[1u];
        regIndex++;
        ep0Count--;
        UART_currentTD.count--;
    }
    UART_ep0Count = ep0Count;
    /* Update the data toggle */
    UART_ep0Toggle ^= UART_EP0_CNT_DATA_TOGGLE;
    /* Expect Data or Status Stage */
    UART_ep0Mode = UART_MODE_ACK_OUT_STATUS_IN;
}


/*******************************************************************************
* Function Name: UART_ControlWriteStatusStage
********************************************************************************
*
* Summary:
*  Handle the Status Stage of a control write transfer
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  UART_transferState - set to TRANS_STATE_IDLE.
*  UART_USBFS_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_ControlWriteStatusStage(void) 
{
    /* Go Idle */
    UART_transferState = UART_TRANS_STATE_IDLE;
    /* Update the completion block */
    UART_UpdateStatusBlock(UART_XFER_STATUS_ACK);
    /* We expect no more data, so stall INs and OUTs */
    UART_ep0Mode = UART_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: UART_InitNoDataControlTransfer
********************************************************************************
*
* Summary:
*  Initialize a no data control transfer
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  UART_transferState - set to TRANS_STATE_NO_DATA_CONTROL.
*  UART_ep0Mode  - set to MODE_STATUS_IN_ONLY.
*  UART_ep0Count - cleared.
*  UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 UART_InitNoDataControlTransfer(void) 
{
    UART_transferState = UART_TRANS_STATE_NO_DATA_CONTROL;
    UART_ep0Mode = UART_MODE_STATUS_IN_ONLY;
    UART_ep0Toggle = UART_EP0_CNT_DATA_TOGGLE;
    UART_ep0Count = 0u;

    return(UART_TRUE);
}


/*******************************************************************************
* Function Name: UART_NoDataControlStatusStage
********************************************************************************
* Summary:
*  Handle the Status Stage of a no data control transfer.
*
*  SET_ADDRESS is special, since we need to receive the status stage with
*  the old address.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  UART_transferState - set to TRANS_STATE_IDLE.
*  UART_ep0Mode  - set to MODE_STALL_IN_OUT.
*  UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  UART_deviceAddress - used to set new address and cleared
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_NoDataControlStatusStage(void) 
{
    /* Change the USB address register if we got a SET_ADDRESS. */
    if (UART_deviceAddress != 0u)
    {
        CY_SET_REG8(UART_CR0_PTR, UART_deviceAddress | UART_CR0_ENABLE);
        UART_deviceAddress = 0u;
    }
    /* Go Idle */
    UART_transferState = UART_TRANS_STATE_IDLE;
    /* Update the completion block */
    UART_UpdateStatusBlock(UART_XFER_STATUS_ACK);
     /* We expect no more data, so stall INs and OUTs */
    UART_ep0Mode = UART_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: UART_UpdateStatusBlock
********************************************************************************
*
* Summary:
*  Update the Completion Status Block for a Request.  The block is updated
*  with the completion code the UART_transferByteCount.  The
*  StatusBlock Pointer is set to NULL.
*
* Parameters:
*  completionCode - status.
*
* Return:
*  None.
*
* Global variables:
*  UART_currentTD.pStatusBlock->status - updated by the
*    completionCode parameter.
*  UART_currentTD.pStatusBlock->length - updated.
*  UART_currentTD.pStatusBlock - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_UpdateStatusBlock(uint8 completionCode) 
{
    if (UART_currentTD.pStatusBlock != NULL)
    {
        UART_currentTD.pStatusBlock->status = completionCode;
        UART_currentTD.pStatusBlock->length = UART_transferByteCount;
        UART_currentTD.pStatusBlock = NULL;
    }
}


/*******************************************************************************
* Function Name: UART_InitializeStatusBlock
********************************************************************************
*
* Summary:
*  Initialize the Completion Status Block for a Request.  The completion
*  code is set to USB_XFER_IDLE.
*
*  Also, initializes UART_transferByteCount.  Save some space,
*  this is the only consumer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  UART_currentTD.pStatusBlock->status - set to XFER_IDLE.
*  UART_currentTD.pStatusBlock->length - cleared.
*  UART_transferByteCount - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_InitializeStatusBlock(void) 
{
    UART_transferByteCount = 0u;
    if(UART_currentTD.pStatusBlock != NULL)
    {
        UART_currentTD.pStatusBlock->status = UART_XFER_IDLE;
        UART_currentTD.pStatusBlock->length = 0u;
    }
}


/* [] END OF FILE */
