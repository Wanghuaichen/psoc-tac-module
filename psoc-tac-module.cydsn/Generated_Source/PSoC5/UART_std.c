/*******************************************************************************
* File Name: UART_std.c
* Version 2.80
*
* Description:
*  USB Standard request handler.
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
#include "UART_cdc.h"
#include "UART_pvt.h"
#if defined(UART_ENABLE_MIDI_STREAMING)
    #include "UART_midi.h"
#endif /*  UART_ENABLE_MIDI_STREAMING*/


/***************************************
*   Static data allocation
***************************************/

#if defined(UART_ENABLE_FWSN_STRING)
    static volatile uint8 *UART_fwSerialNumberStringDescriptor;
    static volatile uint8 UART_snStringConfirm = UART_FALSE;
#endif  /* UART_ENABLE_FWSN_STRING */

#if defined(UART_ENABLE_FWSN_STRING)

    /*******************************************************************************
    * Function Name: UART_SerialNumString
    ********************************************************************************
    *
    * Summary:
    *  Application firmware may supply the source of the USB device descriptors
    *  serial number string during runtime.
    *
    * Parameters:
    *  snString:  pointer to string.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void  UART_SerialNumString(uint8 snString[]) 
    {
        UART_snStringConfirm = UART_FALSE;
        if(snString != NULL)
        {
            /* Check descriptor validation */
            if( (snString[0u] > 1u ) && (snString[1u] == UART_DESCR_STRING) )
            {
                UART_fwSerialNumberStringDescriptor = snString;
                UART_snStringConfirm = UART_TRUE;
            }
        }
    }

#endif  /* UART_ENABLE_FWSN_STRING */


