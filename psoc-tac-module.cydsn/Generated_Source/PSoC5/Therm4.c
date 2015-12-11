/*******************************************************************************
* File Name: Therm4.c  
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
#include "Therm4.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Therm4__PORT == 15 && ((Therm4__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Therm4_Write
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
void Therm4_Write(uint8 value) 
{
    uint8 staticBits = (Therm4_DR & (uint8)(~Therm4_MASK));
    Therm4_DR = staticBits | ((uint8)(value << Therm4_SHIFT) & Therm4_MASK);
}


/*******************************************************************************
* Function Name: Therm4_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Therm4_DM_STRONG     Strong Drive 
*  Therm4_DM_OD_HI      Open Drain, Drives High 
*  Therm4_DM_OD_LO      Open Drain, Drives Low 
*  Therm4_DM_RES_UP     Resistive Pull Up 
*  Therm4_DM_RES_DWN    Resistive Pull Down 
*  Therm4_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Therm4_DM_DIG_HIZ    High Impedance Digital 
*  Therm4_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Therm4_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Therm4_0, mode);
}


/*******************************************************************************
* Function Name: Therm4_Read
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
*  Macro Therm4_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Therm4_Read(void) 
{
    return (Therm4_PS & Therm4_MASK) >> Therm4_SHIFT;
}


/*******************************************************************************
* Function Name: Therm4_ReadDataReg
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
uint8 Therm4_ReadDataReg(void) 
{
    return (Therm4_DR & Therm4_MASK) >> Therm4_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Therm4_INTSTAT) 

    /*******************************************************************************
    * Function Name: Therm4_ClearInterrupt
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
    uint8 Therm4_ClearInterrupt(void) 
    {
        return (Therm4_INTSTAT & Therm4_MASK) >> Therm4_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
