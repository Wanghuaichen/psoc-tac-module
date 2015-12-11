/*******************************************************************************
* File Name: UART.h
* Version 2.80
*
* Description:
*  Header File for the USBFS component. Contains prototypes and constant values.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_UART_H)
#define CY_USBFS_UART_H

#include "cytypes.h"
#include "cydevice_trm.h"
#include "cyfitter.h"
#include "CyLib.h"

/*  User supplied definitions. */
/* `#START USER_DEFINITIONS` Place your declaration here */

/* `#END` */


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component USBFS_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*  Memory Type Definitions
***************************************/

/* Renamed Type Definitions for backward compatibility.
*  Should not be used in new designs.
*/
#define UART_CODE CYCODE
#define UART_FAR CYFAR
#if defined(__C51__) || defined(__CX51__)
    #define UART_DATA data
    #define UART_XDATA xdata
#else
    #define UART_DATA
    #define UART_XDATA
#endif /*  __C51__ */
#define UART_NULL       NULL


/***************************************
* Enumerated Types and Parameters
***************************************/

#define UART__EP_MANUAL 0
#define UART__EP_DMAMANUAL 1
#define UART__EP_DMAAUTO 2

#define UART__MA_STATIC 0
#define UART__MA_DYNAMIC 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define UART_NUM_DEVICES   (1u)
#define UART_ENABLE_CDC_CLASS   
#define UART_ENABLE_DESCRIPTOR_STRINGS   
#define UART_ENABLE_MSOS_STRING   
#define UART_ENABLE_SN_STRING   
#define UART_ENABLE_IDSN_STRING   
#define UART_ENABLE_STRINGS   
#define UART_MAX_REPORTID_NUMBER   (0u)

#define UART_MON_VBUS                       (0u)
#define UART_EXTERN_VBUS                    (0u)
#define UART_EXTERN_VND                     (0u)
#define UART_EXTERN_CLS                     (0u)
#define UART_MAX_INTERFACES_NUMBER          (2u)
#define UART_EP0_ISR_REMOVE                 (0u)
#define UART_EP1_ISR_REMOVE                 (0u)
#define UART_EP2_ISR_REMOVE                 (0u)
#define UART_EP3_ISR_REMOVE                 (0u)
#define UART_EP4_ISR_REMOVE                 (1u)
#define UART_EP5_ISR_REMOVE                 (1u)
#define UART_EP6_ISR_REMOVE                 (1u)
#define UART_EP7_ISR_REMOVE                 (1u)
#define UART_EP8_ISR_REMOVE                 (1u)
#define UART_EP_MM                          (0u)
#define UART_EP_MA                          (0u)
#define UART_EP_DMA_AUTO_OPT                (0u)
#define UART_DMA1_REMOVE                    (1u)
#define UART_DMA2_REMOVE                    (1u)
#define UART_DMA3_REMOVE                    (1u)
#define UART_DMA4_REMOVE                    (1u)
#define UART_DMA5_REMOVE                    (1u)
#define UART_DMA6_REMOVE                    (1u)
#define UART_DMA7_REMOVE                    (1u)
#define UART_DMA8_REMOVE                    (1u)
#define UART_SOF_ISR_REMOVE                 (0u)
#define UART_ARB_ISR_REMOVE                 (0u)
#define UART_DP_ISR_REMOVE                  (0u)
#define UART_ENABLE_CDC_CLASS_API           (1u)
#define UART_ENABLE_MIDI_API                (1u)
#define UART_MIDI_EXT_MODE                  (0u)


/***************************************
*    Data Struct Definition
***************************************/

typedef struct
{
    uint8  attrib;
    uint8  apiEpState;
    uint8  hwEpState;
    uint8  epToggle;
    uint8  addr;
    uint8  epMode;
    uint16 buffOffset;
    uint16 bufferSize;
    uint8  interface;
} T_UART_EP_CTL_BLOCK;

typedef struct
{
    uint8  interface;
    uint8  altSetting;
    uint8  addr;
    uint8  attributes;
    uint16 bufferSize;
    uint8  bMisc;
} T_UART_EP_SETTINGS_BLOCK;

typedef struct
{
    uint8  status;
    uint16 length;
} T_UART_XFER_STATUS_BLOCK;

typedef struct
{
    uint16  count;
    volatile uint8 *pData;
    T_UART_XFER_STATUS_BLOCK *pStatusBlock;
} T_UART_TD;


typedef struct
{
    uint8   c;
    const void *p_list;
} T_UART_LUT;

/* Resume/Suspend API Support */
typedef struct
{
    uint8 enableState;
    uint8 mode;
} UART_BACKUP_STRUCT;


/* Renamed structure fields for backward compatibility.
*  Should not be used in new designs.
*/
#define wBuffOffset         buffOffset
#define wBufferSize         bufferSize
#define bStatus             status
#define wLength             length
#define wCount              count

/* Renamed global variable for backward compatibility.
*  Should not be used in new designs.
*/
#define CurrentTD           UART_currentTD


/***************************************
*       Function Prototypes
***************************************/

void   UART_Start(uint8 device, uint8 mode) ;
void   UART_Init(void) ;
void   UART_InitComponent(uint8 device, uint8 mode) ;
void   UART_Stop(void) ;
uint8  UART_CheckActivity(void) ;
uint8  UART_GetConfiguration(void) ;
uint8  UART_IsConfigurationChanged(void) ;
uint8  UART_GetInterfaceSetting(uint8 interfaceNumber)
                                                        ;
uint8  UART_GetEPState(uint8 epNumber) ;
uint16 UART_GetEPCount(uint8 epNumber) ;
void   UART_LoadInEP(uint8 epNumber, const uint8 pData[], uint16 length)
                                                                    ;
uint16 UART_ReadOutEP(uint8 epNumber, uint8 pData[], uint16 length)
                                                                    ;
void   UART_EnableOutEP(uint8 epNumber) ;
void   UART_DisableOutEP(uint8 epNumber) ;
void   UART_Force(uint8 bState) ;
uint8  UART_GetEPAckState(uint8 epNumber) ;
void   UART_SetPowerStatus(uint8 powerStatus) ;
uint8  UART_RWUEnabled(void) ;
void   UART_TerminateEP(uint8 ep) ;

void   UART_Suspend(void) ;
void   UART_Resume(void) ;

#if defined(UART_ENABLE_FWSN_STRING)
    void   UART_SerialNumString(uint8 snString[]) ;
#endif  /* UART_ENABLE_FWSN_STRING */
#if (UART_MON_VBUS == 1u)
    uint8  UART_VBusPresent(void) ;
#endif /*  UART_MON_VBUS */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

    void UART_CyBtldrCommStart(void) ;
    void UART_CyBtldrCommStop(void) ;
    void UART_CyBtldrCommReset(void) ;
    cystatus UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                        ;
    cystatus UART_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                        ;

    #define UART_BTLDR_OUT_EP      (0x01u)
    #define UART_BTLDR_IN_EP       (0x02u)

    #define UART_BTLDR_SIZEOF_WRITE_BUFFER  (64u)   /* EP 1 OUT */
    #define UART_BTLDR_SIZEOF_READ_BUFFER   (64u)   /* EP 2 IN  */
    #define UART_BTLDR_MAX_PACKET_SIZE      UART_BTLDR_SIZEOF_WRITE_BUFFER

    #define UART_BTLDR_WAIT_1_MS            (1u)    /* Time Out quantity equal 1mS */

    /* These defines active if used USBFS interface as an
    *  IO Component for bootloading. When Custom_Interface selected
    *  in Bootloder configuration as the IO Component, user must
    *  provide these functions.
    */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART)
        #define CyBtldrCommStart        UART_CyBtldrCommStart
        #define CyBtldrCommStop         UART_CyBtldrCommStop
        #define CyBtldrCommReset        UART_CyBtldrCommReset
        #define CyBtldrCommWrite        UART_CyBtldrCommWrite
        #define CyBtldrCommRead         UART_CyBtldrCommRead
    #endif  /*End   CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART */

#endif /*  CYDEV_BOOTLOADER_IO_COMP  */

#if(UART_EP_MM != UART__EP_MANUAL)
    void UART_InitEP_DMA(uint8 epNumber, const uint8* pData)
                                                    ;
    void UART_Stop_DMA(uint8 epNumber) ;
#endif /*  UART_EP_MM != UART__EP_MANUAL) */

#if defined(UART_ENABLE_MIDI_STREAMING) && (UART_ENABLE_MIDI_API != 0u)
    void UART_MIDI_EP_Init(void) ;

    #if (UART_MIDI_IN_BUFF_SIZE > 0)
        void UART_MIDI_IN_Service(void) ;
        uint8 UART_PutUsbMidiIn(uint8 ic, const uint8 midiMsg[], uint8 cable)
                                                                ;
    #endif /* UART_MIDI_IN_BUFF_SIZE > 0 */

    #if (UART_MIDI_OUT_BUFF_SIZE > 0)
        void UART_MIDI_OUT_EP_Service(void) ;
    #endif /* UART_MIDI_OUT_BUFF_SIZE > 0 */

#endif /*  UART_ENABLE_MIDI_API != 0u */

/* Renamed Functions for backward compatibility.
*  Should not be used in new designs.
*/

