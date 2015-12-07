/*******************************************************************************
* File Name: PELTIER2_Heat.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "PELTIER2_Heat.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 PELTIER2_Heat__PORT == 15 && ((PELTIER2_Heat__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: PELTIER2_Heat_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void PELTIER2_Heat_Write(uint8 value) 
{
    uint8 staticBits = (PELTIER2_Heat_DR & (uint8)(~PELTIER2_Heat_MASK));
    PELTIER2_Heat_DR = staticBits | ((uint8)(value << PELTIER2_Heat_SHIFT) & PELTIER2_Heat_MASK);
}


/*******************************************************************************
* Function Name: PELTIER2_Heat_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PELTIER2_Heat_DM_STRONG     Strong Drive 
*  PELTIER2_Heat_DM_OD_HI      Open Drain, Drives High 
*  PELTIER2_Heat_DM_OD_LO      Open Drain, Drives Low 
*  PELTIER2_Heat_DM_RES_UP     Resistive Pull Up 
*  PELTIER2_Heat_DM_RES_DWN    Resistive Pull Down 
*  PELTIER2_Heat_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PELTIER2_Heat_DM_DIG_HIZ    High Impedance Digital 
*  PELTIER2_Heat_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PELTIER2_Heat_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PELTIER2_Heat_0, mode);
}


/*******************************************************************************
* Function Name: PELTIER2_Heat_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro PELTIER2_Heat_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PELTIER2_Heat_Read(void) 
{
    return (PELTIER2_Heat_PS & PELTIER2_Heat_MASK) >> PELTIER2_Heat_SHIFT;
}


/*******************************************************************************
* Function Name: PELTIER2_Heat_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 PELTIER2_Heat_ReadDataReg(void) 
{
    return (PELTIER2_Heat_DR & PELTIER2_Heat_MASK) >> PELTIER2_Heat_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PELTIER2_Heat_INTSTAT) 

    /*******************************************************************************
    * Function Name: PELTIER2_Heat_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 PELTIER2_Heat_ClearInterrupt(void) 
    {
        return (PELTIER2_Heat_INTSTAT & PELTIER2_Heat_MASK) >> PELTIER2_Heat_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
