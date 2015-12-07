/*******************************************************************************
* File Name: pwmFan_PM.c
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

#include "pwmFan.h"

static pwmFan_backupStruct pwmFan_backup;


/*******************************************************************************
* Function Name: pwmFan_SaveConfig
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
*  pwmFan_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void pwmFan_SaveConfig(void) 
{

    #if(!pwmFan_UsingFixedFunction)
        #if(!pwmFan_PWMModeIsCenterAligned)
            pwmFan_backup.PWMPeriod = pwmFan_ReadPeriod();
        #endif /* (!pwmFan_PWMModeIsCenterAligned) */
        pwmFan_backup.PWMUdb = pwmFan_ReadCounter();
        #if (pwmFan_UseStatus)
            pwmFan_backup.InterruptMaskValue = pwmFan_STATUS_MASK;
        #endif /* (pwmFan_UseStatus) */

        #if(pwmFan_DeadBandMode == pwmFan__B_PWM__DBM_256_CLOCKS || \
            pwmFan_DeadBandMode == pwmFan__B_PWM__DBM_2_4_CLOCKS)
            pwmFan_backup.PWMdeadBandValue = pwmFan_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(pwmFan_KillModeMinTime)
             pwmFan_backup.PWMKillCounterPeriod = pwmFan_ReadKillTime();
        #endif /* (pwmFan_KillModeMinTime) */

        #if(pwmFan_UseControl)
            pwmFan_backup.PWMControlRegister = pwmFan_ReadControlRegister();
        #endif /* (pwmFan_UseControl) */
    #endif  /* (!pwmFan_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwmFan_RestoreConfig
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
*  pwmFan_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void pwmFan_RestoreConfig(void) 
{
        #if(!pwmFan_UsingFixedFunction)
            #if(!pwmFan_PWMModeIsCenterAligned)
                pwmFan_WritePeriod(pwmFan_backup.PWMPeriod);
            #endif /* (!pwmFan_PWMModeIsCenterAligned) */

            pwmFan_WriteCounter(pwmFan_backup.PWMUdb);

            #if (pwmFan_UseStatus)
                pwmFan_STATUS_MASK = pwmFan_backup.InterruptMaskValue;
            #endif /* (pwmFan_UseStatus) */

            #if(pwmFan_DeadBandMode == pwmFan__B_PWM__DBM_256_CLOCKS || \
                pwmFan_DeadBandMode == pwmFan__B_PWM__DBM_2_4_CLOCKS)
                pwmFan_WriteDeadTime(pwmFan_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(pwmFan_KillModeMinTime)
                pwmFan_WriteKillTime(pwmFan_backup.PWMKillCounterPeriod);
            #endif /* (pwmFan_KillModeMinTime) */

            #if(pwmFan_UseControl)
                pwmFan_WriteControlRegister(pwmFan_backup.PWMControlRegister);
            #endif /* (pwmFan_UseControl) */
        #endif  /* (!pwmFan_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: pwmFan_Sleep
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
*  pwmFan_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void pwmFan_Sleep(void) 
{
    #if(pwmFan_UseControl)
        if(pwmFan_CTRL_ENABLE == (pwmFan_CONTROL & pwmFan_CTRL_ENABLE))
        {
            /*Component is enabled */
            pwmFan_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            pwmFan_backup.PWMEnableState = 0u;
        }
    #endif /* (pwmFan_UseControl) */

    /* Stop component */
    pwmFan_Stop();

    /* Save registers configuration */
    pwmFan_SaveConfig();
}


/*******************************************************************************
* Function Name: pwmFan_Wakeup
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
*  pwmFan_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void pwmFan_Wakeup(void) 
{
     /* Restore registers values */
    pwmFan_RestoreConfig();

    if(pwmFan_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        pwmFan_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
