/*******************************************************************************
* File Name: photo_test.c  
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
#include "photo_test.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 photo_test__PORT == 15 && ((photo_test__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: photo_test_Write
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
void photo_test_Write(uint8 value) 
{
    uint8 staticBits = (photo_test_DR & (uint8)(~photo_test_MASK));
    photo_test_DR = staticBits | ((uint8)(value << photo_test_SHIFT) & photo_test_MASK);
}


/*******************************************************************************
* Function Name: photo_test_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  photo_test_DM_STRONG     Strong Drive 
*  photo_test_DM_OD_HI      Open Drain, Drives High 
*  photo_test_DM_OD_LO      Open Drain, Drives Low 
*  photo_test_DM_RES_UP     Resistive Pull Up 
*  photo_test_DM_RES_DWN    Resistive Pull Down 
*  photo_test_DM_RES_UPDWN  Resistive Pull Up/Down 
*  photo_test_DM_DIG_HIZ    High Impedance Digital 
*  photo_test_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void photo_test_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(photo_test_0, mode);
}


/*******************************************************************************
* Function Name: photo_test_Read
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
*  Macro photo_test_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 photo_test_Read(void) 
{
    return (photo_test_PS & photo_test_MASK) >> photo_test_SHIFT;
}


/*******************************************************************************
* Function Name: photo_test_ReadDataReg
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
uint8 photo_test_ReadDataReg(void) 
{
    return (photo_test_DR & photo_test_MASK) >> photo_test_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(photo_test_INTSTAT) 

    /*******************************************************************************
    * Function Name: photo_test_ClearInterrupt
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
    uint8 photo_test_ClearInterrupt(void) 
    {
        return (photo_test_INTSTAT & photo_test_MASK) >> photo_test_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
