/*******************************************************************************
* File Name: Peltier1_PWM_Ctrl_PM.c
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

#include "Peltier1_PWM_Ctrl.h"

static Peltier1_PWM_Ctrl_backupStruct Peltier1_PWM_Ctrl_backup;


/*******************************************************************************
* Function Name: Peltier1_PWM_Ctrl_SaveConfig
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
*  Peltier1_PWM_Ctrl_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Peltier1_PWM_Ctrl_SaveConfig(void) 
{

    #if(!Peltier1_PWM_Ctrl_UsingFixedFunction)
        #if(!Peltier1_PWM_Ctrl_PWMModeIsCenterAligned)
            Peltier1_PWM_Ctrl_backup.PWMPeriod = Peltier1_PWM_Ctrl_ReadPeriod();
        #endif /* (!Peltier1_PWM_Ctrl_PWMModeIsCenterAligned) */
        Peltier1_PWM_Ctrl_backup.PWMUdb = Peltier1_PWM_Ctrl_ReadCounter();
        #if (Peltier1_PWM_Ctrl_UseStatus)
            Peltier1_PWM_Ctrl_backup.InterruptMaskValue = Peltier1_PWM_Ctrl_STATUS_MASK;
        #endif /* (Peltier1_PWM_Ctrl_UseStatus) */

        #if(Peltier1_PWM_Ctrl_DeadBandMode == Peltier1_PWM_Ctrl__B_PWM__DBM_256_CLOCKS || \
            Peltier1_PWM_Ctrl_DeadBandMode == Peltier1_PWM_Ctrl__B_PWM__DBM_2_4_CLOCKS)
            Peltier1_PWM_Ctrl_backup.PWMdeadBandValue = Peltier1_PWM_Ctrl_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Peltier1_PWM_Ctrl_KillModeMinTime)
             Peltier1_PWM_Ctrl_backup.PWMKillCounterPeriod = Peltier1_PWM_Ctrl_ReadKillTime();
        #endif /* (Peltier1_PWM_Ctrl_KillModeMinTime) */

        #if(Peltier1_PWM_Ctrl_UseControl)
            Peltier1_PWM_Ctrl_backup.PWMControlRegister = Peltier1_PWM_Ctrl_ReadControlRegister();
        #endif /* (Peltier1_PWM_Ctrl_UseControl) */
    #endif  /* (!Peltier1_PWM_Ctrl_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Peltier1_PWM_Ctrl_RestoreConfig
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
*  Peltier1_PWM_Ctrl_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Peltier1_PWM_Ctrl_RestoreConfig(void) 
{
        #if(!Peltier1_PWM_Ctrl_UsingFixedFunction)
            #if(!Peltier1_PWM_Ctrl_PWMModeIsCenterAligned)
                Peltier1_PWM_Ctrl_WritePeriod(Peltier1_PWM_Ctrl_backup.PWMPeriod);
            #endif /* (!Peltier1_PWM_Ctrl_PWMModeIsCenterAligned) */

            Peltier1_PWM_Ctrl_WriteCounter(Peltier1_PWM_Ctrl_backup.PWMUdb);

            #if (Peltier1_PWM_Ctrl_UseStatus)
                Peltier1_PWM_Ctrl_STATUS_MASK = Peltier1_PWM_Ctrl_backup.InterruptMaskValue;
            #endif /* (Peltier1_PWM_Ctrl_UseStatus) */

            #if(Peltier1_PWM_Ctrl_DeadBandMode == Peltier1_PWM_Ctrl__B_PWM__DBM_256_CLOCKS || \
                Peltier1_PWM_Ctrl_DeadBandMode == Peltier1_PWM_Ctrl__B_PWM__DBM_2_4_CLOCKS)
                Peltier1_PWM_Ctrl_WriteDeadTime(Peltier1_PWM_Ctrl_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Peltier1_PWM_Ctrl_KillModeMinTime)
                Peltier1_PWM_Ctrl_WriteKillTime(Peltier1_PWM_Ctrl_backup.PWMKillCounterPeriod);
            #endif /* (Peltier1_PWM_Ctrl_KillModeMinTime) */

            #if(Peltier1_PWM_Ctrl_UseControl)
                Peltier1_PWM_Ctrl_WriteControlRegister(Peltier1_PWM_Ctrl_backup.PWMControlRegister);
            #endif /* (Peltier1_PWM_Ctrl_UseControl) */
        #endif  /* (!Peltier1_PWM_Ctrl_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Peltier1_PWM_Ctrl_Sleep
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
*  Peltier1_PWM_Ctrl_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Peltier1_PWM_Ctrl_Sleep(void) 
{
    #if(Peltier1_PWM_Ctrl_UseControl)
        if(Peltier1_PWM_Ctrl_CTRL_ENABLE == (Peltier1_PWM_Ctrl_CONTROL & Peltier1_PWM_Ctrl_CTRL_ENABLE))
        {
            /*Component is enabled */
            Peltier1_PWM_Ctrl_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Peltier1_PWM_Ctrl_backup.PWMEnableState = 0u;
        }
    #endif /* (Peltier1_PWM_Ctrl_UseControl) */

    /* Stop component */
    Peltier1_PWM_Ctrl_Stop();

    /* Save registers configuration */
    Peltier1_PWM_Ctrl_SaveConfig();
}


/*******************************************************************************
* Function Name: Peltier1_PWM_Ctrl_Wakeup
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
*  Peltier1_PWM_Ctrl_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Peltier1_PWM_Ctrl_Wakeup(void) 
{
     /* Restore registers values */
    Peltier1_PWM_Ctrl_RestoreConfig();

    if(Peltier1_PWM_Ctrl_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Peltier1_PWM_Ctrl_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
