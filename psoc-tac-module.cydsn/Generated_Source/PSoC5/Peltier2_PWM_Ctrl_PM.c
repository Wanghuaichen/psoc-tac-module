/*******************************************************************************
* File Name: Peltier2_PWM_Ctrl_PM.c
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

#include "Peltier2_PWM_Ctrl.h"

static Peltier2_PWM_Ctrl_backupStruct Peltier2_PWM_Ctrl_backup;


/*******************************************************************************
* Function Name: Peltier2_PWM_Ctrl_SaveConfig
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
*  Peltier2_PWM_Ctrl_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Peltier2_PWM_Ctrl_SaveConfig(void) 
{

    #if(!Peltier2_PWM_Ctrl_UsingFixedFunction)
        #if(!Peltier2_PWM_Ctrl_PWMModeIsCenterAligned)
            Peltier2_PWM_Ctrl_backup.PWMPeriod = Peltier2_PWM_Ctrl_ReadPeriod();
        #endif /* (!Peltier2_PWM_Ctrl_PWMModeIsCenterAligned) */
        Peltier2_PWM_Ctrl_backup.PWMUdb = Peltier2_PWM_Ctrl_ReadCounter();
        #if (Peltier2_PWM_Ctrl_UseStatus)
            Peltier2_PWM_Ctrl_backup.InterruptMaskValue = Peltier2_PWM_Ctrl_STATUS_MASK;
        #endif /* (Peltier2_PWM_Ctrl_UseStatus) */

        #if(Peltier2_PWM_Ctrl_DeadBandMode == Peltier2_PWM_Ctrl__B_PWM__DBM_256_CLOCKS || \
            Peltier2_PWM_Ctrl_DeadBandMode == Peltier2_PWM_Ctrl__B_PWM__DBM_2_4_CLOCKS)
            Peltier2_PWM_Ctrl_backup.PWMdeadBandValue = Peltier2_PWM_Ctrl_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Peltier2_PWM_Ctrl_KillModeMinTime)
             Peltier2_PWM_Ctrl_backup.PWMKillCounterPeriod = Peltier2_PWM_Ctrl_ReadKillTime();
        #endif /* (Peltier2_PWM_Ctrl_KillModeMinTime) */

        #if(Peltier2_PWM_Ctrl_UseControl)
            Peltier2_PWM_Ctrl_backup.PWMControlRegister = Peltier2_PWM_Ctrl_ReadControlRegister();
        #endif /* (Peltier2_PWM_Ctrl_UseControl) */
    #endif  /* (!Peltier2_PWM_Ctrl_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Peltier2_PWM_Ctrl_RestoreConfig
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
*  Peltier2_PWM_Ctrl_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Peltier2_PWM_Ctrl_RestoreConfig(void) 
{
        #if(!Peltier2_PWM_Ctrl_UsingFixedFunction)
            #if(!Peltier2_PWM_Ctrl_PWMModeIsCenterAligned)
                Peltier2_PWM_Ctrl_WritePeriod(Peltier2_PWM_Ctrl_backup.PWMPeriod);
            #endif /* (!Peltier2_PWM_Ctrl_PWMModeIsCenterAligned) */

            Peltier2_PWM_Ctrl_WriteCounter(Peltier2_PWM_Ctrl_backup.PWMUdb);

            #if (Peltier2_PWM_Ctrl_UseStatus)
                Peltier2_PWM_Ctrl_STATUS_MASK = Peltier2_PWM_Ctrl_backup.InterruptMaskValue;
            #endif /* (Peltier2_PWM_Ctrl_UseStatus) */

            #if(Peltier2_PWM_Ctrl_DeadBandMode == Peltier2_PWM_Ctrl__B_PWM__DBM_256_CLOCKS || \
                Peltier2_PWM_Ctrl_DeadBandMode == Peltier2_PWM_Ctrl__B_PWM__DBM_2_4_CLOCKS)
                Peltier2_PWM_Ctrl_WriteDeadTime(Peltier2_PWM_Ctrl_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Peltier2_PWM_Ctrl_KillModeMinTime)
                Peltier2_PWM_Ctrl_WriteKillTime(Peltier2_PWM_Ctrl_backup.PWMKillCounterPeriod);
            #endif /* (Peltier2_PWM_Ctrl_KillModeMinTime) */

            #if(Peltier2_PWM_Ctrl_UseControl)
                Peltier2_PWM_Ctrl_WriteControlRegister(Peltier2_PWM_Ctrl_backup.PWMControlRegister);
            #endif /* (Peltier2_PWM_Ctrl_UseControl) */
        #endif  /* (!Peltier2_PWM_Ctrl_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Peltier2_PWM_Ctrl_Sleep
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
*  Peltier2_PWM_Ctrl_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Peltier2_PWM_Ctrl_Sleep(void) 
{
    #if(Peltier2_PWM_Ctrl_UseControl)
        if(Peltier2_PWM_Ctrl_CTRL_ENABLE == (Peltier2_PWM_Ctrl_CONTROL & Peltier2_PWM_Ctrl_CTRL_ENABLE))
        {
            /*Component is enabled */
            Peltier2_PWM_Ctrl_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Peltier2_PWM_Ctrl_backup.PWMEnableState = 0u;
        }
    #endif /* (Peltier2_PWM_Ctrl_UseControl) */

    /* Stop component */
    Peltier2_PWM_Ctrl_Stop();

    /* Save registers configuration */
    Peltier2_PWM_Ctrl_SaveConfig();
}


/*******************************************************************************
* Function Name: Peltier2_PWM_Ctrl_Wakeup
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
*  Peltier2_PWM_Ctrl_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Peltier2_PWM_Ctrl_Wakeup(void) 
{
     /* Restore registers values */
    Peltier2_PWM_Ctrl_RestoreConfig();

    if(Peltier2_PWM_Ctrl_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Peltier2_PWM_Ctrl_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
