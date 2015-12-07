/*******************************************************************************
* File Name: UART_audio.c
* Version 2.80
*
* Description:
*  USB AUDIO Class request handler.
*
* Related Document:
*  Universal Serial Bus Device Class Definition for Audio Devices Release 1.0
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART.h"


#if defined(UART_ENABLE_AUDIO_CLASS)

#include "UART_audio.h"
#include "UART_pvt.h"
#if defined(UART_ENABLE_MIDI_STREAMING)
    #include "UART_midi.h"
#endif /*  UART_ENABLE_MIDI_STREAMING*/


/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if !defined(USER_SUPPLIED_AUDIO_HANDLER)


/***************************************
*    AUDIO Variables
***************************************/

#if defined(UART_ENABLE_AUDIO_STREAMING)
    volatile uint8 UART_currentSampleFrequency[UART_MAX_EP][UART_SAMPLE_FREQ_LEN];
    volatile uint8 UART_frequencyChanged;
    volatile uint8 UART_currentMute;
    volatile uint8 UART_currentVolume[UART_VOLUME_LEN];
    volatile uint8 UART_minimumVolume[UART_VOLUME_LEN] = {UART_VOL_MIN_LSB,
                                                                                  UART_VOL_MIN_MSB};
    volatile uint8 UART_maximumVolume[UART_VOLUME_LEN] = {UART_VOL_MAX_LSB,
                                                                                  UART_VOL_MAX_MSB};
    volatile uint8 UART_resolutionVolume[UART_VOLUME_LEN] = {UART_VOL_RES_LSB,
                                                                                     UART_VOL_RES_MSB};
#endif /*  UART_ENABLE_AUDIO_STREAMING */


