/*******************************************************************************
* File Name: UART_vnd.c
* Version 2.80
*
* Description:
*  USB vendor request handler.
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


#if(UART_EXTERN_VND == UART_FALSE)


/***************************************
* Vendor Specific Declarations
***************************************/

/* `#START VENDOR_SPECIFIC_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: UART_HandleVendorRqst
********************************************************************************
*
* Summary:
*  This routine provide users with a method to implement vendor specific
*  requests.
*
*  To implement vendor specific requests, add your code in this function to
*  decode and disposition the request.  If the request is handled, your code
*  must set the variable "requestHandled" to TRUE, indicating that the
*  request has been handled.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 UART_HandleVendorRqst(void) 
{
    uint8 requestHandled = UART_FALSE;

    if ((CY_GET_REG8(UART_bmRequestType) & UART_RQST_DIR_MASK) == UART_RQST_DIR_D2H)
    {
        /* Control Read */
        switch (CY_GET_REG8(UART_bRequest))
        {
            case UART_GET_EXTENDED_CONFIG_DESCRIPTOR:
                #if defined(UART_ENABLE_MSOS_STRING)
                    UART_currentTD.pData = (volatile uint8 *)&UART_MSOS_CONFIGURATION_DESCR[0u];
                    UART_currentTD.count = UART_MSOS_CONFIGURATION_DESCR[0u];
                    requestHandled  = UART_InitControlRead();
                #endif /*  UART_ENABLE_MSOS_STRING */
                break;
            default:
                break;
        }
    }

    /* `#START VENDOR_SPECIFIC_CODE` Place your vendor specific request here */

    /* `#END` */

    #ifdef UART_HANDLE_VENDOR_RQST_CALLBACK
        UART_HandleVendorRqst_Callback();
    #endif /* UART_HANDLE_VENDOR_RQST_CALLBACK */

    return(requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Vendor Specific Requests
********************************************************************************/

/* `#START VENDOR_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif /* UART_EXTERN_VND */


/* [] END OF FILE */
