/*******************************************************************************
* File Name: pwmAgitator_2_PM.c
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

#include "pwmAgitator_2.h"

static pwmAgitator_2_backupStruct pwmAgitator_2_backup;


/*******************************************************************************
* Function Name: pwmAgitator_2_SaveConfig
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
*  pwmAgitator_2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void pwmAgitator_2_SaveConfig(void) 
{

    #if(!pwmAgitator_2_UsingFixedFunction)
        #if(!pwmAgitator_2_PWMModeIsCenterAligned)
            pwmAgitator_2_backup.PWMPeriod = pwmAgitator_2_ReadPeriod();
        #endif /* (!pwmAgitator_2_PWMModeIsCenterAligned) */
        pwmAgitator_2_backup.PWMUdb = pwmAgitator_2_ReadCounter();
        #if (pwmAgitator_2_UseStatus)
            pwmAgitator_2_backup.InterruptMaskValue = pwmAgitator_2_STATUS_MASK;
        #endif /* (pwmAgitator_2_UseStatus) */

        #if(pwmAgitator_2_DeadBandMode == pwmAgitator_2__B_PWM__DBM_256_CLOCKS || \
            pwmAgitator_2_DeadBandMode == pwmAgitator_2__B_PWM__DBM_2_4_CLOCKS)
            pwmAgitator_2_backup.PWMdeadBandValue = pwmAgitator_2_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(pwmAgitator_2_KillModeMinTime)
             pwmAgitator_2_backup.PWMKillCounterPeriod = pwmAgitator_2_ReadKillTime();
        #endif /* (pwmAgitator_2_KillModeMinTime) */

        #if(pwmAgitator_2_UseControl)
            pwmAgitator_2_backup.PWMControlRegister = pwmAgitator_2_ReadControlRegister();
        #endif /* (pwmAgitator_2_UseControl) */
    #endif  /* (!pwmAgitator_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwmAgitator_2_RestoreConfig
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
*  pwmAgitator_2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void pwmAgitator_2_RestoreConfig(void) 
{
        #if(!pwmAgitator_2_UsingFixedFunction)
            #if(!pwmAgitator_2_PWMModeIsCenterAligned)
                pwmAgitator_2_WritePeriod(pwmAgitator_2_backup.PWMPeriod);
            #endif /* (!pwmAgitator_2_PWMModeIsCenterAligned) */

            pwmAgitator_2_WriteCounter(pwmAgitator_2_backup.PWMUdb);

            #if (pwmAgitator_2_UseStatus)
                pwmAgitator_2_STATUS_MASK = pwmAgitator_2_backup.InterruptMaskValue;
            #endif /* (pwmAgitator_2_UseStatus) */

            #if(pwmAgitator_2_DeadBandMode == pwmAgitator_2__B_PWM__DBM_256_CLOCKS || \
                pwmAgitator_2_DeadBandMode == pwmAgitator_2__B_PWM__DBM_2_4_CLOCKS)
                pwmAgitator_2_WriteDeadTime(pwmAgitator_2_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(pwmAgitator_2_KillModeMinTime)
                pwmAgitator_2_WriteKillTime(pwmAgitator_2_backup.PWMKillCounterPeriod);
            #endif /* (pwmAgitator_2_KillModeMinTime) */

            #if(pwmAgitator_2_UseControl)
                pwmAgitator_2_WriteControlRegister(pwmAgitator_2_backup.PWMControlRegister);
            #endif /* (pwmAgitator_2_UseControl) */
        #endif  /* (!pwmAgitator_2_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: pwmAgitator_2_Sleep
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
*  pwmAgitator_2_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void pwmAgitator_2_Sleep(void) 
{
    #if(pwmAgitator_2_UseControl)
        if(pwmAgitator_2_CTRL_ENABLE == (pwmAgitator_2_CONTROL & pwmAgitator_2_CTRL_ENABLE))
        {
            /*Component is enabled */
            pwmAgitator_2_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            pwmAgitator_2_backup.PWMEnableState = 0u;
        }
    #endif /* (pwmAgitator_2_UseControl) */

    /* Stop component */
    pwmAgitator_2_Stop();

    /* Save registers configuration */
    pwmAgitator_2_SaveConfig();
}


/*******************************************************************************
* Function Name: pwmAgitator_2_Wakeup
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
*  pwmAgitator_2_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void pwmAgitator_2_Wakeup(void) 
{
     /* Restore registers values */
    pwmAgitator_2_RestoreConfig();

    if(pwmAgitator_2_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        pwmAgitator_2_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
