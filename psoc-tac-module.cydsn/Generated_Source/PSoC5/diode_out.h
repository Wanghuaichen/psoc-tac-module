/*******************************************************************************
* File Name: diode_out.h  
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

#if !defined(CY_PINS_diode_out_H) /* Pins diode_out_H */
#define CY_PINS_diode_out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "diode_out_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 diode_out__PORT == 15 && ((diode_out__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    diode_out_Write(uint8 value) ;
void    diode_out_SetDriveMode(uint8 mode) ;
uint8   diode_out_ReadDataReg(void) ;
uint8   diode_out_Read(void) ;
uint8   diode_out_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define diode_out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define diode_out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define diode_out_DM_RES_UP          PIN_DM_RES_UP
#define diode_out_DM_RES_DWN         PIN_DM_RES_DWN
#define diode_out_DM_OD_LO           PIN_DM_OD_LO
#define diode_out_DM_OD_HI           PIN_DM_OD_HI
#define diode_out_DM_STRONG          PIN_DM_STRONG
#define diode_out_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define diode_out_MASK               diode_out__MASK
#define diode_out_SHIFT              diode_out__SHIFT
#define diode_out_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define diode_out_PS                     (* (reg8 *) diode_out__PS)
/* Data Register */
#define diode_out_DR                     (* (reg8 *) diode_out__DR)
/* Port Number */
#define diode_out_PRT_NUM                (* (reg8 *) diode_out__PRT) 
/* Connect to Analog Globals */                                                  
#define diode_out_AG                     (* (reg8 *) diode_out__AG)                       
/* Analog MUX bux enable */
#define diode_out_AMUX                   (* (reg8 *) diode_out__AMUX) 
/* Bidirectional Enable */                                                        
#define diode_out_BIE                    (* (reg8 *) diode_out__BIE)
/* Bit-mask for Aliased Register Access */
#define diode_out_BIT_MASK               (* (reg8 *) diode_out__BIT_MASK)
/* Bypass Enable */
#define diode_out_BYP                    (* (reg8 *) diode_out__BYP)
/* Port wide control signals */                                                   
#define diode_out_CTL                    (* (reg8 *) diode_out__CTL)
/* Drive Modes */
#define diode_out_DM0                    (* (reg8 *) diode_out__DM0) 
#define diode_out_DM1                    (* (reg8 *) diode_out__DM1)
#define diode_out_DM2                    (* (reg8 *) diode_out__DM2) 
/* Input Buffer Disable Override */
#define diode_out_INP_DIS                (* (reg8 *) diode_out__INP_DIS)
/* LCD Common or Segment Drive */
#define diode_out_LCD_COM_SEG            (* (reg8 *) diode_out__LCD_COM_SEG)
/* Enable Segment LCD */
#define diode_out_LCD_EN                 (* (reg8 *) diode_out__LCD_EN)
/* Slew Rate Control */
#define diode_out_SLW                    (* (reg8 *) diode_out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define diode_out_PRTDSI__CAPS_SEL       (* (reg8 *) diode_out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define diode_out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) diode_out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define diode_out_PRTDSI__OE_SEL0        (* (reg8 *) diode_out__PRTDSI__OE_SEL0) 
#define diode_out_PRTDSI__OE_SEL1        (* (reg8 *) diode_out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define diode_out_PRTDSI__OUT_SEL0       (* (reg8 *) diode_out__PRTDSI__OUT_SEL0) 
#define diode_out_PRTDSI__OUT_SEL1       (* (reg8 *) diode_out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define diode_out_PRTDSI__SYNC_OUT       (* (reg8 *) diode_out__PRTDSI__SYNC_OUT) 


#if defined(diode_out__INTSTAT)  /* Interrupt Registers */

    #define diode_out_INTSTAT                (* (reg8 *) diode_out__INTSTAT)
    #define diode_out_SNAP                   (* (reg8 *) diode_out__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_diode_out_H */


/* [] END OF FILE */
