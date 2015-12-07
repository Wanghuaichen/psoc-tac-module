/*******************************************************************************
* File Name: pwmAgitator_1_PM.c
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

#include "pwmAgitator_1.h"

static pwmAgitator_1_backupStruct pwmAgitator_1_backup;


/*******************************************************************************
* Function Name: pwmAgitator_1_SaveConfig
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
*  pwmAgitator_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void pwmAgitator_1_SaveConfig(void) 
{

    #if(!pwmAgitator_1_UsingFixedFunction)
        #if(!pwmAgitator_1_PWMModeIsCenterAligned)
            pwmAgitator_1_backup.PWMPeriod = pwmAgitator_1_ReadPeriod();
        #endif /* (!pwmAgitator_1_PWMModeIsCenterAligned) */
        pwmAgitator_1_backup.PWMUdb = pwmAgitator_1_ReadCounter();
        #if (pwmAgitator_1_UseStatus)
            pwmAgitator_1_backup.InterruptMaskValue = pwmAgitator_1_STATUS_MASK;
        #endif /* (pwmAgitator_1_UseStatus) */

        #if(pwmAgitator_1_DeadBandMode == pwmAgitator_1__B_PWM__DBM_256_CLOCKS || \
            pwmAgitator_1_DeadBandMode == pwmAgitator_1__B_PWM__DBM_2_4_CLOCKS)
            pwmAgitator_1_backup.PWMdeadBandValue = pwmAgitator_1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(pwmAgitator_1_KillModeMinTime)
             pwmAgitator_1_backup.PWMKillCounterPeriod = pwmAgitator_1_ReadKillTime();
        #endif /* (pwmAgitator_1_KillModeMinTime) */

        #if(pwmAgitator_1_UseControl)
            pwmAgitator_1_backup.PWMControlRegister = pwmAgitator_1_ReadControlRegister();
        #endif /* (pwmAgitator_1_UseControl) */
    #endif  /* (!pwmAgitator_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwmAgitator_1_RestoreConfig
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
*  pwmAgitator_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void pwmAgitator_1_RestoreConfig(void) 
{
        #if(!pwmAgitator_1_UsingFixedFunction)
            #if(!pwmAgitator_1_PWMModeIsCenterAligned)
                pwmAgitator_1_WritePeriod(pwmAgitator_1_backup.PWMPeriod);
            #endif /* (!pwmAgitator_1_PWMModeIsCenterAligned) */

            pwmAgitator_1_WriteCounter(pwmAgitator_1_backup.PWMUdb);

            #if (pwmAgitator_1_UseStatus)
                pwmAgitator_1_STATUS_MASK = pwmAgitator_1_backup.InterruptMaskValue;
            #endif /* (pwmAgitator_1_UseStatus) */

            #if(pwmAgitator_1_DeadBandMode == pwmAgitator_1__B_PWM__DBM_256_CLOCKS || \
                pwmAgitator_1_DeadBandMode == pwmAgitator_1__B_PWM__DBM_2_4_CLOCKS)
                pwmAgitator_1_WriteDeadTime(pwmAgitator_1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(pwmAgitator_1_KillModeMinTime)
                pwmAgitator_1_WriteKillTime(pwmAgitator_1_backup.PWMKillCounterPeriod);
            #endif /* (pwmAgitator_1_KillModeMinTime) */

            #if(pwmAgitator_1_UseControl)
                pwmAgitator_1_WriteControlRegister(pwmAgitator_1_backup.PWMControlRegister);
            #endif /* (pwmAgitator_1_UseControl) */
        #endif  /* (!pwmAgitator_1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: pwmAgitator_1_Sleep
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
*  pwmAgitator_1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void pwmAgitator_1_Sleep(void) 
{
    #if(pwmAgitator_1_UseControl)
        if(pwmAgitator_1_CTRL_ENABLE == (pwmAgitator_1_CONTROL & pwmAgitator_1_CTRL_ENABLE))
        {
            /*Component is enabled */
            pwmAgitator_1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            pwmAgitator_1_backup.PWMEnableState = 0u;
        }
    #endif /* (pwmAgitator_1_UseControl) */

    /* Stop component */
    pwmAgitator_1_Stop();

    /* Save registers configuration */
    pwmAgitator_1_SaveConfig();
}


/*******************************************************************************
* Function Name: pwmAgitator_1_Wakeup
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
*  pwmAgitator_1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void pwmAgitator_1_Wakeup(void) 
{
     /* Restore registers values */
    pwmAgitator_1_RestoreConfig();

    if(pwmAgitator_1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        pwmAgitator_1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
