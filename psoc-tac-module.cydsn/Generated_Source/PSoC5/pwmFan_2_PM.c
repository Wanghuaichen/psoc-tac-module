/*******************************************************************************
* File Name: pwmFan_2_PM.c
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

#include "pwmFan_2.h"

static pwmFan_2_backupStruct pwmFan_2_backup;


/*******************************************************************************
* Function Name: pwmFan_2_SaveConfig
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
*  pwmFan_2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void pwmFan_2_SaveConfig(void) 
{

    #if(!pwmFan_2_UsingFixedFunction)
        #if(!pwmFan_2_PWMModeIsCenterAligned)
            pwmFan_2_backup.PWMPeriod = pwmFan_2_ReadPeriod();
        #endif /* (!pwmFan_2_PWMModeIsCenterAligned) */
        pwmFan_2_backup.PWMUdb = pwmFan_2_ReadCounter();
        #if (pwmFan_2_UseStatus)
            pwmFan_2_backup.InterruptMaskValue = pwmFan_2_STATUS_MASK;
        #endif /* (pwmFan_2_UseStatus) */

        #if(pwmFan_2_DeadBandMode == pwmFan_2__B_PWM__DBM_256_CLOCKS || \
            pwmFan_2_DeadBandMode == pwmFan_2__B_PWM__DBM_2_4_CLOCKS)
            pwmFan_2_backup.PWMdeadBandValue = pwmFan_2_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(pwmFan_2_KillModeMinTime)
             pwmFan_2_backup.PWMKillCounterPeriod = pwmFan_2_ReadKillTime();
        #endif /* (pwmFan_2_KillModeMinTime) */

        #if(pwmFan_2_UseControl)
            pwmFan_2_backup.PWMControlRegister = pwmFan_2_ReadControlRegister();
        #endif /* (pwmFan_2_UseControl) */
    #endif  /* (!pwmFan_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwmFan_2_RestoreConfig
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
*  pwmFan_2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void pwmFan_2_RestoreConfig(void) 
{
        #if(!pwmFan_2_UsingFixedFunction)
            #if(!pwmFan_2_PWMModeIsCenterAligned)
                pwmFan_2_WritePeriod(pwmFan_2_backup.PWMPeriod);
            #endif /* (!pwmFan_2_PWMModeIsCenterAligned) */

            pwmFan_2_WriteCounter(pwmFan_2_backup.PWMUdb);

            #if (pwmFan_2_UseStatus)
                pwmFan_2_STATUS_MASK = pwmFan_2_backup.InterruptMaskValue;
            #endif /* (pwmFan_2_UseStatus) */

            #if(pwmFan_2_DeadBandMode == pwmFan_2__B_PWM__DBM_256_CLOCKS || \
                pwmFan_2_DeadBandMode == pwmFan_2__B_PWM__DBM_2_4_CLOCKS)
                pwmFan_2_WriteDeadTime(pwmFan_2_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(pwmFan_2_KillModeMinTime)
                pwmFan_2_WriteKillTime(pwmFan_2_backup.PWMKillCounterPeriod);
            #endif /* (pwmFan_2_KillModeMinTime) */

            #if(pwmFan_2_UseControl)
                pwmFan_2_WriteControlRegister(pwmFan_2_backup.PWMControlRegister);
            #endif /* (pwmFan_2_UseControl) */
        #endif  /* (!pwmFan_2_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: pwmFan_2_Sleep
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
*  pwmFan_2_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void pwmFan_2_Sleep(void) 
{
    #if(pwmFan_2_UseControl)
        if(pwmFan_2_CTRL_ENABLE == (pwmFan_2_CONTROL & pwmFan_2_CTRL_ENABLE))
        {
            /*Component is enabled */
            pwmFan_2_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            pwmFan_2_backup.PWMEnableState = 0u;
        }
    #endif /* (pwmFan_2_UseControl) */

    /* Stop component */
    pwmFan_2_Stop();

    /* Save registers configuration */
    pwmFan_2_SaveConfig();
}


/*******************************************************************************
* Function Name: pwmFan_2_Wakeup
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
*  pwmFan_2_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void pwmFan_2_Wakeup(void) 
{
     /* Restore registers values */
    pwmFan_2_RestoreConfig();

    if(pwmFan_2_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        pwmFan_2_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
