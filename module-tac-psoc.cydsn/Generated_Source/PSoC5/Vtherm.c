/*******************************************************************************
* File Name: VTherm.c  
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
#include "VTherm.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 VTherm__PORT == 15 && ((VTherm__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: VTherm_Write
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
void VTherm_Write(uint8 value) 
{
    uint8 staticBits = (VTherm_DR & (uint8)(~VTherm_MASK));
    VTherm_DR = staticBits | ((uint8)(value << VTherm_SHIFT) & VTherm_MASK);
}


/*******************************************************************************
* Function Name: VTherm_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  VTherm_DM_STRONG     Strong Drive 
*  VTherm_DM_OD_HI      Open Drain, Drives High 
*  VTherm_DM_OD_LO      Open Drain, Drives Low 
*  VTherm_DM_RES_UP     Resistive Pull Up 
*  VTherm_DM_RES_DWN    Resistive Pull Down 
*  VTherm_DM_RES_UPDWN  Resistive Pull Up/Down 
*  VTherm_DM_DIG_HIZ    High Impedance Digital 
*  VTherm_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void VTherm_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(VTherm_0, mode);
}


/*******************************************************************************
* Function Name: VTherm_Read
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
*  Macro VTherm_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 VTherm_Read(void) 
{
    return (VTherm_PS & VTherm_MASK) >> VTherm_SHIFT;
}


/*******************************************************************************
* Function Name: VTherm_ReadDataReg
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
uint8 VTherm_ReadDataReg(void) 
{
    return (VTherm_DR & VTherm_MASK) >> VTherm_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(VTherm_INTSTAT) 

    /*******************************************************************************
    * Function Name: VTherm_ClearInterrupt
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
    uint8 VTherm_ClearInterrupt(void) 
    {
        return (VTherm_INTSTAT & VTherm_MASK) >> VTherm_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