/*******************************************************************************
* Function Name: UART_HandleStandardRqst
********************************************************************************
*
* Summary:
*  This Routine dispatches standard requests
*
* Parameters:
*  None.
*
* Return:
*  TRUE if request handled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 UART_HandleStandardRqst(void) 
{
    uint8 requestHandled = UART_FALSE;
    uint8 interfaceNumber;
    uint8 configurationN;
    #if defined(UART_ENABLE_STRINGS)
        volatile uint8 *pStr = 0u;
        #if defined(UART_ENABLE_DESCRIPTOR_STRINGS)
            uint8 nStr;
            uint8 descrLength;
        #endif /* UART_ENABLE_DESCRIPTOR_STRINGS */
    #endif /* UART_ENABLE_STRINGS */
    static volatile uint8 UART_tBuffer[UART_STATUS_LENGTH_MAX];
    const T_UART_LUT CYCODE *pTmp;
    UART_currentTD.count = 0u;

    if ((CY_GET_REG8(UART_bmRequestType) & UART_RQST_DIR_MASK) == UART_RQST_DIR_D2H)
    {
        /* Control Read */
        switch (CY_GET_REG8(UART_bRequest))
        {
            case UART_GET_DESCRIPTOR:
                if (CY_GET_REG8(UART_wValueHi) == UART_DESCR_DEVICE)
                {
                    pTmp = UART_GetDeviceTablePtr();
                    UART_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                    UART_currentTD.count = UART_DEVICE_DESCR_LENGTH;
                    requestHandled  = UART_InitControlRead();
                }
                else if (CY_GET_REG8(UART_wValueHi) == UART_DESCR_CONFIG)
                {
                    pTmp = UART_GetConfigTablePtr(CY_GET_REG8(UART_wValueLo));
                    if( pTmp != NULL )  /* Verify that requested descriptor exists */
                    {
                        UART_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                        UART_currentTD.count = ((uint16)(UART_currentTD.pData)[ \
                                          UART_CONFIG_DESCR_TOTAL_LENGTH_HI] << 8u) | \
                                         (UART_currentTD.pData)[UART_CONFIG_DESCR_TOTAL_LENGTH_LOW];
                        requestHandled  = UART_InitControlRead();
                    }
                }
                #if defined(UART_ENABLE_STRINGS)
                else if (CY_GET_REG8(UART_wValueHi) == UART_DESCR_STRING)
                {
                    /* Descriptor Strings*/
                    #if defined(UART_ENABLE_DESCRIPTOR_STRINGS)
                        nStr = 0u;
                        pStr = (volatile uint8 *)&UART_STRING_DESCRIPTORS[0u];
                        while ( (CY_GET_REG8(UART_wValueLo) > nStr) && (*pStr != 0u) )
                        {
                            /* Read descriptor length from 1st byte */
                            descrLength = *pStr;
                            /* Move to next string descriptor */
                            pStr = &pStr[descrLength];
                            nStr++;
                        }
                    #endif /*  UART_ENABLE_DESCRIPTOR_STRINGS */
                    /* Microsoft OS String*/
                    #if defined(UART_ENABLE_MSOS_STRING)
                        if( CY_GET_REG8(UART_wValueLo) == UART_STRING_MSOS )
                        {
                            pStr = (volatile uint8 *)&UART_MSOS_DESCRIPTOR[0u];
                        }
                    #endif /*  UART_ENABLE_MSOS_STRING*/
                    /* SN string */
                    #if defined(UART_ENABLE_SN_STRING)
                        if( (CY_GET_REG8(UART_wValueLo) != 0u) &&
                            (CY_GET_REG8(UART_wValueLo) ==
                            UART_DEVICE0_DESCR[UART_DEVICE_DESCR_SN_SHIFT]) )
                        {

                            #if defined(UART_ENABLE_IDSN_STRING)
                                /* Read DIE ID and generate string descriptor in RAM */
                                UART_ReadDieID(UART_idSerialNumberStringDescriptor);
                                pStr = UART_idSerialNumberStringDescriptor;
                            #elif defined(UART_ENABLE_FWSN_STRING)
                                if(UART_snStringConfirm != UART_FALSE)
                                {
                                    pStr = UART_fwSerialNumberStringDescriptor;
                                }
                                else
                                {
                                    pStr = (volatile uint8 *)&UART_SN_STRING_DESCRIPTOR[0u];
                                }
                            #else
                                pStr = (volatile uint8 *)&UART_SN_STRING_DESCRIPTOR[0u];
                            #endif  /* defined(UART_ENABLE_IDSN_STRING) */
                        }
                    #endif    /*  UART_ENABLE_SN_STRING */
                    if (*pStr != 0u)
                    {
                        UART_currentTD.count = *pStr;
                        UART_currentTD.pData = pStr;
                        requestHandled  = UART_InitControlRead();
                    }
                }
                #endif /*  UART_ENABLE_STRINGS */
                else
                {
                    requestHandled = UART_DispatchClassRqst();
                }
                break;
            case UART_GET_STATUS:
                switch ((CY_GET_REG8(UART_bmRequestType) & UART_RQST_RCPT_MASK))
                {
                    case UART_RQST_RCPT_EP:
                        UART_currentTD.count = UART_EP_STATUS_LENGTH;
                        UART_tBuffer[0u] = UART_EP[ \
                                        CY_GET_REG8(UART_wIndexLo) & UART_DIR_UNUSED].hwEpState;
                        UART_tBuffer[1u] = 0u;
                        UART_currentTD.pData = &UART_tBuffer[0u];
                        requestHandled  = UART_InitControlRead();
                        break;
                    case UART_RQST_RCPT_DEV:
                        UART_currentTD.count = UART_DEVICE_STATUS_LENGTH;
                        UART_tBuffer[0u] = UART_deviceStatus;
                        UART_tBuffer[1u] = 0u;
                        UART_currentTD.pData = &UART_tBuffer[0u];
                        requestHandled  = UART_InitControlRead();
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
            case UART_GET_CONFIGURATION:
                UART_currentTD.count = 1u;
                UART_currentTD.pData = (volatile uint8 *)&UART_configuration;
                requestHandled  = UART_InitControlRead();
                break;
            case UART_GET_INTERFACE:
                UART_currentTD.count = 1u;
                UART_currentTD.pData = (volatile uint8 *)&UART_interfaceSetting[ \
                                                                            CY_GET_REG8(UART_wIndexLo)];
                requestHandled  = UART_InitControlRead();
                break;
            default: /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else {
        /* Control Write */
        switch (CY_GET_REG8(UART_bRequest))
        {
            case UART_SET_ADDRESS:
                UART_deviceAddress = CY_GET_REG8(UART_wValueLo);
                requestHandled = UART_InitNoDataControlTransfer();
                break;
            case UART_SET_CONFIGURATION:
                configurationN = CY_GET_REG8(UART_wValueLo);
                if(configurationN > 0u)
                {   /* Verify that configuration descriptor exists */
                    pTmp = UART_GetConfigTablePtr(configurationN - 1u);
                }
                /* Responds with a Request Error when configuration number is invalid */
                if (((configurationN > 0u) && (pTmp != NULL)) || (configurationN == 0u))
                {
                    /* Set new configuration if it has been changed */
                    if(configurationN != UART_configuration)
                    {
                        UART_configuration = configurationN;
                        UART_configurationChanged = UART_TRUE;
                        UART_Config(UART_TRUE);
                    }
                    requestHandled = UART_InitNoDataControlTransfer();
                }
                break;
            case UART_SET_INTERFACE:
                if (UART_ValidateAlternateSetting() != 0u)
                {
                    interfaceNumber = CY_GET_REG8(UART_wIndexLo);
                    UART_interfaceNumber = interfaceNumber;
                    UART_configurationChanged = UART_TRUE;
                    #if ((UART_EP_MA == UART__MA_DYNAMIC) && \
                         (UART_EP_MM == UART__EP_MANUAL) )
                        UART_Config(UART_FALSE);
                    #else
                        UART_ConfigAltChanged();
                    #endif /*  (UART_EP_MA == UART__MA_DYNAMIC) */
                    /* Update handled Alt setting changes status */
                    UART_interfaceSetting_last[interfaceNumber] =
                         UART_interfaceSetting[interfaceNumber];
                    requestHandled = UART_InitNoDataControlTransfer();
                }
                break;
            case UART_CLEAR_FEATURE:
                switch (CY_GET_REG8(UART_bmRequestType) & UART_RQST_RCPT_MASK)
                {
                    case UART_RQST_RCPT_EP:
                        if (CY_GET_REG8(UART_wValueLo) == UART_ENDPOINT_HALT)
                        {
                            requestHandled = UART_ClearEndpointHalt();
                        }
                        break;
                    case UART_RQST_RCPT_DEV:
                        /* Clear device REMOTE_WAKEUP */
                        if (CY_GET_REG8(UART_wValueLo) == UART_DEVICE_REMOTE_WAKEUP)
                        {
                            UART_deviceStatus &= (uint8)~UART_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = UART_InitNoDataControlTransfer();
                        }
                        break;
                    case UART_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (CY_GET_REG8(UART_wIndexLo) < UART_MAX_INTERFACES_NUMBER)
                        {
                            UART_interfaceStatus[CY_GET_REG8(UART_wIndexLo)] &=
                                                                (uint8)~(CY_GET_REG8(UART_wValueLo));
                            requestHandled = UART_InitNoDataControlTransfer();
                        }
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
            case UART_SET_FEATURE:
                switch (CY_GET_REG8(UART_bmRequestType) & UART_RQST_RCPT_MASK)
                {
                    case UART_RQST_RCPT_EP:
                        if (CY_GET_REG8(UART_wValueLo) == UART_ENDPOINT_HALT)
                        {
                            requestHandled = UART_SetEndpointHalt();
                        }
                        break;
                    case UART_RQST_RCPT_DEV:
                        /* Set device REMOTE_WAKEUP */
                        if (CY_GET_REG8(UART_wValueLo) == UART_DEVICE_REMOTE_WAKEUP)
                        {
                            UART_deviceStatus |= UART_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = UART_InitNoDataControlTransfer();
                        }
                        break;
                    case UART_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (CY_GET_REG8(UART_wIndexLo) < UART_MAX_INTERFACES_NUMBER)
                        {
                            UART_interfaceStatus[CY_GET_REG8(UART_wIndexLo)] &=
                                                                (uint8)~(CY_GET_REG8(UART_wValueLo));
                            requestHandled = UART_InitNoDataControlTransfer();
                        }
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    return(requestHandled);
}


#if defined(UART_ENABLE_IDSN_STRING)

    /***************************************************************************
    * Function Name: UART_ReadDieID
    ****************************************************************************
    *
    * Summary:
    *  This routine read Die ID and generate Serial Number string descriptor.
    *
    * Parameters:
    *  descr:  pointer on string descriptor.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ***************************************************************************/
    void UART_ReadDieID(uint8 descr[]) 
    {
        uint8 i;
        uint8 j = 0u;
        uint8 value;
        const char8 CYCODE hex[16u] = "0123456789ABCDEF";

        /* Check descriptor validation */
        if( descr != NULL)
        {
            descr[0u] = UART_IDSN_DESCR_LENGTH;
            descr[1u] = UART_DESCR_STRING;

            /* fill descriptor */
            for(i = 2u; i < UART_IDSN_DESCR_LENGTH; i += 4u)
            {
                value = CY_GET_XTND_REG8((void CYFAR *)(UART_DIE_ID + j));
                j++;
                descr[i] = (uint8)hex[value >> 4u];
                descr[i + 2u] = (uint8)hex[value & 0x0Fu];
            }
        }
    }

#endif /*  UART_ENABLE_IDSN_STRING */


/*******************************************************************************
* Function Name: UART_ConfigReg
********************************************************************************
*
* Summary:
*  This routine configures hardware registers from the variables.
*  It is called from UART_Config() function and from RestoreConfig
*  after Wakeup.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void UART_ConfigReg(void) 
{
    uint8 ep;
    uint8 i;
    #if(UART_EP_MM == UART__EP_DMAAUTO)
        uint8 epType = 0u;
    #endif /*  UART_EP_MM == UART__EP_DMAAUTO */

    /* Set the endpoint buffer addresses */
    ep = UART_EP1;
    for (i = 0u; i < 0x80u; i+= 0x10u)
    {
        CY_SET_REG8((reg8 *)(UART_ARB_EP1_CFG_IND + i), UART_ARB_EPX_CFG_DEFAULT);
        #if(UART_EP_MM != UART__EP_MANUAL)
            /* Enable all Arbiter EP Interrupts : err, buf under, buf over, dma gnt(mode2 only), in buf full */
            CY_SET_REG8((reg8 *)(UART_ARB_EP1_INT_EN_IND + i), UART_ARB_EPX_INT_MASK);
        #endif   /*  UART_EP_MM != UART__EP_MANUAL */

        if(UART_EP[ep].epMode != UART_MODE_DISABLE)
        {
            if((UART_EP[ep].addr & UART_DIR_IN) != 0u )
            {
                CY_SET_REG8((reg8 *)(UART_SIE_EP1_CR0_IND + i), UART_MODE_NAK_IN);
            }
            else
            {
                CY_SET_REG8((reg8 *)(UART_SIE_EP1_CR0_IND + i), UART_MODE_NAK_OUT);
                /* Prepare EP type mask for automatic memory allocation */
                #if(UART_EP_MM == UART__EP_DMAAUTO)
                    epType |= (uint8)(0x01u << (ep - UART_EP1));
                #endif /*  UART_EP_MM == UART__EP_DMAAUTO */
            }
        }
        else
        {
            CY_SET_REG8((reg8 *)(UART_SIE_EP1_CR0_IND + i), UART_MODE_STALL_DATA_EP);
        }

        #if(UART_EP_MM != UART__EP_DMAAUTO)
            CY_SET_REG8((reg8 *)(UART_SIE_EP1_CNT0_IND + i),   UART_EP[ep].bufferSize >> 8u);
            CY_SET_REG8((reg8 *)(UART_SIE_EP1_CNT1_IND + i),   UART_EP[ep].bufferSize & 0xFFu);

            CY_SET_REG8((reg8 *)(UART_ARB_RW1_RA_IND + i),     UART_EP[ep].buffOffset & 0xFFu);
            CY_SET_REG8((reg8 *)(UART_ARB_RW1_RA_MSB_IND + i), UART_EP[ep].buffOffset >> 8u);
            CY_SET_REG8((reg8 *)(UART_ARB_RW1_WA_IND + i),     UART_EP[ep].buffOffset & 0xFFu);
            CY_SET_REG8((reg8 *)(UART_ARB_RW1_WA_MSB_IND + i), UART_EP[ep].buffOffset >> 8u);
        #endif /*  UART_EP_MM != UART__EP_DMAAUTO */

        ep++;
    }

    #if(UART_EP_MM == UART__EP_DMAAUTO)
         /* BUF_SIZE depend on DMA_THRESS value: 55-32 bytes  44-16 bytes 33-8 bytes 22-4 bytes 11-2 bytes */
        UART_BUF_SIZE_REG = UART_DMA_BUF_SIZE;
        UART_DMA_THRES_REG = UART_DMA_BYTES_PER_BURST;   /* DMA burst threshold */
        UART_DMA_THRES_MSB_REG = 0u;
        UART_EP_ACTIVE_REG = UART_ARB_INT_MASK;
        UART_EP_TYPE_REG = epType;
        /* Cfg_cmp bit set to 1 once configuration is complete. */
        UART_ARB_CFG_REG = UART_ARB_CFG_AUTO_DMA | UART_ARB_CFG_AUTO_MEM |
                                       UART_ARB_CFG_CFG_CPM;
        /* Cfg_cmp bit set to 0 during configuration of PFSUSB Registers. */
        UART_ARB_CFG_REG = UART_ARB_CFG_AUTO_DMA | UART_ARB_CFG_AUTO_MEM;
    #endif /*  UART_EP_MM == UART__EP_DMAAUTO */

    CY_SET_REG8(UART_SIE_EP_INT_EN_PTR, 0xFFu);
}


/*******************************************************************************
* Function Name: UART_Config
********************************************************************************
*
* Summary:
*  This routine configures endpoints for the entire configuration by scanning
*  the configuration descriptor.
*
* Parameters:
*  clearAltSetting: It configures the bAlternateSetting 0 for each interface.
*
* Return:
*  None.
*
* UART_interfaceClass - Initialized class array for each interface.
*   It is used for handling Class specific requests depend on interface class.
*   Different classes in multiple Alternate settings does not supported.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Config(uint8 clearAltSetting) 
{
    uint8 ep;
    uint8 cur_ep;
    uint8 i;
    uint8 epType;
    const uint8 *pDescr;
    #if(UART_EP_MM != UART__EP_DMAAUTO)
        uint16 buffCount = 0u;
    #endif /*  UART_EP_MM != UART__EP_DMAAUTO */

    const T_UART_LUT CYCODE *pTmp;
    const T_UART_EP_SETTINGS_BLOCK CYCODE *pEP;

    /* Clear all of the endpoints */
    for (ep = 0u; ep < UART_MAX_EP; ep++)
    {
        UART_EP[ep].attrib = 0u;
        UART_EP[ep].hwEpState = 0u;
        UART_EP[ep].apiEpState = UART_NO_EVENT_PENDING;
        UART_EP[ep].epToggle = 0u;
        UART_EP[ep].epMode = UART_MODE_DISABLE;
        UART_EP[ep].bufferSize = 0u;
        UART_EP[ep].interface = 0u;

    }

    /* Clear Alternate settings for all interfaces */
    if(clearAltSetting != 0u)
    {
        for (i = 0u; i < UART_MAX_INTERFACES_NUMBER; i++)
        {
            UART_interfaceSetting[i] = 0x00u;
            UART_interfaceSetting_last[i] = 0x00u;
        }
    }

    /* Init Endpoints and Device Status if configured */
    if(UART_configuration > 0u)
    {
        pTmp = UART_GetConfigTablePtr(UART_configuration - 1u);
        /* Set Power status for current configuration */
        pDescr = (const uint8 *)pTmp->p_list;
        if((pDescr[UART_CONFIG_DESCR_ATTRIB] & UART_CONFIG_DESCR_ATTRIB_SELF_POWERED) != 0u)
        {
            UART_deviceStatus |=  UART_DEVICE_STATUS_SELF_POWERED;
        }
        else
        {
            UART_deviceStatus &=  (uint8)~UART_DEVICE_STATUS_SELF_POWERED;
        }
        /* Move to next element */
        pTmp = &pTmp[1u];
        ep = pTmp->c;  /* For this table, c is the number of endpoints configurations  */

        #if ((UART_EP_MA == UART__MA_DYNAMIC) && \
             (UART_EP_MM == UART__EP_MANUAL) )
            /* Configure for dynamic EP memory allocation */
            /* p_list points the endpoint setting table. */
            pEP = (T_UART_EP_SETTINGS_BLOCK *) pTmp->p_list;
            for (i = 0u; i < ep; i++)
            {
                /* Compare current Alternate setting with EP Alt */
                if(UART_interfaceSetting[pEP->interface] == pEP->altSetting)
                {
                    cur_ep = pEP->addr & UART_DIR_UNUSED;
                    epType = pEP->attributes & UART_EP_TYPE_MASK;
                    if (pEP->addr & UART_DIR_IN)
                    {
                        /* IN Endpoint */
                        UART_EP[cur_ep].apiEpState = UART_EVENT_PENDING;
                        UART_EP[cur_ep].epMode = (epType == UART_EP_TYPE_ISOC) ?
                                                        UART_MODE_ISO_IN : UART_MODE_ACK_IN;
                        #if defined(UART_ENABLE_CDC_CLASS)
                            if(((pEP->bMisc == UART_CLASS_CDC_DATA) ||
                                (pEP->bMisc == UART_CLASS_CDC)) &&
                                (epType != UART_EP_TYPE_INT))
                            {
                                UART_cdc_data_in_ep = cur_ep;
                            }
                        #endif  /*  UART_ENABLE_CDC_CLASS*/
                        #if ( defined(UART_ENABLE_MIDI_STREAMING) && \
                                             (UART_MIDI_IN_BUFF_SIZE > 0) )
                            if((pEP->bMisc == UART_CLASS_AUDIO) &&
                               (epType == UART_EP_TYPE_BULK))
                            {
                                UART_midi_in_ep = cur_ep;
                            }
                        #endif  /*  UART_ENABLE_MIDI_STREAMING*/
                    }
                    else
                    {
                        /* OUT Endpoint */
                        UART_EP[cur_ep].apiEpState = UART_NO_EVENT_PENDING;
                        UART_EP[cur_ep].epMode = (epType == UART_EP_TYPE_ISOC) ?
                                                    UART_MODE_ISO_OUT : UART_MODE_ACK_OUT;
                        #if defined(UART_ENABLE_CDC_CLASS)
                            if(((pEP->bMisc == UART_CLASS_CDC_DATA) ||
                                (pEP->bMisc == UART_CLASS_CDC)) &&
                                (epType != UART_EP_TYPE_INT))
                            {
                                UART_cdc_data_out_ep = cur_ep;
                            }
                        #endif  /*  UART_ENABLE_CDC_CLASS*/
                        #if ( defined(UART_ENABLE_MIDI_STREAMING) && \
                                     (UART_MIDI_OUT_BUFF_SIZE > 0) )
                            if((pEP->bMisc == UART_CLASS_AUDIO) &&
                               (epType == UART_EP_TYPE_BULK))
                            {
                                UART_midi_out_ep = cur_ep;
                            }
                        #endif  /*  UART_ENABLE_MIDI_STREAMING*/
                    }
                    UART_EP[cur_ep].bufferSize = pEP->bufferSize;
                    UART_EP[cur_ep].addr = pEP->addr;
                    UART_EP[cur_ep].attrib = pEP->attributes;
                }
                pEP = &pEP[1u];
            }
        #else /* Configure for static EP memory allocation  */
            for (i = UART_EP1; i < UART_MAX_EP; i++)
            {
                /* p_list points the endpoint setting table. */
                pEP = (const T_UART_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
                /* Find max length for each EP and select it (length could be different in different Alt settings) */
                /* but other settings should be correct with regards to Interface alt Setting */
                for (cur_ep = 0u; cur_ep < ep; cur_ep++)
                {
                    /* EP count is equal to EP # in table and we found larger EP length than have before*/
                    if(i == (pEP->addr & UART_DIR_UNUSED))
                    {
                        if(UART_EP[i].bufferSize < pEP->bufferSize)
                        {
                            UART_EP[i].bufferSize = pEP->bufferSize;
                        }
                        /* Compare current Alternate setting with EP Alt*/
                        if(UART_interfaceSetting[pEP->interface] == pEP->altSetting)
                        {
                            epType = pEP->attributes & UART_EP_TYPE_MASK;
                            if ((pEP->addr & UART_DIR_IN) != 0u)
                            {
                                /* IN Endpoint */
                                UART_EP[i].apiEpState = UART_EVENT_PENDING;
                                UART_EP[i].epMode = (epType == UART_EP_TYPE_ISOC) ?
                                                        UART_MODE_ISO_IN : UART_MODE_ACK_IN;
                                /* Find and initialize CDC IN endpoint number */
                                #if defined(UART_ENABLE_CDC_CLASS)
                                    if(((pEP->bMisc == UART_CLASS_CDC_DATA) ||
                                        (pEP->bMisc == UART_CLASS_CDC)) &&
                                        (epType != UART_EP_TYPE_INT))
                                    {
                                        UART_cdc_data_in_ep = i;
                                    }
                                #endif  /*  UART_ENABLE_CDC_CLASS*/
                                #if ( defined(UART_ENABLE_MIDI_STREAMING) && \
                                             (UART_MIDI_IN_BUFF_SIZE > 0) )
                                    if((pEP->bMisc == UART_CLASS_AUDIO) &&
                                       (epType == UART_EP_TYPE_BULK))
                                    {
                                        UART_midi_in_ep = i;
                                    }
                                #endif  /*  UART_ENABLE_MIDI_STREAMING*/
                            }
                            else
                            {
                                /* OUT Endpoint */
                                UART_EP[i].apiEpState = UART_NO_EVENT_PENDING;
                                UART_EP[i].epMode = (epType == UART_EP_TYPE_ISOC) ?
                                                    UART_MODE_ISO_OUT : UART_MODE_ACK_OUT;
                                /* Find and initialize CDC IN endpoint number */
                                #if defined(UART_ENABLE_CDC_CLASS)
                                    if(((pEP->bMisc == UART_CLASS_CDC_DATA) ||
                                        (pEP->bMisc == UART_CLASS_CDC)) &&
                                        (epType != UART_EP_TYPE_INT))
                                    {
                                        UART_cdc_data_out_ep = i;
                                    }
                                #endif  /*  UART_ENABLE_CDC_CLASS*/
                                #if ( defined(UART_ENABLE_MIDI_STREAMING) && \
                                             (UART_MIDI_OUT_BUFF_SIZE > 0) )
                                    if((pEP->bMisc == UART_CLASS_AUDIO) &&
                                       (epType == UART_EP_TYPE_BULK))
                                    {
                                        UART_midi_out_ep = i;
                                    }
                                #endif  /*  UART_ENABLE_MIDI_STREAMING*/
                            }
                            UART_EP[i].addr = pEP->addr;
                            UART_EP[i].attrib = pEP->attributes;

                            #if(UART_EP_MM == UART__EP_DMAAUTO)
                                break;      /* use first EP setting in Auto memory managment */
                            #endif /*  UART_EP_MM == UART__EP_DMAAUTO */
                        }
                    }
                    pEP = &pEP[1u];
                }
            }
        #endif /*  (UART_EP_MA == UART__MA_DYNAMIC) */

        /* Init class array for each interface and interface number for each EP.
        *  It is used for handling Class specific requests directed to either an
        *  interface or the endpoint.
        */
        /* p_list points the endpoint setting table. */
        pEP = (const T_UART_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        for (i = 0u; i < ep; i++)
        {
            /* Configure interface number for each EP*/
            UART_EP[pEP->addr & UART_DIR_UNUSED].interface = pEP->interface;
            pEP = &pEP[1u];
        }
        /* Init pointer on interface class table*/
        UART_interfaceClass = UART_GetInterfaceClassTablePtr();
        /* Set the endpoint buffer addresses */

        #if(UART_EP_MM != UART__EP_DMAAUTO)
            for (ep = UART_EP1; ep < UART_MAX_EP; ep++)
            {
                UART_EP[ep].buffOffset = buffCount;
                 buffCount += UART_EP[ep].bufferSize;
            }
        #endif /*  UART_EP_MM != UART__EP_DMAAUTO */

        /* Configure hardware registers */
        UART_ConfigReg();
    } /* UART_configuration > 0 */
}


