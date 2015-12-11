/*******************************************************************************
* File Name: UART_cls.c
* Version 2.80
*
* Description:
*  USB Class request handler.
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

#if(UART_EXTERN_CLS == UART_FALSE)

#include "UART_pvt.h"



/***************************************
* User Implemented Class Driver Declarations.
***************************************/
/* `#START USER_DEFINED_CLASS_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: UART_DispatchClassRqst
********************************************************************************
* Summary:
*  This routine dispatches class specific requests depend on interface class.
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
uint8 UART_DispatchClassRqst(void) 
{
    uint8 requestHandled = UART_FALSE;
    uint8 interfaceNumber = 0u;

    switch(CY_GET_REG8(UART_bmRequestType) & UART_RQST_RCPT_MASK)
    {
        case UART_RQST_RCPT_IFC:        /* Class-specific request directed to an interface */
            interfaceNumber = CY_GET_REG8(UART_wIndexLo); /* wIndexLo contain Interface number */
            break;
        case UART_RQST_RCPT_EP:         /* Class-specific request directed to the endpoint */
            /* Find related interface to the endpoint, wIndexLo contain EP number */
            interfaceNumber = UART_EP[CY_GET_REG8(UART_wIndexLo) &
                              UART_DIR_UNUSED].interface;
            break;
        default:    /* RequestHandled is initialized as FALSE by default */
            break;
    }
    /* Handle Class request depend on interface type */
    switch(UART_interfaceClass[interfaceNumber])
    {
        case UART_CLASS_HID:
            #if defined(UART_ENABLE_HID_CLASS)
                requestHandled = UART_DispatchHIDClassRqst();
            #endif /* UART_ENABLE_HID_CLASS */
            break;
        case UART_CLASS_AUDIO:
            #if defined(UART_ENABLE_AUDIO_CLASS)
                requestHandled = UART_DispatchAUDIOClassRqst();
            #endif /* UART_CLASS_AUDIO */
            break;
        case UART_CLASS_CDC:
            #if defined(UART_ENABLE_CDC_CLASS)
                requestHandled = UART_DispatchCDCClassRqst();
            #endif /* UART_ENABLE_CDC_CLASS */
            break;
        default:    /* requestHandled is initialized as FALSE by default */
            break;
    }

    /* `#START USER_DEFINED_CLASS_CODE` Place your Class request here */

    /* `#END` */

    #ifdef UART_DISPATCH_CLASS_RQST_CALLBACK
        UART_DispatchClassRqst_Callback();
    #endif /* UART_DISPATCH_CLASS_RQST_CALLBACK */

    return(requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Class Specific Requests
********************************************************************************/

/* `#START CLASS_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif /* UART_EXTERN_CLS */


/* [] END OF FILE */