#define UART_bCheckActivity             UART_CheckActivity
#define UART_bGetConfiguration          UART_GetConfiguration
#define UART_bGetInterfaceSetting       UART_GetInterfaceSetting
#define UART_bGetEPState                UART_GetEPState
#define UART_wGetEPCount                UART_GetEPCount
#define UART_bGetEPAckState             UART_GetEPAckState
#define UART_bRWUEnabled                UART_RWUEnabled
#define UART_bVBusPresent               UART_VBusPresent

#define UART_bConfiguration             UART_configuration
#define UART_bInterfaceSetting          UART_interfaceSetting
#define UART_bDeviceAddress             UART_deviceAddress
#define UART_bDeviceStatus              UART_deviceStatus
#define UART_bDevice                    UART_device
#define UART_bTransferState             UART_transferState
#define UART_bLastPacketSize            UART_lastPacketSize

#define UART_LoadEP                     UART_LoadInEP
#define UART_LoadInISOCEP               UART_LoadInEP
#define UART_EnableOutISOCEP            UART_EnableOutEP

#define UART_SetVector                  CyIntSetVector
#define UART_SetPriority                CyIntSetPriority
#define UART_EnableInt                  CyIntEnable


/***************************************
*          API Constants
***************************************/

#define UART_EP0                        (0u)
#define UART_EP1                        (1u)
#define UART_EP2                        (2u)
#define UART_EP3                        (3u)
#define UART_EP4                        (4u)
#define UART_EP5                        (5u)
#define UART_EP6                        (6u)
#define UART_EP7                        (7u)
#define UART_EP8                        (8u)
#define UART_MAX_EP                     (9u)

#define UART_TRUE                       (1u)
#define UART_FALSE                      (0u)

#define UART_NO_EVENT_ALLOWED           (2u)
#define UART_EVENT_PENDING              (1u)
#define UART_NO_EVENT_PENDING           (0u)

#define UART_IN_BUFFER_FULL             UART_NO_EVENT_PENDING
#define UART_IN_BUFFER_EMPTY            UART_EVENT_PENDING
#define UART_OUT_BUFFER_FULL            UART_EVENT_PENDING
#define UART_OUT_BUFFER_EMPTY           UART_NO_EVENT_PENDING

#define UART_FORCE_J                    (0xA0u)
#define UART_FORCE_K                    (0x80u)
#define UART_FORCE_SE0                  (0xC0u)
#define UART_FORCE_NONE                 (0x00u)

#define UART_IDLE_TIMER_RUNNING         (0x02u)
#define UART_IDLE_TIMER_EXPIRED         (0x01u)
#define UART_IDLE_TIMER_INDEFINITE      (0x00u)

#define UART_DEVICE_STATUS_BUS_POWERED  (0x00u)
#define UART_DEVICE_STATUS_SELF_POWERED (0x01u)

#define UART_3V_OPERATION               (0x00u)
#define UART_5V_OPERATION               (0x01u)
#define UART_DWR_VDDD_OPERATION         (0x02u)

#define UART_MODE_DISABLE               (0x00u)
#define UART_MODE_NAK_IN_OUT            (0x01u)
#define UART_MODE_STATUS_OUT_ONLY       (0x02u)
#define UART_MODE_STALL_IN_OUT          (0x03u)
#define UART_MODE_RESERVED_0100         (0x04u)
#define UART_MODE_ISO_OUT               (0x05u)
#define UART_MODE_STATUS_IN_ONLY        (0x06u)
#define UART_MODE_ISO_IN                (0x07u)
#define UART_MODE_NAK_OUT               (0x08u)
#define UART_MODE_ACK_OUT               (0x09u)
#define UART_MODE_RESERVED_1010         (0x0Au)
#define UART_MODE_ACK_OUT_STATUS_IN     (0x0Bu)
#define UART_MODE_NAK_IN                (0x0Cu)
#define UART_MODE_ACK_IN                (0x0Du)
#define UART_MODE_RESERVED_1110         (0x0Eu)
#define UART_MODE_ACK_IN_STATUS_OUT     (0x0Fu)
#define UART_MODE_MASK                  (0x0Fu)
#define UART_MODE_STALL_DATA_EP         (0x80u)

#define UART_MODE_ACKD                  (0x10u)
#define UART_MODE_OUT_RCVD              (0x20u)
#define UART_MODE_IN_RCVD               (0x40u)
#define UART_MODE_SETUP_RCVD            (0x80u)

#define UART_RQST_TYPE_MASK             (0x60u)
#define UART_RQST_TYPE_STD              (0x00u)
#define UART_RQST_TYPE_CLS              (0x20u)
#define UART_RQST_TYPE_VND              (0x40u)
#define UART_RQST_DIR_MASK              (0x80u)
#define UART_RQST_DIR_D2H               (0x80u)
#define UART_RQST_DIR_H2D               (0x00u)
#define UART_RQST_RCPT_MASK             (0x03u)
#define UART_RQST_RCPT_DEV              (0x00u)
#define UART_RQST_RCPT_IFC              (0x01u)
#define UART_RQST_RCPT_EP               (0x02u)
#define UART_RQST_RCPT_OTHER            (0x03u)

/* USB Class Codes */
#define UART_CLASS_DEVICE               (0x00u)     /* Use class code info from Interface Descriptors */
#define UART_CLASS_AUDIO                (0x01u)     /* Audio device */
#define UART_CLASS_CDC                  (0x02u)     /* Communication device class */
#define UART_CLASS_HID                  (0x03u)     /* Human Interface Device */
#define UART_CLASS_PDC                  (0x05u)     /* Physical device class */
#define UART_CLASS_IMAGE                (0x06u)     /* Still Imaging device */
#define UART_CLASS_PRINTER              (0x07u)     /* Printer device  */
#define UART_CLASS_MSD                  (0x08u)     /* Mass Storage device  */
#define UART_CLASS_HUB                  (0x09u)     /* Full/Hi speed Hub */
#define UART_CLASS_CDC_DATA             (0x0Au)     /* CDC data device */
#define UART_CLASS_SMART_CARD           (0x0Bu)     /* Smart Card device */
#define UART_CLASS_CSD                  (0x0Du)     /* Content Security device */
#define UART_CLASS_VIDEO                (0x0Eu)     /* Video device */
#define UART_CLASS_PHD                  (0x0Fu)     /* Personal Healthcare device */
#define UART_CLASS_WIRELESSD            (0xDCu)     /* Wireless Controller */
#define UART_CLASS_MIS                  (0xE0u)     /* Miscellaneous */
#define UART_CLASS_APP                  (0xEFu)     /* Application Specific */
#define UART_CLASS_VENDOR               (0xFFu)     /* Vendor specific */


/* Standard Request Types (Table 9-4) */
#define UART_GET_STATUS                 (0x00u)
#define UART_CLEAR_FEATURE              (0x01u)
#define UART_SET_FEATURE                (0x03u)
#define UART_SET_ADDRESS                (0x05u)
#define UART_GET_DESCRIPTOR             (0x06u)
#define UART_SET_DESCRIPTOR             (0x07u)
#define UART_GET_CONFIGURATION          (0x08u)
#define UART_SET_CONFIGURATION          (0x09u)
#define UART_GET_INTERFACE              (0x0Au)
#define UART_SET_INTERFACE              (0x0Bu)
#define UART_SYNCH_FRAME                (0x0Cu)

/* Vendor Specific Request Types */
/* Request for Microsoft OS String Descriptor */
#define UART_GET_EXTENDED_CONFIG_DESCRIPTOR (0x01u)

/* Descriptor Types (Table 9-5) */
#define UART_DESCR_DEVICE                   (1u)
#define UART_DESCR_CONFIG                   (2u)
#define UART_DESCR_STRING                   (3u)
#define UART_DESCR_INTERFACE                (4u)
#define UART_DESCR_ENDPOINT                 (5u)
#define UART_DESCR_DEVICE_QUALIFIER         (6u)
#define UART_DESCR_OTHER_SPEED              (7u)
#define UART_DESCR_INTERFACE_POWER          (8u)

/* Device Descriptor Defines */
#define UART_DEVICE_DESCR_LENGTH            (18u)
#define UART_DEVICE_DESCR_SN_SHIFT          (16u)

/* Config Descriptor Shifts and Masks */
#define UART_CONFIG_DESCR_LENGTH                (0u)
#define UART_CONFIG_DESCR_TYPE                  (1u)
#define UART_CONFIG_DESCR_TOTAL_LENGTH_LOW      (2u)
#define UART_CONFIG_DESCR_TOTAL_LENGTH_HI       (3u)
#define UART_CONFIG_DESCR_NUM_INTERFACES        (4u)
#define UART_CONFIG_DESCR_CONFIG_VALUE          (5u)
#define UART_CONFIG_DESCR_CONFIGURATION         (6u)
#define UART_CONFIG_DESCR_ATTRIB                (7u)
#define UART_CONFIG_DESCR_ATTRIB_SELF_POWERED   (0x40u)
#define UART_CONFIG_DESCR_ATTRIB_RWU_EN         (0x20u)

/* Feature Selectors (Table 9-6) */
#define UART_DEVICE_REMOTE_WAKEUP           (0x01u)
#define UART_ENDPOINT_HALT                  (0x00u)
#define UART_TEST_MODE                      (0x02u)

/* USB Device Status (Figure 9-4) */
#define UART_DEVICE_STATUS_BUS_POWERED      (0x00u)
#define UART_DEVICE_STATUS_SELF_POWERED     (0x01u)
#define UART_DEVICE_STATUS_REMOTE_WAKEUP    (0x02u)

