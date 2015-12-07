/*******************************************************************************
* File Name: .h
* Version 2.80
*
* Description:
*  This private file provides constants and parameter values for the
*  USBFS Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_UART_pvt_H)
#define CY_USBFS_UART_pvt_H


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors*/
extern const uint8 CYCODE UART_DEVICE0_DESCR[18u];
extern const uint8 CYCODE UART_DEVICE0_CONFIGURATION0_DESCR[67u];
extern const T_UART_EP_SETTINGS_BLOCK CYCODE UART_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[3u];
extern const uint8 CYCODE UART_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[2u];
extern const T_UART_LUT CYCODE UART_DEVICE0_CONFIGURATION0_TABLE[5u];
extern const T_UART_LUT CYCODE UART_DEVICE0_TABLE[2u];
extern const T_UART_LUT CYCODE UART_TABLE[1u];
extern const uint8 CYCODE UART_SN_STRING_DESCRIPTOR[2];
extern const uint8 CYCODE UART_STRING_DESCRIPTORS[159u];


extern const uint8 CYCODE UART_MSOS_DESCRIPTOR[UART_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE UART_MSOS_CONFIGURATION_DESCR[UART_MSOS_CONF_DESCR_LENGTH];
#if defined(UART_ENABLE_IDSN_STRING)
    extern uint8 UART_idSerialNumberStringDescriptor[UART_IDSN_DESCR_LENGTH];
#endif /* UART_ENABLE_IDSN_STRING */

extern volatile uint8 UART_interfaceNumber;
extern volatile uint8 UART_interfaceSetting[UART_MAX_INTERFACES_NUMBER];
extern volatile uint8 UART_interfaceSetting_last[UART_MAX_INTERFACES_NUMBER];
extern volatile uint8 UART_deviceAddress;
extern volatile uint8 UART_interfaceStatus[UART_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *UART_interfaceClass;

extern volatile T_UART_EP_CTL_BLOCK UART_EP[UART_MAX_EP];
extern volatile T_UART_TD UART_currentTD;

#if(UART_EP_MM != UART__EP_MANUAL)
    extern uint8 UART_DmaChan[UART_MAX_EP];
    extern uint8 UART_DmaTd[UART_MAX_EP];
#endif /*  UART_EP_MM */
#if((UART_EP_MM == UART__EP_DMAAUTO) && (UART_EP_DMA_AUTO_OPT == 0u))
    extern uint8 UART_DmaNextTd[UART_MAX_EP];
    extern const uint8 UART_epX_TD_TERMOUT_EN[UART_MAX_EP];
    extern volatile uint16 UART_inLength[UART_MAX_EP];
    extern const uint8 *UART_inDataPointer[UART_MAX_EP];
    extern volatile uint8 UART_inBufFull[UART_MAX_EP];
#endif /*  ((UART_EP_MM == UART__EP_DMAAUTO) && (UART_EP_DMA_AUTO_OPT == 0u)) */

extern volatile uint8 UART_ep0Toggle;
extern volatile uint8 UART_lastPacketSize;
extern volatile uint8 UART_ep0Mode;
extern volatile uint8 UART_ep0Count;
extern volatile uint16 UART_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  UART_ReInitComponent(void) ;
void  UART_HandleSetup(void) ;
void  UART_HandleIN(void) ;
void  UART_HandleOUT(void) ;
void  UART_LoadEP0(void) ;
uint8 UART_InitControlRead(void) ;
uint8 UART_InitControlWrite(void) ;
void  UART_ControlReadDataStage(void) ;
void  UART_ControlReadStatusStage(void) ;
void  UART_ControlReadPrematureStatus(void)
                                                ;
uint8 UART_InitControlWrite(void) ;
uint8 UART_InitZeroLengthControlTransfer(void)
                                                ;
void  UART_ControlWriteDataStage(void) ;
void  UART_ControlWriteStatusStage(void) ;
void  UART_ControlWritePrematureStatus(void)
                                                ;
uint8 UART_InitNoDataControlTransfer(void) ;
void  UART_NoDataControlStatusStage(void) ;
void  UART_InitializeStatusBlock(void) ;
void  UART_UpdateStatusBlock(uint8 completionCode) ;
uint8 UART_DispatchClassRqst(void) ;

void UART_Config(uint8 clearAltSetting) ;
void UART_ConfigAltChanged(void) ;
void UART_ConfigReg(void) ;

const T_UART_LUT CYCODE *UART_GetConfigTablePtr(uint8 confIndex)
                                                            ;
const T_UART_LUT CYCODE *UART_GetDeviceTablePtr(void)
                                                            ;
const uint8 CYCODE *UART_GetInterfaceClassTablePtr(void)
                                                    ;
uint8 UART_ClearEndpointHalt(void) ;
uint8 UART_SetEndpointHalt(void) ;
uint8 UART_ValidateAlternateSetting(void) ;

void UART_SaveConfig(void) ;
void UART_RestoreConfig(void) ;

#if ((UART_EP_MM == UART__EP_DMAAUTO) && (UART_EP_DMA_AUTO_OPT == 0u))
    void UART_LoadNextInEP(uint8 epNumber, uint8 mode) ;
#endif /* (UART_EP_MM == UART__EP_DMAAUTO) && (UART_EP_DMA_AUTO_OPT == 0u) */

#if defined(UART_ENABLE_IDSN_STRING)
    void UART_ReadDieID(uint8 descr[]) ;
#endif /* UART_ENABLE_IDSN_STRING */

#if defined(UART_ENABLE_HID_CLASS)
    uint8 UART_DispatchHIDClassRqst(void);
#endif /*  UART_ENABLE_HID_CLASS */
#if defined(UART_ENABLE_AUDIO_CLASS)
    uint8 UART_DispatchAUDIOClassRqst(void);
#endif /*  UART_ENABLE_HID_CLASS */
#if defined(UART_ENABLE_CDC_CLASS)
    uint8 UART_DispatchCDCClassRqst(void);
#endif /*  UART_ENABLE_CDC_CLASS */

CY_ISR_PROTO(UART_EP_0_ISR);
#if(UART_EP1_ISR_REMOVE == 0u)
    CY_ISR_PROTO(UART_EP_1_ISR);
#endif /*  UART_EP1_ISR_REMOVE */
#if(UART_EP2_ISR_REMOVE == 0u)
    CY_ISR_PROTO(UART_EP_2_ISR);
#endif /*  UART_EP2_ISR_REMOVE */
#if(UART_EP3_ISR_REMOVE == 0u)
    CY_ISR_PROTO(UART_EP_3_ISR);
#endif /*  UART_EP3_ISR_REMOVE */
#if(UART_EP4_ISR_REMOVE == 0u)
    CY_ISR_PROTO(UART_EP_4_ISR);
#endif /*  UART_EP4_ISR_REMOVE */
#if(UART_EP5_ISR_REMOVE == 0u)
    CY_ISR_PROTO(UART_EP_5_ISR);
#endif /*  UART_EP5_ISR_REMOVE */
#if(UART_EP6_ISR_REMOVE == 0u)
    CY_ISR_PROTO(UART_EP_6_ISR);
#endif /*  UART_EP6_ISR_REMOVE */
#if(UART_EP7_ISR_REMOVE == 0u)
    CY_ISR_PROTO(UART_EP_7_ISR);
#endif /*  UART_EP7_ISR_REMOVE */
#if(UART_EP8_ISR_REMOVE == 0u)
    CY_ISR_PROTO(UART_EP_8_ISR);
#endif /*  UART_EP8_ISR_REMOVE */
CY_ISR_PROTO(UART_BUS_RESET_ISR);
#if(UART_SOF_ISR_REMOVE == 0u)
    CY_ISR_PROTO(UART_SOF_ISR);
#endif /*  UART_SOF_ISR_REMOVE */
#if(UART_EP_MM != UART__EP_MANUAL)
    CY_ISR_PROTO(UART_ARB_ISR);
#endif /*  UART_EP_MM */
#if(UART_DP_ISR_REMOVE == 0u)
    CY_ISR_PROTO(UART_DP_ISR);
#endif /*  UART_DP_ISR_REMOVE */
#if ((UART_EP_MM == UART__EP_DMAAUTO) && (UART_EP_DMA_AUTO_OPT == 0u))
    CY_ISR_PROTO(UART_EP_DMA_DONE_ISR);
#endif /* (UART_EP_MM == UART__EP_DMAAUTO) && (UART_EP_DMA_AUTO_OPT == 0u) */

/***************************************
* Request Handlers
***************************************/

uint8 UART_HandleStandardRqst(void) ;
uint8 UART_DispatchClassRqst(void) ;
uint8 UART_HandleVendorRqst(void) ;


/***************************************
*    HID Internal references
***************************************/

#if defined(UART_ENABLE_HID_CLASS)
    void UART_FindReport(void) ;
    void UART_FindReportDescriptor(void) ;
    void UART_FindHidClassDecriptor(void) ;
#endif /* UART_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/

#if defined(UART_ENABLE_MIDI_STREAMING)
    void UART_MIDI_IN_EP_Service(void) ;
#endif /* UART_ENABLE_MIDI_STREAMING */


#endif /* CY_USBFS_UART_pvt_H */


/* [] END OF FILE */
