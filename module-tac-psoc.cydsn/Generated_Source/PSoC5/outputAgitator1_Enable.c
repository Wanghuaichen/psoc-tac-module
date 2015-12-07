/*******************************************************************************
* File Name: outputAgitator1_Enable.c  
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
#include "outputAgitator1_Enable.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 outputAgitator1_Enable__PORT == 15 && ((outputAgitator1_Enable__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: outputAgitator1_Enable_Write
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
void outputAgitator1_Enable_Write(uint8 value) 
{
    uint8 staticBits = (outputAgitator1_Enable_DR & (uint8)(~outputAgitator1_Enable_MASK));
    outputAgitator1_Enable_DR = staticBits | ((uint8)(value << outputAgitator1_Enable_SHIFT) & outputAgitator1_Enable_MASK);
}


/*******************************************************************************
* Function Name: outputAgitator1_Enable_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  outputAgitator1_Enable_DM_STRONG     Strong Drive 
*  outputAgitator1_Enable_DM_OD_HI      Open Drain, Drives High 
*  outputAgitator1_Enable_DM_OD_LO      Open Drain, Drives Low 
*  outputAgitator1_Enable_DM_RES_UP     Resistive Pull Up 
*  outputAgitator1_Enable_DM_RES_DWN    Resistive Pull Down 
*  outputAgitator1_Enable_DM_RES_UPDWN  Resistive Pull Up/Down 
*  outputAgitator1_Enable_DM_DIG_HIZ    High Impedance Digital 
*  outputAgitator1_Enable_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void outputAgitator1_Enable_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(outputAgitator1_Enable_0, mode);
}


/*******************************************************************************
* Function Name: outputAgitator1_Enable_Read
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
*  Macro outputAgitator1_Enable_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 outputAgitator1_Enable_Read(void) 
{
    return (outputAgitator1_Enable_PS & outputAgitator1_Enable_MASK) >> outputAgitator1_Enable_SHIFT;
}


/*******************************************************************************
* Function Name: outputAgitator1_Enable_ReadDataReg
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
uint8 outputAgitator1_Enable_ReadDataReg(void) 
{
    return (outputAgitator1_Enable_DR & outputAgitator1_Enable_MASK) >> outputAgitator1_Enable_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(outputAgitator1_Enable_INTSTAT) 

    /*******************************************************************************
    * Function Name: outputAgitator1_Enable_ClearInterrupt
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
    uint8 outputAgitator1_Enable_ClearInterrupt(void) 
    {
        return (outputAgitator1_Enable_INTSTAT & outputAgitator1_Enable_MASK) >> outputAgitator1_Enable_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
