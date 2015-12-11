/*******************************************************************************
* File Name: UART_boot.c
* Version 2.80
*
* Description:
*  Boot loader API for USBFS Component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*    Bootloader Variables
***************************************/

static uint8  UART_started = 0u;


/*******************************************************************************
* Function Name: UART_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Starts the component and enables the interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  This function starts the USB with 3V or 5V operation.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_CyBtldrCommStart(void) 
{
    CyGlobalIntEnable;      /* Enable Global Interrupts */

    /*Start USBFS Operation/device 0 and with 5V or 3V operation depend on Voltage Configuration in DWR */
    UART_Start(0u, UART_DWR_VDDD_OPERATION);

    /* USB component started, the correct enumeration will be checked in first Read operation */
    UART_started = 1u;
}


/*******************************************************************************
* Function Name: UART_CyBtldrCommStop.
********************************************************************************
*
* Summary:
*  Disable the component and disable the interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void UART_CyBtldrCommStop(void) 
{
    UART_Stop();
}


/*******************************************************************************
* Function Name: UART_CyBtldrCommReset.
********************************************************************************
*
* Summary:
*  Resets the receive and transmit communication Buffers.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void UART_CyBtldrCommReset(void) 
{
    UART_EnableOutEP(UART_BTLDR_OUT_EP);  /* Enable the OUT endpoint */
}


/*******************************************************************************
* Function Name: UART_CyBtldrCommWrite.
********************************************************************************
*
* Summary:
*  Allows the caller to write data to the boot loader host. The function will
*  handle polling to allow a block of data to be completely sent to the host
*  device.
*
* Parameters:
*  pData:    A pointer to the block of data to send to the device
*  size:     The number of bytes to write.
*  count:    Pointer to an unsigned short variable to write the number of
*             bytes actually written.
*  timeOut:  Number of units to wait before returning because of a timeout.
*
* Return:
*  Returns the value that best describes the problem.
*
* Reentrant:
*  No
*
*******************************************************************************/
cystatus UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                            
{
    cystatus retCode;
    uint16 timeoutMs;

    timeoutMs = ((uint16) 10u * timeOut);  /* Convert from 10mS check to number 1mS checks */

    /* Enable IN transfer */
    UART_LoadInEP(UART_BTLDR_IN_EP, pData, UART_BTLDR_SIZEOF_READ_BUFFER);

    /* Wait for the master to read it. */
    while ((UART_GetEPState(UART_BTLDR_IN_EP) == UART_IN_BUFFER_FULL) &&
           (0u != timeoutMs))
    {
        CyDelay(UART_BTLDR_WAIT_1_MS);
        timeoutMs--;
    }

    if (UART_GetEPState(UART_BTLDR_IN_EP) == UART_IN_BUFFER_FULL)
    {
        retCode = CYRET_TIMEOUT;
    }
    else
    {
        *count = size;
        retCode = CYRET_SUCCESS;
    }

    return(retCode);
}


/*******************************************************************************
* Function Name: UART_CyBtldrCommRead.
********************************************************************************
*
* Summary:
*  Allows the caller to read data from the boot loader host. The function will
*  handle polling to allow a block of data to be completely received from the
*  host device.
*
* Parameters:
*  pData:    A pointer to the area to store the block of data received
*             from the device.
*  size:     The number of bytes to read.
*  count:    Pointer to an unsigned short variable to write the number
*             of bytes actually read.
*  timeOut:  Number of units to wait before returning because of a timeOut.
*            Timeout is measured in 10s of ms.
*
* Return:
*  Returns the value that best describes the problem.
*
* Reentrant:
*  No
*
*******************************************************************************/
cystatus UART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                            
{
    cystatus retCode;
    uint16 timeoutMs;

    timeoutMs = ((uint16) 10u * timeOut);  /* Convert from 10mS check to number 1mS checks */

    if (size > UART_BTLDR_SIZEOF_WRITE_BUFFER)
    {
        size = UART_BTLDR_SIZEOF_WRITE_BUFFER;
    }

    /* Wait on enumeration in first time */
    if (0u != UART_started)
    {
        /* Wait for Device to enumerate */
        while ((0u ==UART_GetConfiguration()) && (0u != timeoutMs))
        {
            CyDelay(UART_BTLDR_WAIT_1_MS);
            timeoutMs--;
        }

        /* Enable first OUT, if enumeration complete */
        if (0u != UART_GetConfiguration())
        {
            (void) UART_IsConfigurationChanged();  /* Clear configuration changes state status */
            UART_CyBtldrCommReset();
            UART_started = 0u;
        }
    }
    else /* Check for configuration changes, has been done by Host */
    {
        if (0u != UART_IsConfigurationChanged()) /* Host could send double SET_INTERFACE request or RESET */
        {
            if (0u != UART_GetConfiguration())   /* Init OUT endpoints when device reconfigured */
            {
                UART_CyBtldrCommReset();
            }
        }
    }

    timeoutMs = ((uint16) 10u * timeOut); /* Re-arm timeout */

    /* Wait on next packet */
    while((UART_GetEPState(UART_BTLDR_OUT_EP) != UART_OUT_BUFFER_FULL) && \
          (0u != timeoutMs))
    {
        CyDelay(UART_BTLDR_WAIT_1_MS);
        timeoutMs--;
    }

    /* OUT EP has completed */
    if (UART_GetEPState(UART_BTLDR_OUT_EP) == UART_OUT_BUFFER_FULL)
    {
        *count = UART_ReadOutEP(UART_BTLDR_OUT_EP, pData, size);
        retCode = CYRET_SUCCESS;
    }
    else
    {
        *count = 0u;
        retCode = CYRET_TIMEOUT;
    }

    return(retCode);
}

#endif /*  CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART */


/* [] END OF FILE */