/*******************************************************************************
* Function Name: UART_ConfigAltChanged
********************************************************************************
*
* Summary:
*  This routine update configuration for the required endpoints only.
*  It is called after SET_INTERFACE request when Static memory allocation used.
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
void UART_ConfigAltChanged(void) 
{
    uint8 ep;
    uint8 cur_ep;
    uint8 i;
    uint8 epType;
    uint8 ri;

    const T_UART_LUT CYCODE *pTmp;
    const T_UART_EP_SETTINGS_BLOCK CYCODE *pEP;


    /* Init Endpoints and Device Status if configured */
    if(UART_configuration > 0u)
    {
        pTmp = UART_GetConfigTablePtr(UART_configuration - 1u);
        pTmp = &pTmp[1u];
        ep = pTmp->c;  /* For this table, c is the number of endpoints configurations  */

        /* Do not touch EP which doesn't need reconfiguration */
        /* When Alt setting changed, the only required endpoints need to be reconfigured */
        /* p_list points the endpoint setting table. */
        pEP = (const T_UART_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        for (i = 0u; i < ep; i++)
        {
            /*If Alt setting changed and new is same with EP Alt */
            if((UART_interfaceSetting[pEP->interface] !=
                UART_interfaceSetting_last[pEP->interface] ) &&
               (UART_interfaceSetting[pEP->interface] == pEP->altSetting) &&
               (pEP->interface == CY_GET_REG8(UART_wIndexLo)))
            {
                cur_ep = pEP->addr & UART_DIR_UNUSED;
                ri = ((cur_ep - UART_EP1) << UART_EPX_CNTX_ADDR_SHIFT);
                epType = pEP->attributes & UART_EP_TYPE_MASK;
                if ((pEP->addr & UART_DIR_IN) != 0u)
                {
                    /* IN Endpoint */
                    UART_EP[cur_ep].apiEpState = UART_EVENT_PENDING;
                    UART_EP[cur_ep].epMode = (epType == UART_EP_TYPE_ISOC) ?
                                                UART_MODE_ISO_IN : UART_MODE_ACK_IN;
                }
                else
                {
                    /* OUT Endpoint */
                    UART_EP[cur_ep].apiEpState = UART_NO_EVENT_PENDING;
                    UART_EP[cur_ep].epMode = (epType == UART_EP_TYPE_ISOC) ?
                                                UART_MODE_ISO_OUT : UART_MODE_ACK_OUT;
                }
                 /* Change the SIE mode for the selected EP to NAK ALL */
                 CY_SET_REG8((reg8 *)(UART_SIE_EP1_CR0_IND + ri), UART_MODE_NAK_IN_OUT);
                UART_EP[cur_ep].bufferSize = pEP->bufferSize;
                UART_EP[cur_ep].addr = pEP->addr;
                UART_EP[cur_ep].attrib = pEP->attributes;

                /* Clear the data toggle */
                UART_EP[cur_ep].epToggle = 0u;

                /* Dynamic reconfiguration for mode 3 transfer */
            #if(UART_EP_MM == UART__EP_DMAAUTO)
                /* In_data_rdy for selected EP should be set to 0 */
                * (reg8 *)(UART_ARB_EP1_CFG_IND + ri) &= (uint8)~UART_ARB_EPX_CFG_IN_DATA_RDY;

                /* write the EP number for which reconfiguration is required */
                UART_DYN_RECONFIG_REG = (cur_ep - UART_EP1) <<
                                                    UART_DYN_RECONFIG_EP_SHIFT;
                /* Set the dyn_config_en bit in dynamic reconfiguration register */
                UART_DYN_RECONFIG_REG |= UART_DYN_RECONFIG_ENABLE;
                /* wait for the dyn_config_rdy bit to set by the block,
                *  this bit will be set to 1 when block is ready for reconfiguration.
                */
                while((UART_DYN_RECONFIG_REG & UART_DYN_RECONFIG_RDY_STS) == 0u)
                {
                    ;
                }
                /* Once dyn_config_rdy bit is set, FW can change the EP configuration. */
                /* Change EP Type with new direction */
                if((pEP->addr & UART_DIR_IN) == 0u)
                {
                    UART_EP_TYPE_REG |= (uint8)(0x01u << (cur_ep - UART_EP1));
                }
                else
                {
                    UART_EP_TYPE_REG &= (uint8)~(uint8)(0x01u << (cur_ep - UART_EP1));
                }
                /* dynamic reconfiguration enable bit cleared, pointers and control/status
                *  signals for the selected EP is cleared/re-initialized on negative edge
                *  of dynamic reconfiguration enable bit).
                */
                UART_DYN_RECONFIG_REG &= (uint8)~UART_DYN_RECONFIG_ENABLE;
                /* The main loop has to re-enable DMA and OUT endpoint*/
            #else
                CY_SET_REG8((reg8 *)(UART_SIE_EP1_CNT0_IND + ri),
                                                                UART_EP[cur_ep].bufferSize >> 8u);
                CY_SET_REG8((reg8 *)(UART_SIE_EP1_CNT1_IND + ri),
                                                                UART_EP[cur_ep].bufferSize & 0xFFu);
                CY_SET_REG8((reg8 *)(UART_ARB_RW1_RA_IND + ri),
                                                                UART_EP[cur_ep].buffOffset & 0xFFu);
                CY_SET_REG8((reg8 *)(UART_ARB_RW1_RA_MSB_IND + ri),
                                                                UART_EP[cur_ep].buffOffset >> 8u);
                CY_SET_REG8((reg8 *)(UART_ARB_RW1_WA_IND + ri),
                                                                UART_EP[cur_ep].buffOffset & 0xFFu);
                CY_SET_REG8((reg8 *)(UART_ARB_RW1_WA_MSB_IND + ri),
                                                                UART_EP[cur_ep].buffOffset >> 8u);
            #endif /*  UART_EP_MM == UART__EP_DMAAUTO */
            }
            /* Get next EP element */
            pEP = &pEP[1u];
        }
    }   /* UART_configuration > 0 */
}


