/*******************************************************************************
* File Name: ADC_TURBIDO_PM.c
* Version 2.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_TURBIDO.h"


/***************************************
* Local data allocation
***************************************/

static ADC_TURBIDO_BACKUP_STRUCT  ADC_TURBIDO_backup =
{
    ADC_TURBIDO_DISABLED
};


/*******************************************************************************
* Function Name: ADC_TURBIDO_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_TURBIDO_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_TURBIDO_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_TURBIDO_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_TURBIDO_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The ADC_TURBIDO_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_TURBIDO_backup - modified.
*
*******************************************************************************/
void ADC_TURBIDO_Sleep(void)
{
    if((ADC_TURBIDO_PWRMGR_SAR_REG  & ADC_TURBIDO_ACT_PWR_SAR_EN) != 0u)
    {
        if((ADC_TURBIDO_SAR_CSR0_REG & ADC_TURBIDO_SAR_SOF_START_CONV) != 0u)
        {
            ADC_TURBIDO_backup.enableState = ADC_TURBIDO_ENABLED | ADC_TURBIDO_STARTED;
        }
        else
        {
            ADC_TURBIDO_backup.enableState = ADC_TURBIDO_ENABLED;
        }
        ADC_TURBIDO_Stop();
    }
    else
    {
        ADC_TURBIDO_backup.enableState = ADC_TURBIDO_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_TURBIDO_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  ADC_TURBIDO_Sleep() was called. If the component was enabled before the
*  ADC_TURBIDO_Sleep() function was called, the
*  ADC_TURBIDO_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_TURBIDO_backup - used to check enabable state.
*
*******************************************************************************/
void ADC_TURBIDO_Wakeup(void)
{
    if(ADC_TURBIDO_backup.enableState != ADC_TURBIDO_DISABLED)
    {
        ADC_TURBIDO_Enable();
        #if(ADC_TURBIDO_DEFAULT_CONV_MODE != ADC_TURBIDO__HARDWARE_TRIGGER)
            if((ADC_TURBIDO_backup.enableState & ADC_TURBIDO_STARTED) != 0u)
            {
                ADC_TURBIDO_StartConvert();
            }
        #endif /* End ADC_TURBIDO_DEFAULT_CONV_MODE != ADC_TURBIDO__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
