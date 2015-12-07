/*******************************************************************************
* File Name: UART_cdc.h
* Version 2.80
*
* Description:
*  Header File for the USBFS component.
*  Contains CDC class prototypes and constant values.
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

#if !defined(CY_USBFS_UART_cdc_H)
#define CY_USBFS_UART_cdc_H

#include "cytypes.h"


/***************************************
* Prototypes of the UART_cdc API.
***************************************/

#if (UART_ENABLE_CDC_CLASS_API != 0u)
    void UART_CDC_Init(void) ;
    void UART_PutData(const uint8* pData, uint16 length) ;
    void UART_PutString(const char8 string[]) ;
    void UART_PutChar(char8 txDataByte) ;
    void UART_PutCRLF(void) ;
    uint16 UART_GetCount(void) ;
    uint8 UART_CDCIsReady(void) ;
    uint8 UART_DataIsReady(void) ;
    uint16 UART_GetData(uint8* pData, uint16 length) ;
    uint16 UART_GetAll(uint8* pData) ;
    uint8 UART_GetChar(void) ;
    uint8 UART_IsLineChanged(void) ;
    uint32 UART_GetDTERate(void) ;
    uint8 UART_GetCharFormat(void) ;
    uint8 UART_GetParityType(void) ;
    uint8 UART_GetDataBits(void) ;
    uint16 UART_GetLineControl(void) ;
#endif  /*  UART_ENABLE_CDC_CLASS_API */


/***************************************
*  Constants for UART_cdc API.
***************************************/

/* CDC Class-Specific Request Codes (CDC ver 1.2 Table 19) */
#define UART_CDC_SET_LINE_CODING        (0x20u)
#define UART_CDC_GET_LINE_CODING        (0x21u)
#define UART_CDC_SET_CONTROL_LINE_STATE (0x22u)

#define UART_LINE_CODING_CHANGED        (0x01u)
#define UART_LINE_CONTROL_CHANGED       (0x02u)

#define UART_1_STOPBIT                  (0x00u)
#define UART_1_5_STOPBITS               (0x01u)
#define UART_2_STOPBITS                 (0x02u)

#define UART_PARITY_NONE                (0x00u)
#define UART_PARITY_ODD                 (0x01u)
#define UART_PARITY_EVEN                (0x02u)
#define UART_PARITY_MARK                (0x03u)
#define UART_PARITY_SPACE               (0x04u)

#define UART_LINE_CODING_SIZE           (0x07u)
#define UART_LINE_CODING_RATE           (0x00u)
#define UART_LINE_CODING_STOP_BITS      (0x04u)
#define UART_LINE_CODING_PARITY         (0x05u)
#define UART_LINE_CODING_DATA_BITS      (0x06u)

#define UART_LINE_CONTROL_DTR           (0x01u)
#define UART_LINE_CONTROL_RTS           (0x02u)


/***************************************
* External data references
***************************************/

extern volatile uint8 UART_lineCoding[UART_LINE_CODING_SIZE];
extern volatile uint8 UART_lineChanged;
extern volatile uint16 UART_lineControlBitmap;
extern volatile uint8 UART_cdc_data_in_ep;
extern volatile uint8 UART_cdc_data_out_ep;

#endif /*  CY_USBFS_UART_cdc_H */


/* [] END OF FILE */