/*******************************************************************************
* Function Name: UART_GetConfigTablePtr
********************************************************************************
*
* Summary:
*  This routine returns a pointer a configuration table entry
*
* Parameters:
*  confIndex:  Configuration Index
*
* Return:
*  Device Descriptor pointer or NULL when descriptor isn't exists.
*
*******************************************************************************/
const T_UART_LUT CYCODE *UART_GetConfigTablePtr(uint8 confIndex)
                                                        
{
    /* Device Table */
    const T_UART_LUT CYCODE *pTmp;

    pTmp = (const T_UART_LUT CYCODE *) UART_TABLE[UART_device].p_list;

    /* The first entry points to the Device Descriptor,
    *  the rest configuration entries.
    *  Set pointer to the first Configuration Descriptor
    */
    pTmp = &pTmp[1u];
    /* For this table, c is the number of configuration descriptors  */
    if(confIndex >= pTmp->c)   /* Verify that required configuration descriptor exists */
    {
        pTmp = (const T_UART_LUT CYCODE *) NULL;
    }
    else
    {
        pTmp = (const T_UART_LUT CYCODE *) pTmp[confIndex].p_list;
    }

    return( pTmp );
}


/*******************************************************************************
* Function Name: UART_GetDeviceTablePtr
********************************************************************************
*
* Summary:
*  This routine returns a pointer to the Device table
*
* Parameters:
*  None.
*
* Return:
*  Device Table pointer
*
*******************************************************************************/
const T_UART_LUT CYCODE *UART_GetDeviceTablePtr(void)
                                                            
