/*******************************************************************************
* File Name: ClockTurbido.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_ClockTurbido_H)
#define CY_CLOCK_ClockTurbido_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void ClockTurbido_Start(void) ;
void ClockTurbido_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void ClockTurbido_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void ClockTurbido_StandbyPower(uint8 state) ;
void ClockTurbido_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 ClockTurbido_GetDividerRegister(void) ;
void ClockTurbido_SetModeRegister(uint8 modeBitMask) ;
void ClockTurbido_ClearModeRegister(uint8 modeBitMask) ;
uint8 ClockTurbido_GetModeRegister(void) ;
void ClockTurbido_SetSourceRegister(uint8 clkSource) ;
uint8 ClockTurbido_GetSourceRegister(void) ;
#if defined(ClockTurbido__CFG3)
void ClockTurbido_SetPhaseRegister(uint8 clkPhase) ;
uint8 ClockTurbido_GetPhaseRegister(void) ;
#endif /* defined(ClockTurbido__CFG3) */

#define ClockTurbido_Enable()                       ClockTurbido_Start()
#define ClockTurbido_Disable()                      ClockTurbido_Stop()
#define ClockTurbido_SetDivider(clkDivider)         ClockTurbido_SetDividerRegister(clkDivider, 1u)
#define ClockTurbido_SetDividerValue(clkDivider)    ClockTurbido_SetDividerRegister((clkDivider) - 1u, 1u)
#define ClockTurbido_SetMode(clkMode)               ClockTurbido_SetModeRegister(clkMode)
#define ClockTurbido_SetSource(clkSource)           ClockTurbido_SetSourceRegister(clkSource)
#if defined(ClockTurbido__CFG3)
#define ClockTurbido_SetPhase(clkPhase)             ClockTurbido_SetPhaseRegister(clkPhase)
#define ClockTurbido_SetPhaseValue(clkPhase)        ClockTurbido_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(ClockTurbido__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define ClockTurbido_CLKEN              (* (reg8 *) ClockTurbido__PM_ACT_CFG)
#define ClockTurbido_CLKEN_PTR          ((reg8 *) ClockTurbido__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define ClockTurbido_CLKSTBY            (* (reg8 *) ClockTurbido__PM_STBY_CFG)
#define ClockTurbido_CLKSTBY_PTR        ((reg8 *) ClockTurbido__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define ClockTurbido_DIV_LSB            (* (reg8 *) ClockTurbido__CFG0)
#define ClockTurbido_DIV_LSB_PTR        ((reg8 *) ClockTurbido__CFG0)
#define ClockTurbido_DIV_PTR            ((reg16 *) ClockTurbido__CFG0)

/* Clock MSB divider configuration register. */
#define ClockTurbido_DIV_MSB            (* (reg8 *) ClockTurbido__CFG1)
#define ClockTurbido_DIV_MSB_PTR        ((reg8 *) ClockTurbido__CFG1)

/* Mode and source configuration register */
#define ClockTurbido_MOD_SRC            (* (reg8 *) ClockTurbido__CFG2)
#define ClockTurbido_MOD_SRC_PTR        ((reg8 *) ClockTurbido__CFG2)

#if defined(ClockTurbido__CFG3)
/* Analog clock phase configuration register */
#define ClockTurbido_PHASE              (* (reg8 *) ClockTurbido__CFG3)
#define ClockTurbido_PHASE_PTR          ((reg8 *) ClockTurbido__CFG3)
#endif /* defined(ClockTurbido__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define ClockTurbido_CLKEN_MASK         ClockTurbido__PM_ACT_MSK
#define ClockTurbido_CLKSTBY_MASK       ClockTurbido__PM_STBY_MSK

/* CFG2 field masks */
#define ClockTurbido_SRC_SEL_MSK        ClockTurbido__CFG2_SRC_SEL_MASK
#define ClockTurbido_MODE_MASK          (~(ClockTurbido_SRC_SEL_MSK))

#if defined(ClockTurbido__CFG3)
/* CFG3 phase mask */
#define ClockTurbido_PHASE_MASK         ClockTurbido__CFG3_PHASE_DLY_MASK
#endif /* defined(ClockTurbido__CFG3) */

#endif /* CY_CLOCK_ClockTurbido_H */


/* [] END OF FILE */
