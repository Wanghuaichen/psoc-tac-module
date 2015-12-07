/*******************************************************************************
* File Name: peltierPWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "peltierPWM.h"

static peltierPWM_backupStruct peltierPWM_backup;


/*******************************************************************************
* Function Name: peltierPWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  peltierPWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void peltierPWM_SaveConfig(void) 
{

    #if(!peltierPWM_UsingFixedFunction)
        #if(!peltierPWM_PWMModeIsCenterAligned)
            peltierPWM_backup.PWMPeriod = peltierPWM_ReadPeriod();
        #endif /* (!peltierPWM_PWMModeIsCenterAligned) */
        peltierPWM_backup.PWMUdb = peltierPWM_ReadCounter();
        #if (peltierPWM_UseStatus)
            peltierPWM_backup.InterruptMaskValue = peltierPWM_STATUS_MASK;
        #endif /* (peltierPWM_UseStatus) */

        #if(peltierPWM_DeadBandMode == peltierPWM__B_PWM__DBM_256_CLOCKS || \
            peltierPWM_DeadBandMode == peltierPWM__B_PWM__DBM_2_4_CLOCKS)
            peltierPWM_backup.PWMdeadBandValue = peltierPWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(peltierPWM_KillModeMinTime)
             peltierPWM_backup.PWMKillCounterPeriod = peltierPWM_ReadKillTime();
        #endif /* (peltierPWM_KillModeMinTime) */

        #if(peltierPWM_UseControl)
            peltierPWM_backup.PWMControlRegister = peltierPWM_ReadControlRegister();
        #endif /* (peltierPWM_UseControl) */
    #endif  /* (!peltierPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: peltierPWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  peltierPWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void peltierPWM_RestoreConfig(void) 
{
        #if(!peltierPWM_UsingFixedFunction)
            #if(!peltierPWM_PWMModeIsCenterAligned)
                peltierPWM_WritePeriod(peltierPWM_backup.PWMPeriod);
            #endif /* (!peltierPWM_PWMModeIsCenterAligned) */

            peltierPWM_WriteCounter(peltierPWM_backup.PWMUdb);

            #if (peltierPWM_UseStatus)
                peltierPWM_STATUS_MASK = peltierPWM_backup.InterruptMaskValue;
            #endif /* (peltierPWM_UseStatus) */

            #if(peltierPWM_DeadBandMode == peltierPWM__B_PWM__DBM_256_CLOCKS || \
                peltierPWM_DeadBandMode == peltierPWM__B_PWM__DBM_2_4_CLOCKS)
                peltierPWM_WriteDeadTime(peltierPWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(peltierPWM_KillModeMinTime)
                peltierPWM_WriteKillTime(peltierPWM_backup.PWMKillCounterPeriod);
            #endif /* (peltierPWM_KillModeMinTime) */

            #if(peltierPWM_UseControl)
                peltierPWM_WriteControlRegister(peltierPWM_backup.PWMControlRegister);
            #endif /* (peltierPWM_UseControl) */
        #endif  /* (!peltierPWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: peltierPWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  peltierPWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void peltierPWM_Sleep(void) 
{
    #if(peltierPWM_UseControl)
        if(peltierPWM_CTRL_ENABLE == (peltierPWM_CONTROL & peltierPWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            peltierPWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            peltierPWM_backup.PWMEnableState = 0u;
        }
    #endif /* (peltierPWM_UseControl) */

    /* Stop component */
    peltierPWM_Stop();

    /* Save registers configuration */
    peltierPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: peltierPWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  peltierPWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void peltierPWM_Wakeup(void) 
{
     /* Restore registers values */
    peltierPWM_RestoreConfig();

    if(peltierPWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        peltierPWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
