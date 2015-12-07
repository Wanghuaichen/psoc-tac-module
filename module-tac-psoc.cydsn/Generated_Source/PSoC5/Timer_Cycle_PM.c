/*******************************************************************************
* File Name: Timer_Cycle_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Cycle.h"

static Timer_Cycle_backupStruct Timer_Cycle_backup;


/*******************************************************************************
* Function Name: Timer_Cycle_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Cycle_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Cycle_SaveConfig(void) 
{
    #if (!Timer_Cycle_UsingFixedFunction)
        Timer_Cycle_backup.TimerUdb = Timer_Cycle_ReadCounter();
        Timer_Cycle_backup.InterruptMaskValue = Timer_Cycle_STATUS_MASK;
        #if (Timer_Cycle_UsingHWCaptureCounter)
            Timer_Cycle_backup.TimerCaptureCounter = Timer_Cycle_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Cycle_UDB_CONTROL_REG_REMOVED)
            Timer_Cycle_backup.TimerControlRegister = Timer_Cycle_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Cycle_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Cycle_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Cycle_RestoreConfig(void) 
{   
    #if (!Timer_Cycle_UsingFixedFunction)

        Timer_Cycle_WriteCounter(Timer_Cycle_backup.TimerUdb);
        Timer_Cycle_STATUS_MASK =Timer_Cycle_backup.InterruptMaskValue;
        #if (Timer_Cycle_UsingHWCaptureCounter)
            Timer_Cycle_SetCaptureCount(Timer_Cycle_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Cycle_UDB_CONTROL_REG_REMOVED)
            Timer_Cycle_WriteControlRegister(Timer_Cycle_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Cycle_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Cycle_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Cycle_Sleep(void) 
{
    #if(!Timer_Cycle_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Cycle_CTRL_ENABLE == (Timer_Cycle_CONTROL & Timer_Cycle_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Cycle_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Cycle_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Cycle_Stop();
    Timer_Cycle_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Cycle_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Cycle_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Cycle_Wakeup(void) 
{
    Timer_Cycle_RestoreConfig();
    #if(!Timer_Cycle_UDB_CONTROL_REG_REMOVED)
        if(Timer_Cycle_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Cycle_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
