/*******************************************************************************
* File Name: pwmAgitator_PM.c
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

#include "pwmAgitator.h"

static pwmAgitator_backupStruct pwmAgitator_backup;


/*******************************************************************************
* Function Name: pwmAgitator_SaveConfig
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
*  pwmAgitator_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void pwmAgitator_SaveConfig(void) 
{

    #if(!pwmAgitator_UsingFixedFunction)
        #if(!pwmAgitator_PWMModeIsCenterAligned)
            pwmAgitator_backup.PWMPeriod = pwmAgitator_ReadPeriod();
        #endif /* (!pwmAgitator_PWMModeIsCenterAligned) */
        pwmAgitator_backup.PWMUdb = pwmAgitator_ReadCounter();
        #if (pwmAgitator_UseStatus)
            pwmAgitator_backup.InterruptMaskValue = pwmAgitator_STATUS_MASK;
        #endif /* (pwmAgitator_UseStatus) */

        #if(pwmAgitator_DeadBandMode == pwmAgitator__B_PWM__DBM_256_CLOCKS || \
            pwmAgitator_DeadBandMode == pwmAgitator__B_PWM__DBM_2_4_CLOCKS)
            pwmAgitator_backup.PWMdeadBandValue = pwmAgitator_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(pwmAgitator_KillModeMinTime)
             pwmAgitator_backup.PWMKillCounterPeriod = pwmAgitator_ReadKillTime();
        #endif /* (pwmAgitator_KillModeMinTime) */

        #if(pwmAgitator_UseControl)
            pwmAgitator_backup.PWMControlRegister = pwmAgitator_ReadControlRegister();
        #endif /* (pwmAgitator_UseControl) */
    #endif  /* (!pwmAgitator_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwmAgitator_RestoreConfig
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
*  pwmAgitator_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void pwmAgitator_RestoreConfig(void) 
{
        #if(!pwmAgitator_UsingFixedFunction)
            #if(!pwmAgitator_PWMModeIsCenterAligned)
                pwmAgitator_WritePeriod(pwmAgitator_backup.PWMPeriod);
            #endif /* (!pwmAgitator_PWMModeIsCenterAligned) */

            pwmAgitator_WriteCounter(pwmAgitator_backup.PWMUdb);

            #if (pwmAgitator_UseStatus)
                pwmAgitator_STATUS_MASK = pwmAgitator_backup.InterruptMaskValue;
            #endif /* (pwmAgitator_UseStatus) */

            #if(pwmAgitator_DeadBandMode == pwmAgitator__B_PWM__DBM_256_CLOCKS || \
                pwmAgitator_DeadBandMode == pwmAgitator__B_PWM__DBM_2_4_CLOCKS)
                pwmAgitator_WriteDeadTime(pwmAgitator_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(pwmAgitator_KillModeMinTime)
                pwmAgitator_WriteKillTime(pwmAgitator_backup.PWMKillCounterPeriod);
            #endif /* (pwmAgitator_KillModeMinTime) */

            #if(pwmAgitator_UseControl)
                pwmAgitator_WriteControlRegister(pwmAgitator_backup.PWMControlRegister);
            #endif /* (pwmAgitator_UseControl) */
        #endif  /* (!pwmAgitator_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: pwmAgitator_Sleep
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
*  pwmAgitator_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void pwmAgitator_Sleep(void) 
{
    #if(pwmAgitator_UseControl)
        if(pwmAgitator_CTRL_ENABLE == (pwmAgitator_CONTROL & pwmAgitator_CTRL_ENABLE))
        {
            /*Component is enabled */
            pwmAgitator_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            pwmAgitator_backup.PWMEnableState = 0u;
        }
    #endif /* (pwmAgitator_UseControl) */

    /* Stop component */
    pwmAgitator_Stop();

    /* Save registers configuration */
    pwmAgitator_SaveConfig();
}


/*******************************************************************************
* Function Name: pwmAgitator_Wakeup
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
*  pwmAgitator_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void pwmAgitator_Wakeup(void) 
{
     /* Restore registers values */
    pwmAgitator_RestoreConfig();

    if(pwmAgitator_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        pwmAgitator_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