/* USB Endpoint Status (Figure 9-4) */
#define UART_ENDPOINT_STATUS_HALT           (0x01u)

/* USB Endpoint Directions */
#define UART_DIR_IN                         (0x80u)
#define UART_DIR_OUT                        (0x00u)
#define UART_DIR_UNUSED                     (0x7Fu)

/* USB Endpoint Attributes */
#define UART_EP_TYPE_CTRL                   (0x00u)
#define UART_EP_TYPE_ISOC                   (0x01u)
#define UART_EP_TYPE_BULK                   (0x02u)
#define UART_EP_TYPE_INT                    (0x03u)
#define UART_EP_TYPE_MASK                   (0x03u)

#define UART_EP_SYNC_TYPE_NO_SYNC           (0x00u)
#define UART_EP_SYNC_TYPE_ASYNC             (0x04u)
#define UART_EP_SYNC_TYPE_ADAPTIVE          (0x08u)
#define UART_EP_SYNC_TYPE_SYNCHRONOUS       (0x0Cu)
#define UART_EP_SYNC_TYPE_MASK              (0x0Cu)

#define UART_EP_USAGE_TYPE_DATA             (0x00u)
#define UART_EP_USAGE_TYPE_FEEDBACK         (0x10u)
#define UART_EP_USAGE_TYPE_IMPLICIT         (0x20u)
#define UART_EP_USAGE_TYPE_RESERVED         (0x30u)
#define UART_EP_USAGE_TYPE_MASK             (0x30u)

/* point Status defines */
#define UART_EP_STATUS_LENGTH               (0x02u)

/* point Device defines */
#define UART_DEVICE_STATUS_LENGTH           (0x02u)

#define UART_STATUS_LENGTH_MAX \
                 ( (UART_EP_STATUS_LENGTH > UART_DEVICE_STATUS_LENGTH) ? \
                    UART_EP_STATUS_LENGTH : UART_DEVICE_STATUS_LENGTH )
/* Transfer Completion Notification */
#define UART_XFER_IDLE                      (0x00u)
#define UART_XFER_STATUS_ACK                (0x01u)
#define UART_XFER_PREMATURE                 (0x02u)
#define UART_XFER_ERROR                     (0x03u)

/* Driver State defines */
#define UART_TRANS_STATE_IDLE               (0x00u)
#define UART_TRANS_STATE_CONTROL_READ       (0x02u)
#define UART_TRANS_STATE_CONTROL_WRITE      (0x04u)
#define UART_TRANS_STATE_NO_DATA_CONTROL    (0x06u)

/* String Descriptor defines */
#define UART_STRING_MSOS                    (0xEEu)
#define UART_MSOS_DESCRIPTOR_LENGTH         (18u)
#define UART_MSOS_CONF_DESCR_LENGTH         (40u)

#if(UART_EP_MM == UART__EP_DMAMANUAL)
    /* DMA manual mode defines */
    #define UART_DMA_BYTES_PER_BURST        (0u)
    #define UART_DMA_REQUEST_PER_BURST      (0u)
#endif /*  UART_EP_MM == UART__EP_DMAMANUAL */
#if(UART_EP_MM == UART__EP_DMAAUTO)
    /* DMA automatic mode defines */
    #define UART_DMA_BYTES_PER_BURST        (32u)
    #define UART_DMA_BYTES_REPEAT           (2u)
    /* BUF_SIZE-BYTES_PER_BURST examples: 55-32 bytes  44-16 bytes 33-8 bytes 22-4 bytes 11-2 bytes */
    #define UART_DMA_BUF_SIZE               (0x55u)
    #define UART_DMA_REQUEST_PER_BURST      (1u)

    #if(UART_DMA1_REMOVE == 0u)
        #define UART_ep1_TD_TERMOUT_EN      UART_ep1__TD_TERMOUT_EN
    #else
        #define UART_ep1_TD_TERMOUT_EN      (0u)
    #endif /* UART_DMA1_REMOVE == 0u */
    #if(UART_DMA2_REMOVE == 0u)
        #define UART_ep2_TD_TERMOUT_EN      UART_ep2__TD_TERMOUT_EN
    #else
        #define UART_ep2_TD_TERMOUT_EN      (0u)
    #endif /* UART_DMA2_REMOVE == 0u */
    #if(UART_DMA3_REMOVE == 0u)
        #define UART_ep3_TD_TERMOUT_EN      UART_ep3__TD_TERMOUT_EN
    #else
        #define UART_ep3_TD_TERMOUT_EN      (0u)
    #endif /* UART_DMA3_REMOVE == 0u */
    #if(UART_DMA4_REMOVE == 0u)
        #define UART_ep4_TD_TERMOUT_EN      UART_ep4__TD_TERMOUT_EN
    #else
        #define UART_ep4_TD_TERMOUT_EN      (0u)
    #endif /* UART_DMA4_REMOVE == 0u */
    #if(UART_DMA5_REMOVE == 0u)
        #define UART_ep5_TD_TERMOUT_EN      UART_ep5__TD_TERMOUT_EN
    #else
        #define UART_ep5_TD_TERMOUT_EN      (0u)
    #endif /* UART_DMA5_REMOVE == 0u */
    #if(UART_DMA6_REMOVE == 0u)
        #define UART_ep6_TD_TERMOUT_EN      UART_ep6__TD_TERMOUT_EN
    #else
        #define UART_ep6_TD_TERMOUT_EN      (0u)
    #endif /* UART_DMA6_REMOVE == 0u */
    #if(UART_DMA7_REMOVE == 0u)
        #define UART_ep7_TD_TERMOUT_EN      UART_ep7__TD_TERMOUT_EN
    #else
        #define UART_ep7_TD_TERMOUT_EN      (0u)
    #endif /* UART_DMA7_REMOVE == 0u */
    #if(UART_DMA8_REMOVE == 0u)
        #define UART_ep8_TD_TERMOUT_EN      UART_ep8__TD_TERMOUT_EN
    #else
        #define UART_ep8_TD_TERMOUT_EN      (0u)
    #endif /* UART_DMA8_REMOVE == 0u */

    #define     UART_EP17_SR_MASK           (0x7fu)
    #define     UART_EP8_SR_MASK            (0x03u)

#endif /*  UART_EP_MM == UART__EP_DMAAUTO */

/* DIE ID string descriptor defines */
#if defined(UART_ENABLE_IDSN_STRING)
    #define UART_IDSN_DESCR_LENGTH          (0x22u)
#endif /* UART_ENABLE_IDSN_STRING */


/***************************************
* External data references
***************************************/

extern uint8 UART_initVar;
extern volatile uint8 UART_device;
extern volatile uint8 UART_transferState;
extern volatile uint8 UART_configuration;
extern volatile uint8 UART_configurationChanged;
extern volatile uint8 UART_deviceStatus;

/* HID Variables */
#if defined(UART_ENABLE_HID_CLASS)
    extern volatile uint8 UART_hidProtocol[UART_MAX_INTERFACES_NUMBER];
    extern volatile uint8 UART_hidIdleRate[UART_MAX_INTERFACES_NUMBER];
    extern volatile uint8 UART_hidIdleTimer[UART_MAX_INTERFACES_NUMBER];
#endif /* UART_ENABLE_HID_CLASS */


/***************************************
*              Registers
***************************************/

#define UART_ARB_CFG_PTR        (  (reg8 *) UART_USB__ARB_CFG)
#define UART_ARB_CFG_REG        (* (reg8 *) UART_USB__ARB_CFG)

#define UART_ARB_EP1_CFG_PTR    (  (reg8 *) UART_USB__ARB_EP1_CFG)
#define UART_ARB_EP1_CFG_REG    (* (reg8 *) UART_USB__ARB_EP1_CFG)
#define UART_ARB_EP1_CFG_IND    UART_USB__ARB_EP1_CFG
#define UART_ARB_EP1_INT_EN_PTR (  (reg8 *) UART_USB__ARB_EP1_INT_EN)
#define UART_ARB_EP1_INT_EN_REG (* (reg8 *) UART_USB__ARB_EP1_INT_EN)
#define UART_ARB_EP1_INT_EN_IND UART_USB__ARB_EP1_INT_EN
#define UART_ARB_EP1_SR_PTR     (  (reg8 *) UART_USB__ARB_EP1_SR)
#define UART_ARB_EP1_SR_REG     (* (reg8 *) UART_USB__ARB_EP1_SR)
#define UART_ARB_EP1_SR_IND     UART_USB__ARB_EP1_SR

#define UART_ARB_EP2_CFG_PTR    (  (reg8 *) UART_USB__ARB_EP2_CFG)
#define UART_ARB_EP2_CFG_REG    (* (reg8 *) UART_USB__ARB_EP2_CFG)
#define UART_ARB_EP2_INT_EN_PTR (  (reg8 *) UART_USB__ARB_EP2_INT_EN)
#define UART_ARB_EP2_INT_EN_REG (* (reg8 *) UART_USB__ARB_EP2_INT_EN)
#define UART_ARB_EP2_SR_PTR     (  (reg8 *) UART_USB__ARB_EP2_SR)
#define UART_ARB_EP2_SR_REG     (* (reg8 *) UART_USB__ARB_EP2_SR)

