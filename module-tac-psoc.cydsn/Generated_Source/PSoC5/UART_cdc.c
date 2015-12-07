/*******************************************************************************
* File Name: UART_cdc.c
* Version 2.80
*
* Description:
*  USB CDC class request handler.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* Copyright 2012-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART.h"

#if defined(UART_ENABLE_CDC_CLASS)

#include "UART_cdc.h"
#include "UART_pvt.h"



/***************************************
*    CDC Variables
***************************************/

volatile uint8 UART_lineCoding[UART_LINE_CODING_SIZE] =
{
    0x00u, 0xC2u, 0x01u, 0x00u,     /* Data terminal rate 115200 */
    0x00u,                          /* 1 Stop bit */
    0x00u,                          /* None parity */
    0x08u                           /* 8 data bits */
};
volatile uint8 UART_lineChanged;
volatile uint16 UART_lineControlBitmap;
volatile uint8 UART_cdc_data_in_ep;
volatile uint8 UART_cdc_data_out_ep;


/***************************************
*     Static Function Prototypes
***************************************/
#if (UART_ENABLE_CDC_CLASS_API != 0u)
    static uint16 UART_StrLen(const char8 string[]) ;
#endif /* (UART_ENABLE_CDC_CLASS_API != 0u) */


/***************************************
* Custom Declarations
***************************************/