/*******************************************************************************
* Function Name: UART_DispatchAUDIOClassRqst
********************************************************************************
*
* Summary:
*  This routine dispatches class requests
*
* Parameters:
*  None.
*
* Return:
*  requestHandled
*
* Global variables:
*   UART_currentSampleFrequency: Contains the current audio Sample
*       Frequency. It is set by the Host using SET_CUR request to the endpoint.
*   UART_frequencyChanged: This variable is used as a flag for the
*       user code, to be aware that Host has been sent request for changing
*       Sample Frequency. Sample frequency will be sent on the next OUT
*       transaction. It is contains endpoint address when set. The following
*       code is recommended for detecting new Sample Frequency in main code:
*       if((UART_frequencyChanged != 0) &&
*       (UART_transferState == UART_TRANS_STATE_IDLE))
*       {
*          UART_frequencyChanged = 0;
*       }
*       UART_transferState variable is checked to be sure that
*             transfer completes.
*   UART_currentMute: Contains mute configuration set by Host.
*   UART_currentVolume: Contains volume level set by Host.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 UART_DispatchAUDIOClassRqst(void) 
{
    uint8 requestHandled = UART_FALSE;
    uint8 bmRequestType  = CY_GET_REG8(UART_bmRequestType);

    #if defined(UART_ENABLE_AUDIO_STREAMING)
        uint8 epNumber;
        epNumber = CY_GET_REG8(UART_wIndexLo) & UART_DIR_UNUSED;
    #endif /*  UART_ENABLE_AUDIO_STREAMING */


    if ((bmRequestType & UART_RQST_DIR_MASK) == UART_RQST_DIR_D2H)
    {
        /* Control Read */
        if((bmRequestType & UART_RQST_RCPT_MASK) == UART_RQST_RCPT_EP)
        {
            /* Endpoint */
            switch (CY_GET_REG8(UART_bRequest))
            {
                case UART_GET_CUR:
                #if defined(UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(UART_wValueHi) == UART_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        UART_currentTD.wCount = UART_SAMPLE_FREQ_LEN;
                        UART_currentTD.pData  = UART_currentSampleFrequency[epNumber];
                        requestHandled   = UART_InitControlRead();
                    }
                #endif /*  UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_READ_REQUESTS` Place other request handler here */

                /* `#END` */
                
                #ifdef UART_DISPATCH_AUDIO_CLASS_AUDIO_READ_REQUESTS_CALLBACK
                    UART_DispatchAUDIOClass_AUDIO_READ_REQUESTS_Callback();
                #endif /* UART_DISPATCH_AUDIO_CLASS_AUDIO_READ_REQUESTS_CALLBACK */

                    break;
                default:
                    break;
            }
        }
        else if((bmRequestType & UART_RQST_RCPT_MASK) == UART_RQST_RCPT_IFC)
        {
            /* Interface or Entity ID */
            switch (CY_GET_REG8(UART_bRequest))
            {
                case UART_GET_CUR:
                #if defined(UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(UART_wValueHi) == UART_MUTE_CONTROL)
                    {
                        /* `#START MUTE_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        #ifdef UART_DISPATCH_AUDIO_CLASS_MUTE_CONTROL_GET_REQUEST_CALLBACK
                            UART_DispatchAUDIOClass_MUTE_CONTROL_GET_REQUEST_Callback();
                        #endif /* UART_DISPATCH_AUDIO_CLASS_MUTE_CONTROL_GET_REQUEST_CALLBACK */

                        /* Entity ID Control Selector is MUTE */
                        UART_currentTD.wCount = 1u;
                        UART_currentTD.pData  = &UART_currentMute;
                        requestHandled   = UART_InitControlRead();
                    }
                    else if(CY_GET_REG8(UART_wValueHi) == UART_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        #ifdef UART_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_GET_REQUEST_CALLBACK
                            UART_DispatchAUDIOClass_VOLUME_CONTROL_GET_REQUEST_Callback();
                        #endif /* UART_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_GET_REQUEST_CALLBACK */

                        /* Entity ID Control Selector is VOLUME, */
                        UART_currentTD.wCount = UART_VOLUME_LEN;
                        UART_currentTD.pData  = UART_currentVolume;
                        requestHandled   = UART_InitControlRead();
                    }
                    else
                    {
                        /* `#START OTHER_GET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */

                        #ifdef UART_DISPATCH_AUDIO_CLASS_OTHER_GET_CUR_REQUESTS_CALLBACK
                            UART_DispatchAUDIOClass_OTHER_GET_CUR_REQUESTS_Callback();
                        #endif /* UART_DISPATCH_AUDIO_CLASS_OTHER_GET_CUR_REQUESTS_CALLBACK */
                    }
                    break;
                case UART_GET_MIN:    /* GET_MIN */
                    if(CY_GET_REG8(UART_wValueHi) == UART_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        UART_currentTD.wCount = UART_VOLUME_LEN;
                        UART_currentTD.pData  = &UART_minimumVolume[0];
                        requestHandled   = UART_InitControlRead();
                    }
                    break;
                case UART_GET_MAX:    /* GET_MAX */
                    if(CY_GET_REG8(UART_wValueHi) == UART_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        UART_currentTD.wCount = UART_VOLUME_LEN;
                        UART_currentTD.pData  = &UART_maximumVolume[0];
                        requestHandled   = UART_InitControlRead();
                    }
                    break;
                case UART_GET_RES:    /* GET_RES */
                    if(CY_GET_REG8(UART_wValueHi) == UART_VOLUME_CONTROL)
                    {
                         /* Entity ID Control Selector is VOLUME, */
                        UART_currentTD.wCount = UART_VOLUME_LEN;
                        UART_currentTD.pData  = &UART_resolutionVolume[0];
                        requestHandled   = UART_InitControlRead();
                    }
                    break;
                /* The contents of the status message is reserved for future use.
                *  For the time being, a null packet should be returned in the data stage of the
                *  control transfer, and the received null packet should be ACKed.
                */
                case UART_GET_STAT:
                        UART_currentTD.wCount = 0u;
                        requestHandled   = UART_InitControlWrite();

                #endif /*  UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_WRITE_REQUESTS` Place other request handler here */

                /* `#END` */

                #ifdef UART_DISPATCH_AUDIO_CLASS_AUDIO_WRITE_REQUESTS_CALLBACK
                    UART_DispatchAUDIOClass_AUDIO_WRITE_REQUESTS_Callback();
                #endif /* UART_DISPATCH_AUDIO_CLASS_AUDIO_WRITE_REQUESTS_CALLBACK */

                    break;
                default:
                    break;
            }
        }
        else
        {   /* UART_RQST_RCPT_OTHER */
        }
    }
    else
    {
        /* Control Write */
        if((bmRequestType & UART_RQST_RCPT_MASK) == UART_RQST_RCPT_EP)
        {
            /* point */
            switch (CY_GET_REG8(UART_bRequest))
            {
                case UART_SET_CUR:
                #if defined(UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(UART_wValueHi) == UART_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        UART_currentTD.wCount = UART_SAMPLE_FREQ_LEN;
                        UART_currentTD.pData  = UART_currentSampleFrequency[epNumber];
                        requestHandled   = UART_InitControlWrite();
                        UART_frequencyChanged = epNumber;
                    }
                #endif /*  UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_SAMPLING_FREQ_REQUESTS` Place other request handler here */

                /* `#END` */

                #ifdef UART_DISPATCH_AUDIO_CLASS_AUDIO_SAMPLING_FREQ_REQUESTS_CALLBACK
                    UART_DispatchAUDIOClass_AUDIO_SAMPLING_FREQ_REQUESTS_Callback();
                #endif /* UART_DISPATCH_AUDIO_CLASS_AUDIO_SAMPLING_FREQ_REQUESTS_CALLBACK */

                    break;
                default:
                    break;
            }
        }
        else if((bmRequestType & UART_RQST_RCPT_MASK) == UART_RQST_RCPT_IFC)
        {
            /* Interface or Entity ID */
            switch (CY_GET_REG8(UART_bRequest))
            {
                case UART_SET_CUR:
                #if defined(UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(UART_wValueHi) == UART_MUTE_CONTROL)
                    {
                        /* `#START MUTE_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        #ifdef UART_DISPATCH_AUDIO_CLASS_MUTE_SET_REQUEST_CALLBACK
                            UART_DispatchAUDIOClass_MUTE_SET_REQUEST_Callback();
                        #endif /* UART_DISPATCH_AUDIO_CLASS_MUTE_SET_REQUEST_CALLBACK */

                        /* Entity ID Control Selector is MUTE */
                        UART_currentTD.wCount = 1u;
                        UART_currentTD.pData  = &UART_currentMute;
                        requestHandled   = UART_InitControlWrite();
                    }
                    else if(CY_GET_REG8(UART_wValueHi) == UART_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        #ifdef UART_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_SET_REQUEST_CALLBACK
                            UART_DispatchAUDIOClass_VOLUME_CONTROL_SET_REQUEST_Callback();
                        #endif /* UART_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_SET_REQUEST_CALLBACK */

                        /* Entity ID Control Selector is VOLUME */
                        UART_currentTD.wCount = UART_VOLUME_LEN;
                        UART_currentTD.pData  = UART_currentVolume;
                        requestHandled   = UART_InitControlWrite();
                    }
                    else
                    {
                        /* `#START OTHER_SET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */

                        #ifdef UART_DISPATCH_AUDIO_CLASS_OTHER_SET_CUR_REQUESTS_CALLBACK
                            UART_DispatchAUDIOClass_OTHER_SET_CUR_REQUESTS_Callback();
                        #endif /* UART_DISPATCH_AUDIO_CLASS_OTHER_SET_CUR_REQUESTS_CALLBACK */
                    }
                #endif /*  UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_CONTROL_SEL_REQUESTS` Place other request handler here */

                /* `#END` */

                #ifdef UART_DISPATCH_AUDIO_CLASS_AUDIO_CONTROL_SEL_REQUESTS_CALLBACK
                    UART_DispatchAUDIOClass_AUDIO_CONTROL_SEL_REQUESTS_Callback();
                #endif /* UART_DISPATCH_AUDIO_CLASS_AUDIO_CONTROL_SEL_REQUESTS_CALLBACK */

                    break;
                default:
                    break;
            }
        }
        else
        {
            /* UART_RQST_RCPT_OTHER */
        }
    }

    return(requestHandled);
}

#endif /* USER_SUPPLIED_AUDIO_HANDLER */


/*******************************************************************************
* Additional user functions supporting AUDIO Requests
********************************************************************************/

/* `#START AUDIO_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /*  UART_ENABLE_AUDIO_CLASS */


/* [] END OF FILE */