#define UART_ARB_EP3_CFG_PTR    (  (reg8 *) UART_USB__ARB_EP3_CFG)
#define UART_ARB_EP3_CFG_REG    (* (reg8 *) UART_USB__ARB_EP3_CFG)
#define UART_ARB_EP3_INT_EN_PTR (  (reg8 *) UART_USB__ARB_EP3_INT_EN)
#define UART_ARB_EP3_INT_EN_REG (* (reg8 *) UART_USB__ARB_EP3_INT_EN)
#define UART_ARB_EP3_SR_PTR     (  (reg8 *) UART_USB__ARB_EP3_SR)
#define UART_ARB_EP3_SR_REG     (* (reg8 *) UART_USB__ARB_EP3_SR)

#define UART_ARB_EP4_CFG_PTR    (  (reg8 *) UART_USB__ARB_EP4_CFG)
#define UART_ARB_EP4_CFG_REG    (* (reg8 *) UART_USB__ARB_EP4_CFG)
#define UART_ARB_EP4_INT_EN_PTR (  (reg8 *) UART_USB__ARB_EP4_INT_EN)
#define UART_ARB_EP4_INT_EN_REG (* (reg8 *) UART_USB__ARB_EP4_INT_EN)
#define UART_ARB_EP4_SR_PTR     (  (reg8 *) UART_USB__ARB_EP4_SR)
#define UART_ARB_EP4_SR_REG     (* (reg8 *) UART_USB__ARB_EP4_SR)

#define UART_ARB_EP5_CFG_PTR    (  (reg8 *) UART_USB__ARB_EP5_CFG)
#define UART_ARB_EP5_CFG_REG    (* (reg8 *) UART_USB__ARB_EP5_CFG)
#define UART_ARB_EP5_INT_EN_PTR (  (reg8 *) UART_USB__ARB_EP5_INT_EN)
#define UART_ARB_EP5_INT_EN_REG (* (reg8 *) UART_USB__ARB_EP5_INT_EN)
#define UART_ARB_EP5_SR_PTR     (  (reg8 *) UART_USB__ARB_EP5_SR)
#define UART_ARB_EP5_SR_REG     (* (reg8 *) UART_USB__ARB_EP5_SR)

#define UART_ARB_EP6_CFG_PTR    (  (reg8 *) UART_USB__ARB_EP6_CFG)
#define UART_ARB_EP6_CFG_REG    (* (reg8 *) UART_USB__ARB_EP6_CFG)
#define UART_ARB_EP6_INT_EN_PTR (  (reg8 *) UART_USB__ARB_EP6_INT_EN)
#define UART_ARB_EP6_INT_EN_REG (* (reg8 *) UART_USB__ARB_EP6_INT_EN)
#define UART_ARB_EP6_SR_PTR     (  (reg8 *) UART_USB__ARB_EP6_SR)
#define UART_ARB_EP6_SR_REG     (* (reg8 *) UART_USB__ARB_EP6_SR)

#define UART_ARB_EP7_CFG_PTR    (  (reg8 *) UART_USB__ARB_EP7_CFG)
#define UART_ARB_EP7_CFG_REG    (* (reg8 *) UART_USB__ARB_EP7_CFG)
#define UART_ARB_EP7_INT_EN_PTR (  (reg8 *) UART_USB__ARB_EP7_INT_EN)
#define UART_ARB_EP7_INT_EN_REG (* (reg8 *) UART_USB__ARB_EP7_INT_EN)
#define UART_ARB_EP7_SR_PTR     (  (reg8 *) UART_USB__ARB_EP7_SR)
#define UART_ARB_EP7_SR_REG     (* (reg8 *) UART_USB__ARB_EP7_SR)

#define UART_ARB_EP8_CFG_PTR    (  (reg8 *) UART_USB__ARB_EP8_CFG)
#define UART_ARB_EP8_CFG_REG    (* (reg8 *) UART_USB__ARB_EP8_CFG)
#define UART_ARB_EP8_INT_EN_PTR (  (reg8 *) UART_USB__ARB_EP8_INT_EN)
#define UART_ARB_EP8_INT_EN_REG (* (reg8 *) UART_USB__ARB_EP8_INT_EN)
#define UART_ARB_EP8_SR_PTR     (  (reg8 *) UART_USB__ARB_EP8_SR)
#define UART_ARB_EP8_SR_REG     (* (reg8 *) UART_USB__ARB_EP8_SR)

#define UART_ARB_INT_EN_PTR     (  (reg8 *) UART_USB__ARB_INT_EN)
#define UART_ARB_INT_EN_REG     (* (reg8 *) UART_USB__ARB_INT_EN)
#define UART_ARB_INT_SR_PTR     (  (reg8 *) UART_USB__ARB_INT_SR)
#define UART_ARB_INT_SR_REG     (* (reg8 *) UART_USB__ARB_INT_SR)

#define UART_ARB_RW1_DR_PTR     ((reg8 *) UART_USB__ARB_RW1_DR)
#define UART_ARB_RW1_DR_IND     UART_USB__ARB_RW1_DR
#define UART_ARB_RW1_RA_PTR     ((reg8 *) UART_USB__ARB_RW1_RA)
#define UART_ARB_RW1_RA_IND     UART_USB__ARB_RW1_RA
#define UART_ARB_RW1_RA_MSB_PTR ((reg8 *) UART_USB__ARB_RW1_RA_MSB)
#define UART_ARB_RW1_RA_MSB_IND UART_USB__ARB_RW1_RA_MSB
#define UART_ARB_RW1_WA_PTR     ((reg8 *) UART_USB__ARB_RW1_WA)
#define UART_ARB_RW1_WA_IND     UART_USB__ARB_RW1_WA
#define UART_ARB_RW1_WA_MSB_PTR ((reg8 *) UART_USB__ARB_RW1_WA_MSB)
#define UART_ARB_RW1_WA_MSB_IND UART_USB__ARB_RW1_WA_MSB

#define UART_ARB_RW2_DR_PTR     ((reg8 *) UART_USB__ARB_RW2_DR)
#define UART_ARB_RW2_RA_PTR     ((reg8 *) UART_USB__ARB_RW2_RA)
#define UART_ARB_RW2_RA_MSB_PTR ((reg8 *) UART_USB__ARB_RW2_RA_MSB)
#define UART_ARB_RW2_WA_PTR     ((reg8 *) UART_USB__ARB_RW2_WA)
#define UART_ARB_RW2_WA_MSB_PTR ((reg8 *) UART_USB__ARB_RW2_WA_MSB)

#define UART_ARB_RW3_DR_PTR     ((reg8 *) UART_USB__ARB_RW3_DR)
#define UART_ARB_RW3_RA_PTR     ((reg8 *) UART_USB__ARB_RW3_RA)
#define UART_ARB_RW3_RA_MSB_PTR ((reg8 *) UART_USB__ARB_RW3_RA_MSB)
#define UART_ARB_RW3_WA_PTR     ((reg8 *) UART_USB__ARB_RW3_WA)
#define UART_ARB_RW3_WA_MSB_PTR ((reg8 *) UART_USB__ARB_RW3_WA_MSB)

#define UART_ARB_RW4_DR_PTR     ((reg8 *) UART_USB__ARB_RW4_DR)
#define UART_ARB_RW4_RA_PTR     ((reg8 *) UART_USB__ARB_RW4_RA)
#define UART_ARB_RW4_RA_MSB_PTR ((reg8 *) UART_USB__ARB_RW4_RA_MSB)
#define UART_ARB_RW4_WA_PTR     ((reg8 *) UART_USB__ARB_RW4_WA)
#define UART_ARB_RW4_WA_MSB_PTR ((reg8 *) UART_USB__ARB_RW4_WA_MSB)

#define UART_ARB_RW5_DR_PTR     ((reg8 *) UART_USB__ARB_RW5_DR)
#define UART_ARB_RW5_RA_PTR     ((reg8 *) UART_USB__ARB_RW5_RA)
#define UART_ARB_RW5_RA_MSB_PTR ((reg8 *) UART_USB__ARB_RW5_RA_MSB)
#define UART_ARB_RW5_WA_PTR     ((reg8 *) UART_USB__ARB_RW5_WA)
#define UART_ARB_RW5_WA_MSB_PTR ((reg8 *) UART_USB__ARB_RW5_WA_MSB)

#define UART_ARB_RW6_DR_PTR     ((reg8 *) UART_USB__ARB_RW6_DR)
#define UART_ARB_RW6_RA_PTR     ((reg8 *) UART_USB__ARB_RW6_RA)
#define UART_ARB_RW6_RA_MSB_PTR ((reg8 *) UART_USB__ARB_RW6_RA_MSB)
#define UART_ARB_RW6_WA_PTR     ((reg8 *) UART_USB__ARB_RW6_WA)
#define UART_ARB_RW6_WA_MSB_PTR ((reg8 *) UART_USB__ARB_RW6_WA_MSB)

#define UART_ARB_RW7_DR_PTR     ((reg8 *) UART_USB__ARB_RW7_DR)
#define UART_ARB_RW7_RA_PTR     ((reg8 *) UART_USB__ARB_RW7_RA)
#define UART_ARB_RW7_RA_MSB_PTR ((reg8 *) UART_USB__ARB_RW7_RA_MSB)
#define UART_ARB_RW7_WA_PTR     ((reg8 *) UART_USB__ARB_RW7_WA)
#define UART_ARB_RW7_WA_MSB_PTR ((reg8 *) UART_USB__ARB_RW7_WA_MSB)