/* `#START CDC_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: UART_DispatchCDCClassRqst
********************************************************************************
*
* Summary:
*  This routine dispatches CDC class requests.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled
*
* Global variables:
*   UART_lineCoding: Contains the current line coding structure.
*     It is set by the Host using SET_LINE_CODING request and returned to the
*     user code by the USBFS_GetDTERate(), USBFS_GetCharFormat(),
*     USBFS_GetParityType(), USBFS_GetDataBits() APIs.
*   UART_lineControlBitmap: Contains the current control signal
*     bitmap. It is set by the Host using SET_CONTROL_LINE request and returned
*     to the user code by the USBFS_GetLineControl() API.
*   UART_lineChanged: This variable is used as a flag for the
*     USBFS_IsLineChanged() API, to be aware that Host has been sent request
*     for changing Line Coding or Control Bitmap.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 UART_DispatchCDCClassRqst(void) 
{
    uint8 requestHandled = UART_FALSE;

    if ((CY_GET_REG8(UART_bmRequestType) & UART_RQST_DIR_MASK) == UART_RQST_DIR_D2H)
    {   /* Control Read */
        switch (CY_GET_REG8(UART_bRequest))
        {
            case UART_CDC_GET_LINE_CODING:
                UART_currentTD.count = UART_LINE_CODING_SIZE;
                UART_currentTD.pData = UART_lineCoding;
                requestHandled  = UART_InitControlRead();
                break;

            /* `#START CDC_READ_REQUESTS` Place other request handler here */

            /* `#END` */

            #ifdef UART_DISPATCH_CDC_CLASS_CDC_READ_REQUESTS_CALLBACK
                UART_DispatchCDCClass_CDC_READ_REQUESTS_Callback();
            #endif /* UART_DISPATCH_CDC_CLASS_CDC_READ_REQUESTS_CALLBACK */

            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else if ((CY_GET_REG8(UART_bmRequestType) & UART_RQST_DIR_MASK) == \
                                                                            UART_RQST_DIR_H2D)
    {   /* Control Write */
        switch (CY_GET_REG8(UART_bRequest))
        {
            case UART_CDC_SET_LINE_CODING:
                UART_currentTD.count = UART_LINE_CODING_SIZE;
                UART_currentTD.pData = UART_lineCoding;
                UART_lineChanged |= UART_LINE_CODING_CHANGED;
                requestHandled = UART_InitControlWrite();
                break;

            case UART_CDC_SET_CONTROL_LINE_STATE:
                UART_lineControlBitmap = CY_GET_REG8(UART_wValueLo);
                UART_lineChanged |= UART_LINE_CONTROL_CHANGED;
                requestHandled = UART_InitNoDataControlTransfer();
                break;

            /* `#START CDC_WRITE_REQUESTS` Place other request handler here */

            /* `#END` */

            #ifdef UART_DISPATCH_CDC_CLASS_CDC_WRITE_REQUESTS_CALLBACK
                UART_DispatchCDCClass_CDC_WRITE_REQUESTS_Callback();
            #endif /* UART_DISPATCH_CDC_CLASS_CDC_WRITE_REQUESTS_CALLBACK */

            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {   /* requestHandled is initialized as FALSE by default */
    }

    return(requestHandled);
}


/***************************************
* Optional CDC APIs
***************************************/
#if (UART_ENABLE_CDC_CLASS_API != 0u)

    /*******************************************************************************
    * Function Name: UART_CDC_Init
    ********************************************************************************
    *
    * Summary:
    *  This function initialize the CDC interface to be ready for the receive data
    *  from the PC.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   UART_lineChanged: Initialized to zero.
    *   UART_cdc_data_out_ep: Used as an OUT endpoint number.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UART_CDC_Init(void) 
    {
        UART_lineChanged = 0u;
        UART_EnableOutEP(UART_cdc_data_out_ep);
    }


    /*******************************************************************************
    * Function Name: UART_PutData
    ********************************************************************************
    *
    * Summary:
    *  This function sends a specified number of bytes from the location specified
    *  by a pointer to the PC. The UART_CDCIsReady() function should be
    *  called before sending new data, to be sure that the previous data has
    *  finished sending.
    *  If the last sent packet is less than maximum packet size the USB transfer
    *  of this short packet will identify the end of the segment. If the last sent
    *  packet is exactly maximum packet size, it shall be followed by a zero-length
    *  packet (which is a short packet) to assure the end of segment is properly
    *  identified. To send zero-length packet, use UART_PutData() API
    *  with length parameter set to zero.
    *
    * Parameters:
    *  pData: pointer to the buffer containing data to be sent.
    *  length: Specifies the number of bytes to send from the pData
    *  buffer. Maximum length will be limited by the maximum packet
    *  size for the endpoint. Data will be lost if length is greater than Max
    *  Packet Size.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   UART_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UART_PutData(const uint8* pData, uint16 length) 
    {
        /* Limits length to maximum packet size for the EP */
        if(length > UART_EP[UART_cdc_data_in_ep].bufferSize)
        {
            /* Caution: Data will be lost if length is greater than Max Packet Length */
            length = UART_EP[UART_cdc_data_in_ep].bufferSize;
             /* Halt CPU in debug mode */
            CYASSERT(0u != 0u);
        }
        UART_LoadInEP(UART_cdc_data_in_ep, pData, length);
    }


    /*******************************************************************************
    * Function Name: UART_StrLen
    ********************************************************************************
    *
    * Summary:
    *  Calculates length of a null terminated string.
    *
    * Parameters:
    *  string: pointer to the string.
    *
    * Return:
    *  Length of the string
    *
    *******************************************************************************/
    static uint16 UART_StrLen(const char8 string[]) 
    {
        uint16 len = 0u;

        while (string[len] != (char8)0)
        {
            len++;
        }

        return (len);
    }


    /*******************************************************************************
    * Function Name: UART_PutString
    ********************************************************************************
    *
    * Summary:
    *  This function sends a null terminated string to the PC. This function will
    *  block if there is not enough memory to place the whole string. It will block
    *  until the entire string has been written to the transmit buffer.
    *  The USBUART_CDCIsReady() function should be called before sending data with
    *  a new call to UART_PutString(), to be sure that the previous data
    *  has finished sending.
    *
    * Parameters:
    *  string: pointer to the string to be sent to the PC.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   UART_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UART_PutString(const char8 string[]) 
    {
        uint16 strLength;
        uint16 sendLength;
        uint16 bufIndex = 0u;

        /* Get length of the null terminated string */
        strLength = UART_StrLen(string);
        do
        {
            /* Limits length to maximum packet size for the EP */
            sendLength = (strLength > UART_EP[UART_cdc_data_in_ep].bufferSize) ?
                          UART_EP[UART_cdc_data_in_ep].bufferSize : strLength;
             /* Enable IN transfer */
            UART_LoadInEP(UART_cdc_data_in_ep, (const uint8 *)&string[bufIndex], sendLength);
            strLength -= sendLength;

            /* If more data are present to send or full packet was sent */
            if((strLength > 0u) || (sendLength == UART_EP[UART_cdc_data_in_ep].bufferSize))
            {
                bufIndex += sendLength;
                /* Wait for the Host to read it. */
                while(UART_EP[UART_cdc_data_in_ep].apiEpState ==
                                          UART_IN_BUFFER_FULL)
                {
                    ;
                }
                /* If the last sent packet is exactly maximum packet size,
                *  it shall be followed by a zero-length packet to assure the
                *  end of segment is properly identified by the terminal.
                */
                if(strLength == 0u)
                {
                    UART_LoadInEP(UART_cdc_data_in_ep, NULL, 0u);
                }
            }
        }while(strLength > 0u);
    }


    /*******************************************************************************
    * Function Name: UART_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Writes a single character to the PC.
    *
    * Parameters:
    *  txDataByte: Character to be sent to the PC.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   UART_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UART_PutChar(char8 txDataByte) 
    {
        uint8 dataByte;
        dataByte = (uint8)txDataByte;

        UART_LoadInEP(UART_cdc_data_in_ep, &dataByte, 1u);
    }


    /*******************************************************************************
    * Function Name: UART_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Sends a carriage return (0x0D) and line feed (0x0A) to the PC
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   UART_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UART_PutCRLF(void) 
    {
        const uint8 CYCODE txData[] = {0x0Du, 0x0Au};

        UART_LoadInEP(UART_cdc_data_in_ep, (const uint8 *)txData, 2u);
    }


    /*******************************************************************************
    * Function Name: UART_GetCount
    ********************************************************************************
    *
    * Summary:
    *  This function returns the number of bytes that were received from the PC.
    *  The returned length value should be passed to UART_GetData() as
    *  a parameter to read all received data. If all of the received data is not
    *  read at one time by the UART_GetData() API, the unread data will
    *  be lost.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of received bytes. The maximum amount of received data at
    *  a time is limited by the maximum packet size for the endpoint.
    *
    * Global variables:
    *   UART_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    *******************************************************************************/
    uint16 UART_GetCount(void) 
    {
        uint16 bytesCount;

        if (UART_EP[UART_cdc_data_out_ep].apiEpState == UART_OUT_BUFFER_FULL)
        {
            bytesCount = UART_GetEPCount(UART_cdc_data_out_ep);
        }
        else
        {
            bytesCount = 0u;
        }

        return(bytesCount);
    }


    /*******************************************************************************
    * Function Name: UART_DataIsReady
    ********************************************************************************
    *
    * Summary:
    *  Returns a nonzero value if the component received data or received
    *  zero-length packet. The UART_GetAll() or
    *  UART_GetData() API should be called to read data from the buffer
    *  and re-init OUT endpoint even when zero-length packet received.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If the OUT packet received this function returns a nonzero value.
    *  Otherwise zero is returned.
    *
    * Global variables:
    *   UART_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    *******************************************************************************/
    uint8 UART_DataIsReady(void) 
    {
        return(UART_EP[UART_cdc_data_out_ep].apiEpState);
    }


    /*******************************************************************************
    * Function Name: UART_CDCIsReady
    ********************************************************************************
    *
    * Summary:
    *  This function returns a nonzero value if the component is ready to send more
    *  data to the PC; otherwise, it returns zero. The function should be called
    *  before sending new data when using any of the following APIs:
    *  UART_PutData(),UART_PutString(),
    *  UART_PutChar or UART_PutCRLF(),
    *  to be sure that the previous data has finished sending.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If the buffer can accept new data, this function returns a nonzero value.
    *  Otherwise, it returns zero.
    *
    * Global variables:
    *   UART_cdc_data_in_ep: CDC IN endpoint number used.
    *
    *******************************************************************************/
    uint8 UART_CDCIsReady(void) 
    {
        return(UART_EP[UART_cdc_data_in_ep].apiEpState);
    }


    /*******************************************************************************
    * Function Name: UART_GetData
    ********************************************************************************
    *
    * Summary:
    *  This function gets a specified number of bytes from the input buffer and
    *  places them in a data array specified by the passed pointer.
    *  The UART_DataIsReady() API should be called first, to be sure
    *  that data is received from the host. If all received data will not be read at
    *  once, the unread data will be lost. The UART_GetData() API should
    *  be called to get the number of bytes that were received.
    *
    * Parameters:
    *  pData: Pointer to the data array where data will be placed.
    *  Length: Number of bytes to read into the data array from the RX buffer.
    *          Maximum length is limited by the the number of received bytes.
    *
    * Return:
    *  Number of bytes received.
    *
    * Global variables:
    *   UART_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 UART_GetData(uint8* pData, uint16 length) 
    {
        return(UART_ReadOutEP(UART_cdc_data_out_ep, pData, length));
    }


    /*******************************************************************************
    * Function Name: UART_GetAll
    ********************************************************************************
    *
    * Summary:
    *  Gets all bytes of received data from the input buffer and places it into a
    *  specified data array. UART_DataIsReady() API should be called
    *  before, to be sure that data is received from the Host.
    *
    * Parameters:
    *  pData: Pointer to the data array where data will be placed.
    *
    * Return:
    *  Number of bytes received.
    *
    * Global variables:
    *   UART_cdc_data_out_ep: CDC OUT endpoint number used.
    *   UART_EP[].bufferSize: EP max packet size is used as a length
    *     to read all data from the EP buffer.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 UART_GetAll(uint8* pData) 
    {
        return (UART_ReadOutEP(UART_cdc_data_out_ep, pData,
                                           UART_EP[UART_cdc_data_out_ep].bufferSize));
    }


    /*******************************************************************************
    * Function Name: UART_GetChar
    ********************************************************************************
    *
    * Summary:
    *  This function reads one byte of received data from the buffer. If more than
    *  one byte has been received from the host, the rest of the data will be lost.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received one character.
    *
    * Global variables:
    *   UART_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 UART_GetChar(void) 
    {
         uint8 rxData;

        (void) UART_ReadOutEP(UART_cdc_data_out_ep, &rxData, 1u);

        return(rxData);
    }

    /*******************************************************************************
    * Function Name: UART_IsLineChanged
    ********************************************************************************
    *
    * Summary:
    *  This function returns clear on read status of the line. It returns not zero
    *  value when the host sends updated coding or control information to the
    *  device. The UART_GetDTERate(), UART_GetCharFormat()
    *  or UART_GetParityType() or UART_GetDataBits() API
    *  should be called to read data coding information.
    *  The UART_GetLineControl() API should be called to read line
    *  control information.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If SET_LINE_CODING or CDC_SET_CONTROL_LINE_STATE requests are received, it
    *  returns a nonzero value. Otherwise, it returns zero.
    *
    * Global variables:
    *  UART_transferState: it is checked to be sure then OUT data
    *    phase has been complete, and data written to the lineCoding or Control
    *    Bitmap buffer.
    *  UART_lineChanged: used as a flag to be aware that Host has been
    *    sent request for changing Line Coding or Control Bitmap.
    *
    *******************************************************************************/
    uint8 UART_IsLineChanged(void) 
    {
        uint8 state = 0u;

        /* transferState is checked to be sure then OUT data phase has been complete */
        if(UART_transferState == UART_TRANS_STATE_IDLE)
        {
            if(UART_lineChanged != 0u)
            {
                state = UART_lineChanged;
                UART_lineChanged = 0u;
            }
        }

        return(state);
    }


    /*******************************************************************************
    * Function Name: UART_GetDTERate
    ********************************************************************************
    *
    * Summary:
    *  Returns the data terminal rate set for this port in bits per second.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns a uint32 value of the data rate in bits per second.
    *
    * Global variables:
    *  UART_lineCoding: First four bytes converted to uint32
    *    depend on compiler, and returned as a data rate.
    *
    *******************************************************************************/
    uint32 UART_GetDTERate(void) 
    {
        uint32 rate;

        rate = UART_lineCoding[UART_LINE_CODING_RATE + 3u];
        rate = (rate << 8u) | UART_lineCoding[UART_LINE_CODING_RATE + 2u];
        rate = (rate << 8u) | UART_lineCoding[UART_LINE_CODING_RATE + 1u];
        rate = (rate << 8u) | UART_lineCoding[UART_LINE_CODING_RATE];

        return(rate);
    }


    /*******************************************************************************
    * Function Name: UART_GetCharFormat
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of stop bits.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of stop bits.
    *
    * Global variables:
    *  UART_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 UART_GetCharFormat(void) 
    {
        return(UART_lineCoding[UART_LINE_CODING_STOP_BITS]);
    }


    /*******************************************************************************
    * Function Name: UART_GetParityType
    ********************************************************************************
    *
    * Summary:
    *  Returns the parity type for the CDC port.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the parity type.
    *
    * Global variables:
    *  UART_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 UART_GetParityType(void) 
    {
        return(UART_lineCoding[UART_LINE_CODING_PARITY]);
    }


    /*******************************************************************************
    * Function Name: UART_GetDataBits
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of data bits for the CDC port.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of data bits.
    *  The number of data bits can be 5, 6, 7, 8 or 16.
    *
    * Global variables:
    *  UART_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 UART_GetDataBits(void) 
    {
        return(UART_lineCoding[UART_LINE_CODING_DATA_BITS]);
    }


    /*******************************************************************************
    * Function Name: UART_GetLineControl
    ********************************************************************************
    *
    * Summary:
    *  Returns Line control bitmap.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns Line control bitmap.
    *
    * Global variables:
    *  UART_lineControlBitmap: used to get a parameter.
    *
    *******************************************************************************/
    uint16 UART_GetLineControl(void) 
    {
        return(UART_lineControlBitmap);
    }

#endif  /*  UART_ENABLE_CDC_CLASS_API*/


/*******************************************************************************
* Additional user functions supporting CDC Requests
********************************************************************************/

/* `#START CDC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /*  UART_ENABLE_CDC_CLASS*/


/* [] END OF FILE */
