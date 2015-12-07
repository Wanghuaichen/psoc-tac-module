/*******************************************************************************
* File Name: pwmFan_1_PM.c
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

#include "pwmFan_1.h"

static pwmFan_1_backupStruct pwmFan_1_backup;


/*******************************************************************************
* Function Name: pwmFan_1_SaveConfig
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
*  pwmFan_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void pwmFan_1_SaveConfig(void) 
{

    #if(!pwmFan_1_UsingFixedFunction)
        #if(!pwmFan_1_PWMModeIsCenterAligned)
            pwmFan_1_backup.PWMPeriod = pwmFan_1_ReadPeriod();
        #endif /* (!pwmFan_1_PWMModeIsCenterAligned) */
        pwmFan_1_backup.PWMUdb = pwmFan_1_ReadCounter();
        #if (pwmFan_1_UseStatus)
            pwmFan_1_backup.InterruptMaskValue = pwmFan_1_STATUS_MASK;
        #endif /* (pwmFan_1_UseStatus) */

        #if(pwmFan_1_DeadBandMode == pwmFan_1__B_PWM__DBM_256_CLOCKS || \
            pwmFan_1_DeadBandMode == pwmFan_1__B_PWM__DBM_2_4_CLOCKS)
            pwmFan_1_backup.PWMdeadBandValue = pwmFan_1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(pwmFan_1_KillModeMinTime)
             pwmFan_1_backup.PWMKillCounterPeriod = pwmFan_1_ReadKillTime();
        #endif /* (pwmFan_1_KillModeMinTime) */

        #if(pwmFan_1_UseControl)
            pwmFan_1_backup.PWMControlRegister = pwmFan_1_ReadControlRegister();
        #endif /* (pwmFan_1_UseControl) */
    #endif  /* (!pwmFan_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwmFan_1_RestoreConfig
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
*  pwmFan_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void pwmFan_1_RestoreConfig(void) 
{
        #if(!pwmFan_1_UsingFixedFunction)
            #if(!pwmFan_1_PWMModeIsCenterAligned)
                pwmFan_1_WritePeriod(pwmFan_1_backup.PWMPeriod);
            #endif /* (!pwmFan_1_PWMModeIsCenterAligned) */

            pwmFan_1_WriteCounter(pwmFan_1_backup.PWMUdb);

            #if (pwmFan_1_UseStatus)
                pwmFan_1_STATUS_MASK = pwmFan_1_backup.InterruptMaskValue;
            #endif /* (pwmFan_1_UseStatus) */

            #if(pwmFan_1_DeadBandMode == pwmFan_1__B_PWM__DBM_256_CLOCKS || \
                pwmFan_1_DeadBandMode == pwmFan_1__B_PWM__DBM_2_4_CLOCKS)
                pwmFan_1_WriteDeadTime(pwmFan_1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(pwmFan_1_KillModeMinTime)
                pwmFan_1_WriteKillTime(pwmFan_1_backup.PWMKillCounterPeriod);
            #endif /* (pwmFan_1_KillModeMinTime) */

            #if(pwmFan_1_UseControl)
                pwmFan_1_WriteControlRegister(pwmFan_1_backup.PWMControlRegister);
            #endif /* (pwmFan_1_UseControl) */
        #endif  /* (!pwmFan_1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: pwmFan_1_Sleep
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
*  pwmFan_1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void pwmFan_1_Sleep(void) 
{
    #if(pwmFan_1_UseControl)
        if(pwmFan_1_CTRL_ENABLE == (pwmFan_1_CONTROL & pwmFan_1_CTRL_ENABLE))
        {
            /*Component is enabled */
            pwmFan_1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            pwmFan_1_backup.PWMEnableState = 0u;
        }
    #endif /* (pwmFan_1_UseControl) */

    /* Stop component */
    pwmFan_1_Stop();

    /* Save registers configuration */
    pwmFan_1_SaveConfig();
}


/*******************************************************************************
* Function Name: pwmFan_1_Wakeup
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
*  pwmFan_1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void pwmFan_1_Wakeup(void) 
{
     /* Restore registers values */
    pwmFan_1_RestoreConfig();

    if(pwmFan_1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        pwmFan_1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