#define UART_ARB_RW8_DR_PTR     ((reg8 *) UART_USB__ARB_RW8_DR)
#define UART_ARB_RW8_RA_PTR     ((reg8 *) UART_USB__ARB_RW8_RA)
#define UART_ARB_RW8_RA_MSB_PTR ((reg8 *) UART_USB__ARB_RW8_RA_MSB)
#define UART_ARB_RW8_WA_PTR     ((reg8 *) UART_USB__ARB_RW8_WA)
#define UART_ARB_RW8_WA_MSB_PTR ((reg8 *) UART_USB__ARB_RW8_WA_MSB)

#define UART_BUF_SIZE_PTR       (  (reg8 *) UART_USB__BUF_SIZE)
#define UART_BUF_SIZE_REG       (* (reg8 *) UART_USB__BUF_SIZE)
#define UART_BUS_RST_CNT_PTR    (  (reg8 *) UART_USB__BUS_RST_CNT)
#define UART_BUS_RST_CNT_REG    (* (reg8 *) UART_USB__BUS_RST_CNT)
#define UART_CWA_PTR            (  (reg8 *) UART_USB__CWA)
#define UART_CWA_REG            (* (reg8 *) UART_USB__CWA)
#define UART_CWA_MSB_PTR        (  (reg8 *) UART_USB__CWA_MSB)
#define UART_CWA_MSB_REG        (* (reg8 *) UART_USB__CWA_MSB)
#define UART_CR0_PTR            (  (reg8 *) UART_USB__CR0)
#define UART_CR0_REG            (* (reg8 *) UART_USB__CR0)
#define UART_CR1_PTR            (  (reg8 *) UART_USB__CR1)
#define UART_CR1_REG            (* (reg8 *) UART_USB__CR1)

#define UART_DMA_THRES_PTR      (  (reg8 *) UART_USB__DMA_THRES)
#define UART_DMA_THRES_REG      (* (reg8 *) UART_USB__DMA_THRES)
#define UART_DMA_THRES_MSB_PTR  (  (reg8 *) UART_USB__DMA_THRES_MSB)
#define UART_DMA_THRES_MSB_REG  (* (reg8 *) UART_USB__DMA_THRES_MSB)

#define UART_EP_ACTIVE_PTR      (  (reg8 *) UART_USB__EP_ACTIVE)
#define UART_EP_ACTIVE_REG      (* (reg8 *) UART_USB__EP_ACTIVE)
#define UART_EP_TYPE_PTR        (  (reg8 *) UART_USB__EP_TYPE)
#define UART_EP_TYPE_REG        (* (reg8 *) UART_USB__EP_TYPE)

#define UART_EP0_CNT_PTR        (  (reg8 *) UART_USB__EP0_CNT)
#define UART_EP0_CNT_REG        (* (reg8 *) UART_USB__EP0_CNT)
#define UART_EP0_CR_PTR         (  (reg8 *) UART_USB__EP0_CR)
#define UART_EP0_CR_REG         (* (reg8 *) UART_USB__EP0_CR)
#define UART_EP0_DR0_PTR        (  (reg8 *) UART_USB__EP0_DR0)
#define UART_EP0_DR0_REG        (* (reg8 *) UART_USB__EP0_DR0)
#define UART_EP0_DR0_IND        UART_USB__EP0_DR0
#define UART_EP0_DR1_PTR        (  (reg8 *) UART_USB__EP0_DR1)
#define UART_EP0_DR1_REG        (* (reg8 *) UART_USB__EP0_DR1)
#define UART_EP0_DR2_PTR        (  (reg8 *) UART_USB__EP0_DR2)
#define UART_EP0_DR2_REG        (* (reg8 *) UART_USB__EP0_DR2)
#define UART_EP0_DR3_PTR        (  (reg8 *) UART_USB__EP0_DR3)
#define UART_EP0_DR3_REG        (* (reg8 *) UART_USB__EP0_DR3)
#define UART_EP0_DR4_PTR        (  (reg8 *) UART_USB__EP0_DR4)
#define UART_EP0_DR4_REG        (* (reg8 *) UART_USB__EP0_DR4)
#define UART_EP0_DR5_PTR        (  (reg8 *) UART_USB__EP0_DR5)
#define UART_EP0_DR5_REG        (* (reg8 *) UART_USB__EP0_DR5)
#define UART_EP0_DR6_PTR        (  (reg8 *) UART_USB__EP0_DR6)
#define UART_EP0_DR6_REG        (* (reg8 *) UART_USB__EP0_DR6)
#define UART_EP0_DR7_PTR        (  (reg8 *) UART_USB__EP0_DR7)
#define UART_EP0_DR7_REG        (* (reg8 *) UART_USB__EP0_DR7)

#define UART_OSCLK_DR0_PTR      (  (reg8 *) UART_USB__OSCLK_DR0)
#define UART_OSCLK_DR0_REG      (* (reg8 *) UART_USB__OSCLK_DR0)
#define UART_OSCLK_DR1_PTR      (  (reg8 *) UART_USB__OSCLK_DR1)
#define UART_OSCLK_DR1_REG      (* (reg8 *) UART_USB__OSCLK_DR1)

#define UART_PM_ACT_CFG_PTR     (  (reg8 *) UART_USB__PM_ACT_CFG)
#define UART_PM_ACT_CFG_REG     (* (reg8 *) UART_USB__PM_ACT_CFG)
#define UART_PM_STBY_CFG_PTR    (  (reg8 *) UART_USB__PM_STBY_CFG)
#define UART_PM_STBY_CFG_REG    (* (reg8 *) UART_USB__PM_STBY_CFG)

#define UART_SIE_EP_INT_EN_PTR  (  (reg8 *) UART_USB__SIE_EP_INT_EN)
#define UART_SIE_EP_INT_EN_REG  (* (reg8 *) UART_USB__SIE_EP_INT_EN)
#define UART_SIE_EP_INT_SR_PTR  (  (reg8 *) UART_USB__SIE_EP_INT_SR)
#define UART_SIE_EP_INT_SR_REG  (* (reg8 *) UART_USB__SIE_EP_INT_SR)

#define UART_SIE_EP1_CNT0_PTR   (  (reg8 *) UART_USB__SIE_EP1_CNT0)
#define UART_SIE_EP1_CNT0_REG   (* (reg8 *) UART_USB__SIE_EP1_CNT0)
#define UART_SIE_EP1_CNT0_IND   UART_USB__SIE_EP1_CNT0
#define UART_SIE_EP1_CNT1_PTR   (  (reg8 *) UART_USB__SIE_EP1_CNT1)
#define UART_SIE_EP1_CNT1_REG   (* (reg8 *) UART_USB__SIE_EP1_CNT1)
#define UART_SIE_EP1_CNT1_IND   UART_USB__SIE_EP1_CNT1
#define UART_SIE_EP1_CR0_PTR    (  (reg8 *) UART_USB__SIE_EP1_CR0)
#define UART_SIE_EP1_CR0_REG    (* (reg8 *) UART_USB__SIE_EP1_CR0)
#define UART_SIE_EP1_CR0_IND    UART_USB__SIE_EP1_CR0

#define UART_SIE_EP2_CNT0_PTR   (  (reg8 *) UART_USB__SIE_EP2_CNT0)
#define UART_SIE_EP2_CNT0_REG   (* (reg8 *) UART_USB__SIE_EP2_CNT0)
#define UART_SIE_EP2_CNT1_PTR   (  (reg8 *) UART_USB__SIE_EP2_CNT1)
#define UART_SIE_EP2_CNT1_REG   (* (reg8 *) UART_USB__SIE_EP2_CNT1)
#define UART_SIE_EP2_CR0_PTR    (  (reg8 *) UART_USB__SIE_EP2_CR0)
#define UART_SIE_EP2_CR0_REG    (* (reg8 *) UART_USB__SIE_EP2_CR0)

#define UART_SIE_EP3_CNT0_PTR   (  (reg8 *) UART_USB__SIE_EP3_CNT0)
#define UART_SIE_EP3_CNT0_REG   (* (reg8 *) UART_USB__SIE_EP3_CNT0)
#define UART_SIE_EP3_CNT1_PTR   (  (reg8 *) UART_USB__SIE_EP3_CNT1)
#define UART_SIE_EP3_CNT1_REG   (* (reg8 *) UART_USB__SIE_EP3_CNT1)
#define UART_SIE_EP3_CR0_PTR    (  (reg8 *) UART_USB__SIE_EP3_CR0)
#define UART_SIE_EP3_CR0_REG    (* (reg8 *) UART_USB__SIE_EP3_CR0)

#define UART_SIE_EP4_CNT0_PTR   (  (reg8 *) UART_USB__SIE_EP4_CNT0)
#define UART_SIE_EP4_CNT0_REG   (* (reg8 *) UART_USB__SIE_EP4_CNT0)
#define UART_SIE_EP4_CNT1_PTR   (  (reg8 *) UART_USB__SIE_EP4_CNT1)
#define UART_SIE_EP4_CNT1_REG   (* (reg8 *) UART_USB__SIE_EP4_CNT1)
#define UART_SIE_EP4_CR0_PTR    (  (reg8 *) UART_USB__SIE_EP4_CR0)
#define UART_SIE_EP4_CR0_REG    (* (reg8 *) UART_USB__SIE_EP4_CR0)

