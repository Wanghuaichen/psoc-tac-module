/*******************************************************************************
* File Name: PWM_cool.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PWM_cool_H) /* Pins PWM_cool_H */
#define CY_PINS_PWM_cool_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWM_cool_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PWM_cool__PORT == 15 && ((PWM_cool__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PWM_cool_Write(uint8 value) ;
void    PWM_cool_SetDriveMode(uint8 mode) ;
uint8   PWM_cool_ReadDataReg(void) ;
uint8   PWM_cool_Read(void) ;
uint8   PWM_cool_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWM_cool_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PWM_cool_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PWM_cool_DM_RES_UP          PIN_DM_RES_UP
#define PWM_cool_DM_RES_DWN         PIN_DM_RES_DWN
#define PWM_cool_DM_OD_LO           PIN_DM_OD_LO
#define PWM_cool_DM_OD_HI           PIN_DM_OD_HI
#define PWM_cool_DM_STRONG          PIN_DM_STRONG
#define PWM_cool_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PWM_cool_MASK               PWM_cool__MASK
#define PWM_cool_SHIFT              PWM_cool__SHIFT
#define PWM_cool_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWM_cool_PS                     (* (reg8 *) PWM_cool__PS)
/* Data Register */
#define PWM_cool_DR                     (* (reg8 *) PWM_cool__DR)
/* Port Number */
#define PWM_cool_PRT_NUM                (* (reg8 *) PWM_cool__PRT) 
/* Connect to Analog Globals */                                                  
#define PWM_cool_AG                     (* (reg8 *) PWM_cool__AG)                       
/* Analog MUX bux enable */
#define PWM_cool_AMUX                   (* (reg8 *) PWM_cool__AMUX) 
/* Bidirectional Enable */                                                        
#define PWM_cool_BIE                    (* (reg8 *) PWM_cool__BIE)
/* Bit-mask for Aliased Register Access */
#define PWM_cool_BIT_MASK               (* (reg8 *) PWM_cool__BIT_MASK)
/* Bypass Enable */
#define PWM_cool_BYP                    (* (reg8 *) PWM_cool__BYP)
/* Port wide control signals */                                                   
#define PWM_cool_CTL                    (* (reg8 *) PWM_cool__CTL)
/* Drive Modes */
#define PWM_cool_DM0                    (* (reg8 *) PWM_cool__DM0) 
#define PWM_cool_DM1                    (* (reg8 *) PWM_cool__DM1)
#define PWM_cool_DM2                    (* (reg8 *) PWM_cool__DM2) 
/* Input Buffer Disable Override */
#define PWM_cool_INP_DIS                (* (reg8 *) PWM_cool__INP_DIS)
/* LCD Common or Segment Drive */
#define PWM_cool_LCD_COM_SEG            (* (reg8 *) PWM_cool__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWM_cool_LCD_EN                 (* (reg8 *) PWM_cool__LCD_EN)
/* Slew Rate Control */
#define PWM_cool_SLW                    (* (reg8 *) PWM_cool__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWM_cool_PRTDSI__CAPS_SEL       (* (reg8 *) PWM_cool__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWM_cool_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWM_cool__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWM_cool_PRTDSI__OE_SEL0        (* (reg8 *) PWM_cool__PRTDSI__OE_SEL0) 
#define PWM_cool_PRTDSI__OE_SEL1        (* (reg8 *) PWM_cool__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWM_cool_PRTDSI__OUT_SEL0       (* (reg8 *) PWM_cool__PRTDSI__OUT_SEL0) 
#define PWM_cool_PRTDSI__OUT_SEL1       (* (reg8 *) PWM_cool__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWM_cool_PRTDSI__SYNC_OUT       (* (reg8 *) PWM_cool__PRTDSI__SYNC_OUT) 


#if defined(PWM_cool__INTSTAT)  /* Interrupt Registers */

    #define PWM_cool_INTSTAT                (* (reg8 *) PWM_cool__INTSTAT)
    #define PWM_cool_SNAP                   (* (reg8 *) PWM_cool__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PWM_cool_H */


/* [] END OF FILE */