{
    /* Device Table */
    return( (const T_UART_LUT CYCODE *) UART_TABLE[UART_device].p_list );
}


/*******************************************************************************
* Function Name: USB_GetInterfaceClassTablePtr
********************************************************************************
*
* Summary:
*  This routine returns Interface Class table pointer, which contains
*  the relation between interface number and interface class.
*
* Parameters:
*  None.
*
* Return:
*  Interface Class table pointer.
*
*******************************************************************************/
const uint8 CYCODE *UART_GetInterfaceClassTablePtr(void)
                                                        
{
    const T_UART_LUT CYCODE *pTmp;
    const uint8 CYCODE *pInterfaceClass;
    uint8 currentInterfacesNum;

    pTmp = UART_GetConfigTablePtr(UART_configuration - 1u);
    if( pTmp != NULL )
    {
        currentInterfacesNum  = ((const uint8 *) pTmp->p_list)[UART_CONFIG_DESCR_NUM_INTERFACES];
        /* Third entry in the LUT starts the Interface Table pointers */
        /* The INTERFACE_CLASS table is located after all interfaces */
        pTmp = &pTmp[currentInterfacesNum + 2u];
        pInterfaceClass = (const uint8 CYCODE *) pTmp->p_list;
    }
    else
    {
        pInterfaceClass = (const uint8 CYCODE *) NULL;
    }

    return( pInterfaceClass );
}