#define UART_SIE_EP5_CNT0_PTR   (  (reg8 *) UART_USB__SIE_EP5_CNT0)
#define UART_SIE_EP5_CNT0_REG   (* (reg8 *) UART_USB__SIE_EP5_CNT0)
#define UART_SIE_EP5_CNT1_PTR   (  (reg8 *) UART_USB__SIE_EP5_CNT1)
#define UART_SIE_EP5_CNT1_REG   (* (reg8 *) UART_USB__SIE_EP5_CNT1)
#define UART_SIE_EP5_CR0_PTR    (  (reg8 *) UART_USB__SIE_EP5_CR0)
#define UART_SIE_EP5_CR0_REG    (* (reg8 *) UART_USB__SIE_EP5_CR0)

#define UART_SIE_EP6_CNT0_PTR   (  (reg8 *) UART_USB__SIE_EP6_CNT0)
#define UART_SIE_EP6_CNT0_REG   (* (reg8 *) UART_USB__SIE_EP6_CNT0)
#define UART_SIE_EP6_CNT1_PTR   (  (reg8 *) UART_USB__SIE_EP6_CNT1)
#define UART_SIE_EP6_CNT1_REG   (* (reg8 *) UART_USB__SIE_EP6_CNT1)
#define UART_SIE_EP6_CR0_PTR    (  (reg8 *) UART_USB__SIE_EP6_CR0)
#define UART_SIE_EP6_CR0_REG    (* (reg8 *) UART_USB__SIE_EP6_CR0)

#define UART_SIE_EP7_CNT0_PTR   (  (reg8 *) UART_USB__SIE_EP7_CNT0)
#define UART_SIE_EP7_CNT0_REG   (* (reg8 *) UART_USB__SIE_EP7_CNT0)
#define UART_SIE_EP7_CNT1_PTR   (  (reg8 *) UART_USB__SIE_EP7_CNT1)
#define UART_SIE_EP7_CNT1_REG   (* (reg8 *) UART_USB__SIE_EP7_CNT1)
#define UART_SIE_EP7_CR0_PTR    (  (reg8 *) UART_USB__SIE_EP7_CR0)
#define UART_SIE_EP7_CR0_REG    (* (reg8 *) UART_USB__SIE_EP7_CR0)

#define UART_SIE_EP8_CNT0_PTR   (  (reg8 *) UART_USB__SIE_EP8_CNT0)
#define UART_SIE_EP8_CNT0_REG   (* (reg8 *) UART_USB__SIE_EP8_CNT0)
#define UART_SIE_EP8_CNT1_PTR   (  (reg8 *) UART_USB__SIE_EP8_CNT1)
#define UART_SIE_EP8_CNT1_REG   (* (reg8 *) UART_USB__SIE_EP8_CNT1)
#define UART_SIE_EP8_CR0_PTR    (  (reg8 *) UART_USB__SIE_EP8_CR0)
#define UART_SIE_EP8_CR0_REG    (* (reg8 *) UART_USB__SIE_EP8_CR0)

#define UART_SOF0_PTR           (  (reg8 *) UART_USB__SOF0)
#define UART_SOF0_REG           (* (reg8 *) UART_USB__SOF0)
#define UART_SOF1_PTR           (  (reg8 *) UART_USB__SOF1)
#define UART_SOF1_REG           (* (reg8 *) UART_USB__SOF1)

#define UART_USB_CLK_EN_PTR     (  (reg8 *) UART_USB__USB_CLK_EN)
#define UART_USB_CLK_EN_REG     (* (reg8 *) UART_USB__USB_CLK_EN)

#define UART_USBIO_CR0_PTR      (  (reg8 *) UART_USB__USBIO_CR0)
#define UART_USBIO_CR0_REG      (* (reg8 *) UART_USB__USBIO_CR0)
#define UART_USBIO_CR1_PTR      (  (reg8 *) UART_USB__USBIO_CR1)
#define UART_USBIO_CR1_REG      (* (reg8 *) UART_USB__USBIO_CR1)
#if(!CY_PSOC5LP)
    #define UART_USBIO_CR2_PTR      (  (reg8 *) UART_USB__USBIO_CR2)
    #define UART_USBIO_CR2_REG      (* (reg8 *) UART_USB__USBIO_CR2)
#endif /*  CY_PSOC5LP */

#define UART_DIE_ID             CYDEV_FLSHID_CUST_TABLES_BASE

#define UART_PM_USB_CR0_PTR     (  (reg8 *) CYREG_PM_USB_CR0)
#define UART_PM_USB_CR0_REG     (* (reg8 *) CYREG_PM_USB_CR0)
#define UART_DYN_RECONFIG_PTR   (  (reg8 *) UART_USB__DYN_RECONFIG)
#define UART_DYN_RECONFIG_REG   (* (reg8 *) UART_USB__DYN_RECONFIG)

#define UART_DM_INP_DIS_PTR     (  (reg8 *) UART_Dm__INP_DIS)
#define UART_DM_INP_DIS_REG     (* (reg8 *) UART_Dm__INP_DIS)
#define UART_DP_INP_DIS_PTR     (  (reg8 *) UART_Dp__INP_DIS)
#define UART_DP_INP_DIS_REG     (* (reg8 *) UART_Dp__INP_DIS)
#define UART_DP_INTSTAT_PTR     (  (reg8 *) UART_Dp__INTSTAT)
#define UART_DP_INTSTAT_REG     (* (reg8 *) UART_Dp__INTSTAT)

#if (UART_MON_VBUS == 1u)
    #if (UART_EXTERN_VBUS == 0u)
        #define UART_VBUS_DR_PTR        (  (reg8 *) UART_VBUS__DR)
        #define UART_VBUS_DR_REG        (* (reg8 *) UART_VBUS__DR)
        #define UART_VBUS_PS_PTR        (  (reg8 *) UART_VBUS__PS)
        #define UART_VBUS_PS_REG        (* (reg8 *) UART_VBUS__PS)
        #define UART_VBUS_MASK          UART_VBUS__MASK
    #else
        #define UART_VBUS_PS_PTR        (  (reg8 *) UART_Vbus_ps_sts_sts_reg__STATUS_REG )
        #define UART_VBUS_MASK          (0x01u)
    #endif /*  UART_EXTERN_VBUS == 0u */
#endif /*  UART_MON_VBUS */

/* Renamed Registers for backward compatibility.
*  Should not be used in new designs.
*/
#define UART_ARB_CFG        UART_ARB_CFG_PTR

#define UART_ARB_EP1_CFG    UART_ARB_EP1_CFG_PTR
#define UART_ARB_EP1_INT_EN UART_ARB_EP1_INT_EN_PTR
#define UART_ARB_EP1_SR     UART_ARB_EP1_SR_PTR

#define UART_ARB_EP2_CFG    UART_ARB_EP2_CFG_PTR
#define UART_ARB_EP2_INT_EN UART_ARB_EP2_INT_EN_PTR
#define UART_ARB_EP2_SR     UART_ARB_EP2_SR_PTR

#define UART_ARB_EP3_CFG    UART_ARB_EP3_CFG_PTR
#define UART_ARB_EP3_INT_EN UART_ARB_EP3_INT_EN_PTR
#define UART_ARB_EP3_SR     UART_ARB_EP3_SR_PTR

#define UART_ARB_EP4_CFG    UART_ARB_EP4_CFG_PTR
#define UART_ARB_EP4_INT_EN UART_ARB_EP4_INT_EN_PTR
#define UART_ARB_EP4_SR     UART_ARB_EP4_SR_PTR

#define UART_ARB_EP5_CFG    UART_ARB_EP5_CFG_PTR
#define UART_ARB_EP5_INT_EN UART_ARB_EP5_INT_EN_PTR
#define UART_ARB_EP5_SR     UART_ARB_EP5_SR_PTR

#define UART_ARB_EP6_CFG    UART_ARB_EP6_CFG_PTR
#define UART_ARB_EP6_INT_EN UART_ARB_EP6_INT_EN_PTR
#define UART_ARB_EP6_SR     UART_ARB_EP6_SR_PTR

#define UART_ARB_EP7_CFG    UART_ARB_EP7_CFG_PTR
#define UART_ARB_EP7_INT_EN UART_ARB_EP7_INT_EN_PTR
#define UART_ARB_EP7_SR     UART_ARB_EP7_SR_PTR

#define UART_ARB_EP8_CFG    UART_ARB_EP8_CFG_PTR
#define UART_ARB_EP8_INT_EN UART_ARB_EP8_INT_EN_PTR
#define UART_ARB_EP8_SR     UART_ARB_EP8_SR_PTR

#define UART_ARB_INT_EN     UART_ARB_INT_EN_PTR
#define UART_ARB_INT_SR     UART_ARB_INT_SR_PTR

#define UART_ARB_RW1_DR     UART_ARB_RW1_DR_PTR
#define UART_ARB_RW1_RA     UART_ARB_RW1_RA_PTR
#define UART_ARB_RW1_RA_MSB UART_ARB_RW1_RA_MSB_PTR
#define UART_ARB_RW1_WA     UART_ARB_RW1_WA_PTR
#define UART_ARB_RW1_WA_MSB UART_ARB_RW1_WA_MSB_PTR

#define UART_ARB_RW2_DR     UART_ARB_RW2_DR_PTR
#define UART_ARB_RW2_RA     UART_ARB_RW2_RA_PTR
#define UART_ARB_RW2_RA_MSB UART_ARB_RW2_RA_MSB_PTR
#define UART_ARB_RW2_WA     UART_ARB_RW2_WA_PTR
#define UART_ARB_RW2_WA_MSB UART_ARB_RW2_WA_MSB_PTR

