/*******************************************************************************
* File Name: fanPeltier.c  
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
#include "fanPeltier.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 fanPeltier__PORT == 15 && ((fanPeltier__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: fanPeltier_Write
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
void fanPeltier_Write(uint8 value) 
{
    uint8 staticBits = (fanPeltier_DR & (uint8)(~fanPeltier_MASK));
    fanPeltier_DR = staticBits | ((uint8)(value << fanPeltier_SHIFT) & fanPeltier_MASK);
}


/*******************************************************************************
* Function Name: fanPeltier_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  fanPeltier_DM_STRONG     Strong Drive 
*  fanPeltier_DM_OD_HI      Open Drain, Drives High 
*  fanPeltier_DM_OD_LO      Open Drain, Drives Low 
*  fanPeltier_DM_RES_UP     Resistive Pull Up 
*  fanPeltier_DM_RES_DWN    Resistive Pull Down 
*  fanPeltier_DM_RES_UPDWN  Resistive Pull Up/Down 
*  fanPeltier_DM_DIG_HIZ    High Impedance Digital 
*  fanPeltier_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void fanPeltier_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(fanPeltier_0, mode);
}


/*******************************************************************************
* Function Name: fanPeltier_Read
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
*  Macro fanPeltier_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 fanPeltier_Read(void) 
{
    return (fanPeltier_PS & fanPeltier_MASK) >> fanPeltier_SHIFT;
}


/*******************************************************************************
* Function Name: fanPeltier_ReadDataReg
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
uint8 fanPeltier_ReadDataReg(void) 
{
    return (fanPeltier_DR & fanPeltier_MASK) >> fanPeltier_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(fanPeltier_INTSTAT) 

    /*******************************************************************************
    * Function Name: fanPeltier_ClearInterrupt
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
    uint8 fanPeltier_ClearInterrupt(void) 
    {
        return (fanPeltier_INTSTAT & fanPeltier_MASK) >> fanPeltier_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