/*******************************************************************************
* Function Name: UART_TerminateEP
********************************************************************************
*
* Summary:
*  This function terminates the specified USBFS endpoint.
*  This function should be used before endpoint reconfiguration.
*
* Parameters:
*  Endpoint number.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_TerminateEP(uint8 ep) 
{
    uint8 ri;

    ep &= UART_DIR_UNUSED;
    ri = ((ep - UART_EP1) << UART_EPX_CNTX_ADDR_SHIFT);

    if ((ep > UART_EP0) && (ep < UART_MAX_EP))
    {
        /* Set the endpoint Halt */
        UART_EP[ep].hwEpState |= (UART_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        UART_EP[ep].epToggle = 0u;
        UART_EP[ep].apiEpState = UART_NO_EVENT_ALLOWED;

        if ((UART_EP[ep].addr & UART_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            CY_SET_REG8((reg8 *)(UART_SIE_EP1_CR0_IND + ri), UART_MODE_NAK_IN);
        }
        else
        {
            /* OUT Endpoint */
            CY_SET_REG8((reg8 *)(UART_SIE_EP1_CR0_IND + ri), UART_MODE_NAK_OUT);
        }
    }
}


/*******************************************************************************
* Function Name: UART_SetEndpointHalt
********************************************************************************
*
* Summary:
*  This routine handles set endpoint halt.
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
uint8 UART_SetEndpointHalt(void) 
{
    uint8 ep;
    uint8 ri;
    uint8 requestHandled = UART_FALSE;

    /* Set endpoint halt */
    ep = CY_GET_REG8(UART_wIndexLo) & UART_DIR_UNUSED;
    ri = ((ep - UART_EP1) << UART_EPX_CNTX_ADDR_SHIFT);

    if ((ep > UART_EP0) && (ep < UART_MAX_EP))
    {
        /* Set the endpoint Halt */
        UART_EP[ep].hwEpState |= (UART_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        UART_EP[ep].epToggle = 0u;
        UART_EP[ep].apiEpState |= UART_NO_EVENT_ALLOWED;

        if ((UART_EP[ep].addr & UART_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            CY_SET_REG8((reg8 *)(UART_SIE_EP1_CR0_IND + ri), UART_MODE_STALL_DATA_EP |
                                                               UART_MODE_ACK_IN);
        }
        else
        {
            /* OUT Endpoint */
            CY_SET_REG8((reg8 *)(UART_SIE_EP1_CR0_IND + ri), UART_MODE_STALL_DATA_EP |
                                                               UART_MODE_ACK_OUT);
        }
        requestHandled = UART_InitNoDataControlTransfer();
    }

    return(requestHandled);
}


/*******************************************************************************
* Function Name: UART_ClearEndpointHalt
********************************************************************************
*
* Summary:
*  This routine handles clear endpoint halt.
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
uint8 UART_ClearEndpointHalt(void) 
{
    uint8 ep;
    uint8 ri;
    uint8 requestHandled = UART_FALSE;

    /* Clear endpoint halt */
    ep = CY_GET_REG8(UART_wIndexLo) & UART_DIR_UNUSED;
    ri = ((ep - UART_EP1) << UART_EPX_CNTX_ADDR_SHIFT);

    if ((ep > UART_EP0) && (ep < UART_MAX_EP))
    {
        /* Clear the endpoint Halt */
        UART_EP[ep].hwEpState &= (uint8)~(UART_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        UART_EP[ep].epToggle = 0u;
        /* Clear toggle bit for already armed packet */
        CY_SET_REG8((reg8 *)(UART_SIE_EP1_CNT0_IND + ri), CY_GET_REG8(
                    (reg8 *)(UART_SIE_EP1_CNT0_IND + ri)) & (uint8)~UART_EPX_CNT_DATA_TOGGLE);
        /* Return API State as it was defined before */
        UART_EP[ep].apiEpState &= (uint8)~UART_NO_EVENT_ALLOWED;

        if ((UART_EP[ep].addr & UART_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            if(UART_EP[ep].apiEpState == UART_IN_BUFFER_EMPTY)
            {       /* Wait for next packet from application */
                CY_SET_REG8((reg8 *)(UART_SIE_EP1_CR0_IND + ri), UART_MODE_NAK_IN);
            }
            else    /* Continue armed transfer */
            {
                CY_SET_REG8((reg8 *)(UART_SIE_EP1_CR0_IND + ri), UART_MODE_ACK_IN);
            }
        }
        else
        {
            /* OUT Endpoint */
            if(UART_EP[ep].apiEpState == UART_OUT_BUFFER_FULL)
            {       /* Allow application to read full buffer */
                CY_SET_REG8((reg8 *)(UART_SIE_EP1_CR0_IND + ri), UART_MODE_NAK_OUT);
            }
            else    /* Mark endpoint as empty, so it will be reloaded */
            {
                CY_SET_REG8((reg8 *)(UART_SIE_EP1_CR0_IND + ri), UART_MODE_ACK_OUT);
            }
        }
        requestHandled = UART_InitNoDataControlTransfer();
    }

    return(requestHandled);
}


/*******************************************************************************
* Function Name: UART_ValidateAlternateSetting
********************************************************************************
*
* Summary:
*  Validates (and records) a SET INTERFACE request.
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
uint8 UART_ValidateAlternateSetting(void) 
{
    uint8 requestHandled = UART_TRUE;
    uint8 interfaceNum;
    const T_UART_LUT CYCODE *pTmp;
    uint8 currentInterfacesNum;

    interfaceNum = CY_GET_REG8(UART_wIndexLo);
    /* Validate interface setting, stall if invalid. */
    pTmp = UART_GetConfigTablePtr(UART_configuration - 1u);
    currentInterfacesNum  = ((const uint8 *) pTmp->p_list)[UART_CONFIG_DESCR_NUM_INTERFACES];

    if((interfaceNum >= currentInterfacesNum) || (interfaceNum >= UART_MAX_INTERFACES_NUMBER))
    {   /* Wrong interface number */
        requestHandled = UART_FALSE;
    }
    else
    {
        /* Save current Alt setting to find out the difference in Config() function */
        UART_interfaceSetting_last[interfaceNum] = UART_interfaceSetting[interfaceNum];
        UART_interfaceSetting[interfaceNum] = CY_GET_REG8(UART_wValueLo);
    }

    return (requestHandled);
}


/* [] END OF FILE */
