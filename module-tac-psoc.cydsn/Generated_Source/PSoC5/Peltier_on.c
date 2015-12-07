/*******************************************************************************
* File Name: Peltier_on.c  
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
#include "Peltier_on.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Peltier_on__PORT == 15 && ((Peltier_on__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Peltier_on_Write
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
void Peltier_on_Write(uint8 value) 
{
    uint8 staticBits = (Peltier_on_DR & (uint8)(~Peltier_on_MASK));
    Peltier_on_DR = staticBits | ((uint8)(value << Peltier_on_SHIFT) & Peltier_on_MASK);
}


/*******************************************************************************
* Function Name: Peltier_on_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Peltier_on_DM_STRONG     Strong Drive 
*  Peltier_on_DM_OD_HI      Open Drain, Drives High 
*  Peltier_on_DM_OD_LO      Open Drain, Drives Low 
*  Peltier_on_DM_RES_UP     Resistive Pull Up 
*  Peltier_on_DM_RES_DWN    Resistive Pull Down 
*  Peltier_on_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Peltier_on_DM_DIG_HIZ    High Impedance Digital 
*  Peltier_on_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Peltier_on_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Peltier_on_0, mode);
}


/*******************************************************************************
* Function Name: Peltier_on_Read
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
*  Macro Peltier_on_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Peltier_on_Read(void) 
{
    return (Peltier_on_PS & Peltier_on_MASK) >> Peltier_on_SHIFT;
}


/*******************************************************************************
* Function Name: Peltier_on_ReadDataReg
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
uint8 Peltier_on_ReadDataReg(void) 
{
    return (Peltier_on_DR & Peltier_on_MASK) >> Peltier_on_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Peltier_on_INTSTAT) 

    /*******************************************************************************
    * Function Name: Peltier_on_ClearInterrupt
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
    uint8 Peltier_on_ClearInterrupt(void) 
    {
        return (Peltier_on_INTSTAT & Peltier_on_MASK) >> Peltier_on_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