#define UART_ARB_RW3_DR     UART_ARB_RW3_DR_PTR
#define UART_ARB_RW3_RA     UART_ARB_RW3_RA_PTR
#define UART_ARB_RW3_RA_MSB UART_ARB_RW3_RA_MSB_PTR
#define UART_ARB_RW3_WA     UART_ARB_RW3_WA_PTR
#define UART_ARB_RW3_WA_MSB UART_ARB_RW3_WA_MSB_PTR

#define UART_ARB_RW4_DR     UART_ARB_RW4_DR_PTR
#define UART_ARB_RW4_RA     UART_ARB_RW4_RA_PTR
#define UART_ARB_RW4_RA_MSB UART_ARB_RW4_RA_MSB_PTR
#define UART_ARB_RW4_WA     UART_ARB_RW4_WA_PTR
#define UART_ARB_RW4_WA_MSB UART_ARB_RW4_WA_MSB_PTR

#define UART_ARB_RW5_DR     UART_ARB_RW5_DR_PTR
#define UART_ARB_RW5_RA     UART_ARB_RW5_RA_PTR
#define UART_ARB_RW5_RA_MSB UART_ARB_RW5_RA_MSB_PTR
#define UART_ARB_RW5_WA     UART_ARB_RW5_WA_PTR
#define UART_ARB_RW5_WA_MSB UART_ARB_RW5_WA_MSB_PTR

#define UART_ARB_RW6_DR     UART_ARB_RW6_DR_PTR
#define UART_ARB_RW6_RA     UART_ARB_RW6_RA_PTR
#define UART_ARB_RW6_RA_MSB UART_ARB_RW6_RA_MSB_PTR
#define UART_ARB_RW6_WA     UART_ARB_RW6_WA_PTR
#define UART_ARB_RW6_WA_MSB UART_ARB_RW6_WA_MSB_PTR

#define UART_ARB_RW7_DR     UART_ARB_RW7_DR_PTR
#define UART_ARB_RW7_RA     UART_ARB_RW7_RA_PTR
#define UART_ARB_RW7_RA_MSB UART_ARB_RW7_RA_MSB_PTR
#define UART_ARB_RW7_WA     UART_ARB_RW7_WA_PTR
#define UART_ARB_RW7_WA_MSB UART_ARB_RW7_WA_MSB_PTR

#define UART_ARB_RW8_DR     UART_ARB_RW8_DR_PTR
#define UART_ARB_RW8_RA     UART_ARB_RW8_RA_PTR
#define UART_ARB_RW8_RA_MSB UART_ARB_RW8_RA_MSB_PTR
#define UART_ARB_RW8_WA     UART_ARB_RW8_WA_PTR
#define UART_ARB_RW8_WA_MSB UART_ARB_RW8_WA_MSB_PTR

#define UART_BUF_SIZE       UART_BUF_SIZE_PTR
#define UART_BUS_RST_CNT    UART_BUS_RST_CNT_PTR
#define UART_CR0            UART_CR0_PTR
#define UART_CR1            UART_CR1_PTR
#define UART_CWA            UART_CWA_PTR
#define UART_CWA_MSB        UART_CWA_MSB_PTR

#define UART_DMA_THRES      UART_DMA_THRES_PTR
#define UART_DMA_THRES_MSB  UART_DMA_THRES_MSB_PTR

#define UART_EP_ACTIVE      UART_EP_ACTIVE_PTR
#define UART_EP_TYPE        UART_EP_TYPE_PTR

#define UART_EP0_CNT        UART_EP0_CNT_PTR
#define UART_EP0_CR         UART_EP0_CR_PTR
#define UART_EP0_DR0        UART_EP0_DR0_PTR
#define UART_EP0_DR1        UART_EP0_DR1_PTR
#define UART_EP0_DR2        UART_EP0_DR2_PTR
#define UART_EP0_DR3        UART_EP0_DR3_PTR
#define UART_EP0_DR4        UART_EP0_DR4_PTR
#define UART_EP0_DR5        UART_EP0_DR5_PTR
#define UART_EP0_DR6        UART_EP0_DR6_PTR
#define UART_EP0_DR7        UART_EP0_DR7_PTR

#define UART_OSCLK_DR0      UART_OSCLK_DR0_PTR
#define UART_OSCLK_DR1      UART_OSCLK_DR1_PTR

#define UART_PM_ACT_CFG     UART_PM_ACT_CFG_PTR
#define UART_PM_STBY_CFG    UART_PM_STBY_CFG_PTR

#define UART_SIE_EP_INT_EN  UART_SIE_EP_INT_EN_PTR
#define UART_SIE_EP_INT_SR  UART_SIE_EP_INT_SR_PTR

#define UART_SIE_EP1_CNT0   UART_SIE_EP1_CNT0_PTR
#define UART_SIE_EP1_CNT1   UART_SIE_EP1_CNT1_PTR
#define UART_SIE_EP1_CR0    UART_SIE_EP1_CR0_PTR

#define UART_SIE_EP2_CNT0   UART_SIE_EP2_CNT0_PTR
#define UART_SIE_EP2_CNT1   UART_SIE_EP2_CNT1_PTR
#define UART_SIE_EP2_CR0    UART_SIE_EP2_CR0_PTR

#define UART_SIE_EP3_CNT0   UART_SIE_EP3_CNT0_PTR
#define UART_SIE_EP3_CNT1   UART_SIE_EP3_CNT1_PTR
#define UART_SIE_EP3_CR0    UART_SIE_EP3_CR0_PTR

#define UART_SIE_EP4_CNT0   UART_SIE_EP4_CNT0_PTR
#define UART_SIE_EP4_CNT1   UART_SIE_EP4_CNT1_PTR
#define UART_SIE_EP4_CR0    UART_SIE_EP4_CR0_PTR

#define UART_SIE_EP5_CNT0   UART_SIE_EP5_CNT0_PTR
#define UART_SIE_EP5_CNT1   UART_SIE_EP5_CNT1_PTR
#define UART_SIE_EP5_CR0    UART_SIE_EP5_CR0_PTR

#define UART_SIE_EP6_CNT0   UART_SIE_EP6_CNT0_PTR
#define UART_SIE_EP6_CNT1   UART_SIE_EP6_CNT1_PTR
#define UART_SIE_EP6_CR0    UART_SIE_EP6_CR0_PTR

#define UART_SIE_EP7_CNT0   UART_SIE_EP7_CNT0_PTR
#define UART_SIE_EP7_CNT1   UART_SIE_EP7_CNT1_PTR
#define UART_SIE_EP7_CR0    UART_SIE_EP7_CR0_PTR

#define UART_SIE_EP8_CNT0   UART_SIE_EP8_CNT0_PTR
#define UART_SIE_EP8_CNT1   UART_SIE_EP8_CNT1_PTR
#define UART_SIE_EP8_CR0    UART_SIE_EP8_CR0_PTR

#define UART_SOF0           UART_SOF0_PTR
#define UART_SOF1           UART_SOF1_PTR

#define UART_USB_CLK_EN     UART_USB_CLK_EN_PTR

#define UART_USBIO_CR0      UART_USBIO_CR0_PTR
#define UART_USBIO_CR1      UART_USBIO_CR1_PTR
#define UART_USBIO_CR2      UART_USBIO_CR2_PTR

#define UART_USB_MEM        ((reg8 *) CYDEV_USB_MEM_BASE)

#if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
    /* PSoC3 interrupt registers*/
    #define UART_USB_ISR_PRIOR  ((reg8 *) CYDEV_INTC_PRIOR0)
    #define UART_USB_ISR_SET_EN ((reg8 *) CYDEV_INTC_SET_EN0)
    #define UART_USB_ISR_CLR_EN ((reg8 *) CYDEV_INTC_CLR_EN0)
    #define UART_USB_ISR_VECT   ((cyisraddress *) CYDEV_INTC_VECT_MBASE)
#elif(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_PANTHER)
    /* PSoC5 interrupt registers*/
    #define UART_USB_ISR_PRIOR  ((reg8 *) CYDEV_NVIC_PRI_0)
    #define UART_USB_ISR_SET_EN ((reg8 *) CYDEV_NVIC_SETENA0)
    #define UART_USB_ISR_CLR_EN ((reg8 *) CYDEV_NVIC_CLRENA0)
    #define UART_USB_ISR_VECT   ((cyisraddress *) CYDEV_NVIC_VECT_OFFSET)
#endif /*  CYDEV_CHIP_DIE_EXPECT */


/***************************************
* Interrupt vectors, masks and priorities
***************************************/

#define UART_BUS_RESET_PRIOR    UART_bus_reset__INTC_PRIOR_NUM
#define UART_BUS_RESET_MASK     UART_bus_reset__INTC_MASK
#define UART_BUS_RESET_VECT_NUM UART_bus_reset__INTC_NUMBER

#define UART_SOF_PRIOR          UART_sof_int__INTC_PRIOR_NUM
#define UART_SOF_MASK           UART_sof_int__INTC_MASK
#define UART_SOF_VECT_NUM       UART_sof_int__INTC_NUMBER

#define UART_EP_0_PRIOR         UART_ep_0__INTC_PRIOR_NUM
#define UART_EP_0_MASK          UART_ep_0__INTC_MASK
#define UART_EP_0_VECT_NUM      UART_ep_0__INTC_NUMBER

