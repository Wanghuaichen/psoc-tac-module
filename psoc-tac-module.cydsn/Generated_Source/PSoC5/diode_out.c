/*******************************************************************************
* File Name: diode_out.c  
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
#include "diode_out.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 diode_out__PORT == 15 && ((diode_out__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: diode_out_Write
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
void diode_out_Write(uint8 value) 
{
    uint8 staticBits = (diode_out_DR & (uint8)(~diode_out_MASK));
    diode_out_DR = staticBits | ((uint8)(value << diode_out_SHIFT) & diode_out_MASK);
}


/*******************************************************************************
* Function Name: diode_out_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  diode_out_DM_STRONG     Strong Drive 
*  diode_out_DM_OD_HI      Open Drain, Drives High 
*  diode_out_DM_OD_LO      Open Drain, Drives Low 
*  diode_out_DM_RES_UP     Resistive Pull Up 
*  diode_out_DM_RES_DWN    Resistive Pull Down 
*  diode_out_DM_RES_UPDWN  Resistive Pull Up/Down 
*  diode_out_DM_DIG_HIZ    High Impedance Digital 
*  diode_out_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void diode_out_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(diode_out_0, mode);
}


/*******************************************************************************
* Function Name: diode_out_Read
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
*  Macro diode_out_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 diode_out_Read(void) 
{
    return (diode_out_PS & diode_out_MASK) >> diode_out_SHIFT;
}


/*******************************************************************************
* Function Name: diode_out_ReadDataReg
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
uint8 diode_out_ReadDataReg(void) 
{
    return (diode_out_DR & diode_out_MASK) >> diode_out_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(diode_out_INTSTAT) 

    /*******************************************************************************
    * Function Name: diode_out_ClearInterrupt
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
    uint8 diode_out_ClearInterrupt(void) 
    {
        return (diode_out_INTSTAT & diode_out_MASK) >> diode_out_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