#define UART_EP_1_PRIOR         UART_ep_1__INTC_PRIOR_NUM
#define UART_EP_1_MASK          UART_ep_1__INTC_MASK
#define UART_EP_1_VECT_NUM      UART_ep_1__INTC_NUMBER

#define UART_EP_2_PRIOR         UART_ep_2__INTC_PRIOR_NUM
#define UART_EP_2_MASK          UART_ep_2__INTC_MASK
#define UART_EP_2_VECT_NUM      UART_ep_2__INTC_NUMBER

#define UART_EP_3_PRIOR         UART_ep_3__INTC_PRIOR_NUM
#define UART_EP_3_MASK          UART_ep_3__INTC_MASK
#define UART_EP_3_VECT_NUM      UART_ep_3__INTC_NUMBER

#define UART_EP_4_PRIOR         UART_ep_4__INTC_PRIOR_NUM
#define UART_EP_4_MASK          UART_ep_4__INTC_MASK
#define UART_EP_4_VECT_NUM      UART_ep_4__INTC_NUMBER

#define UART_EP_5_PRIOR         UART_ep_5__INTC_PRIOR_NUM
#define UART_EP_5_MASK          UART_ep_5__INTC_MASK
#define UART_EP_5_VECT_NUM      UART_ep_5__INTC_NUMBER

#define UART_EP_6_PRIOR         UART_ep_6__INTC_PRIOR_NUM
#define UART_EP_6_MASK          UART_ep_6__INTC_MASK
#define UART_EP_6_VECT_NUM      UART_ep_6__INTC_NUMBER

#define UART_EP_7_PRIOR         UART_ep_7__INTC_PRIOR_NUM
#define UART_EP_7_MASK          UART_ep_7__INTC_MASK
#define UART_EP_7_VECT_NUM      UART_ep_7__INTC_NUMBER

#define UART_EP_8_PRIOR         UART_ep_8__INTC_PRIOR_NUM
#define UART_EP_8_MASK          UART_ep_8__INTC_MASK
#define UART_EP_8_VECT_NUM      UART_ep_8__INTC_NUMBER

#define UART_DP_INTC_PRIOR      UART_dp_int__INTC_PRIOR_NUM
#define UART_DP_INTC_MASK       UART_dp_int__INTC_MASK
#define UART_DP_INTC_VECT_NUM   UART_dp_int__INTC_NUMBER

/* ARB ISR should have higher priority from EP_X ISR, therefore it is defined to highest (0) */
#define UART_ARB_PRIOR          (0u)
#define UART_ARB_MASK           UART_arb_int__INTC_MASK
#define UART_ARB_VECT_NUM       UART_arb_int__INTC_NUMBER

/***************************************
 *  Endpoint 0 offsets (Table 9-2)
 **************************************/

#define UART_bmRequestType      UART_EP0_DR0_PTR
#define UART_bRequest           UART_EP0_DR1_PTR
#define UART_wValue             UART_EP0_DR2_PTR
#define UART_wValueHi           UART_EP0_DR3_PTR
#define UART_wValueLo           UART_EP0_DR2_PTR
#define UART_wIndex             UART_EP0_DR4_PTR
#define UART_wIndexHi           UART_EP0_DR5_PTR
#define UART_wIndexLo           UART_EP0_DR4_PTR
#define UART_length             UART_EP0_DR6_PTR
#define UART_lengthHi           UART_EP0_DR7_PTR
#define UART_lengthLo           UART_EP0_DR6_PTR


/***************************************
*       Register Constants
***************************************/
#define UART_VDDD_MV                    CYDEV_VDDD_MV
#define UART_3500MV                     (3500u)

#define UART_CR1_REG_ENABLE             (0x01u)
#define UART_CR1_ENABLE_LOCK            (0x02u)
#define UART_CR1_BUS_ACTIVITY_SHIFT     (0x02u)
#define UART_CR1_BUS_ACTIVITY           ((uint8)(0x01u << UART_CR1_BUS_ACTIVITY_SHIFT))
#define UART_CR1_TRIM_MSB_EN            (0x08u)

#define UART_EP0_CNT_DATA_TOGGLE        (0x80u)
#define UART_EPX_CNT_DATA_TOGGLE        (0x80u)
#define UART_EPX_CNT0_MASK              (0x0Fu)
#define UART_EPX_CNTX_MSB_MASK          (0x07u)
#define UART_EPX_CNTX_ADDR_SHIFT        (0x04u)
#define UART_EPX_CNTX_ADDR_OFFSET       (0x10u)
#define UART_EPX_CNTX_CRC_COUNT         (0x02u)
#define UART_EPX_DATA_BUF_MAX           (512u)

#define UART_CR0_ENABLE                 (0x80u)

/* A 100 KHz clock is used for BUS reset count. Recommended is to count 10 pulses */
#define UART_BUS_RST_COUNT              (0x0au)

#define UART_USBIO_CR1_IOMODE           (0x20u)
#define UART_USBIO_CR1_USBPUEN          (0x04u)
#define UART_USBIO_CR1_DP0              (0x02u)
#define UART_USBIO_CR1_DM0              (0x01u)

#define UART_USBIO_CR0_TEN              (0x80u)
#define UART_USBIO_CR0_TSE0             (0x40u)
#define UART_USBIO_CR0_TD               (0x20u)
#define UART_USBIO_CR0_RD               (0x01u)

#define UART_FASTCLK_IMO_CR_USBCLK_ON   (0x40u)
#define UART_FASTCLK_IMO_CR_XCLKEN      (0x20u)
#define UART_FASTCLK_IMO_CR_FX2ON       (0x10u)

#define UART_ARB_EPX_CFG_RESET          (0x08u)
#define UART_ARB_EPX_CFG_CRC_BYPASS     (0x04u)
#define UART_ARB_EPX_CFG_DMA_REQ        (0x02u)
#define UART_ARB_EPX_CFG_IN_DATA_RDY    (0x01u)
#define UART_ARB_EPX_CFG_DEFAULT        (UART_ARB_EPX_CFG_RESET | \
                                                     UART_ARB_EPX_CFG_CRC_BYPASS)

#define UART_ARB_EPX_SR_IN_BUF_FULL     (0x01u)
#define UART_ARB_EPX_SR_DMA_GNT         (0x02u)
#define UART_ARB_EPX_SR_BUF_OVER        (0x04u)
#define UART_ARB_EPX_SR_BUF_UNDER       (0x08u)

#define UART_ARB_CFG_AUTO_MEM           (0x10u)
#define UART_ARB_CFG_MANUAL_DMA         (0x20u)
#define UART_ARB_CFG_AUTO_DMA           (0x40u)
#define UART_ARB_CFG_CFG_CPM            (0x80u)

#if(UART_EP_MM == UART__EP_DMAAUTO)
    #define UART_ARB_EPX_INT_MASK           (0x1Du)
#else
    #define UART_ARB_EPX_INT_MASK           (0x1Fu)
#endif /*  UART_EP_MM == UART__EP_DMAAUTO */
#define UART_ARB_INT_MASK       (uint8)((UART_DMA1_REMOVE ^ 1u) | \
                                            (uint8)((UART_DMA2_REMOVE ^ 1u) << 1u) | \
                                            (uint8)((UART_DMA3_REMOVE ^ 1u) << 2u) | \
                                            (uint8)((UART_DMA4_REMOVE ^ 1u) << 3u) | \
                                            (uint8)((UART_DMA5_REMOVE ^ 1u) << 4u) | \
                                            (uint8)((UART_DMA6_REMOVE ^ 1u) << 5u) | \
                                            (uint8)((UART_DMA7_REMOVE ^ 1u) << 6u) | \
                                            (uint8)((UART_DMA8_REMOVE ^ 1u) << 7u) )

#define UART_SIE_EP_INT_EP1_MASK        (0x01u)
#define UART_SIE_EP_INT_EP2_MASK        (0x02u)
#define UART_SIE_EP_INT_EP3_MASK        (0x04u)
#define UART_SIE_EP_INT_EP4_MASK        (0x08u)
#define UART_SIE_EP_INT_EP5_MASK        (0x10u)
#define UART_SIE_EP_INT_EP6_MASK        (0x20u)
#define UART_SIE_EP_INT_EP7_MASK        (0x40u)
#define UART_SIE_EP_INT_EP8_MASK        (0x80u)

#define UART_PM_ACT_EN_FSUSB            UART_USB__PM_ACT_MSK
#define UART_PM_STBY_EN_FSUSB           UART_USB__PM_STBY_MSK
#define UART_PM_AVAIL_EN_FSUSBIO        (0x10u)

#define UART_PM_USB_CR0_REF_EN          (0x01u)
#define UART_PM_USB_CR0_PD_N            (0x02u)
#define UART_PM_USB_CR0_PD_PULLUP_N     (0x04u)

#define UART_USB_CLK_ENABLE             (0x01u)

#define UART_DM_MASK                    UART_Dm__0__MASK
#define UART_DP_MASK                    UART_Dp__0__MASK

#define UART_DYN_RECONFIG_ENABLE        (0x01u)
#define UART_DYN_RECONFIG_EP_SHIFT      (0x01u)
#define UART_DYN_RECONFIG_RDY_STS       (0x10u)


#endif /*  CY_USBFS_UART_H */


/* [] END OF FILE */
