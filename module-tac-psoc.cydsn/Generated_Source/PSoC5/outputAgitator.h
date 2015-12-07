/*******************************************************************************
* File Name: outputAgitator.h  
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

#if !defined(CY_PINS_outputAgitator_H) /* Pins outputAgitator_H */
#define CY_PINS_outputAgitator_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "outputAgitator_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 outputAgitator__PORT == 15 && ((outputAgitator__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    outputAgitator_Write(uint8 value) ;
void    outputAgitator_SetDriveMode(uint8 mode) ;
uint8   outputAgitator_ReadDataReg(void) ;
uint8   outputAgitator_Read(void) ;
uint8   outputAgitator_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define outputAgitator_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define outputAgitator_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define outputAgitator_DM_RES_UP          PIN_DM_RES_UP
#define outputAgitator_DM_RES_DWN         PIN_DM_RES_DWN
#define outputAgitator_DM_OD_LO           PIN_DM_OD_LO
#define outputAgitator_DM_OD_HI           PIN_DM_OD_HI
#define outputAgitator_DM_STRONG          PIN_DM_STRONG
#define outputAgitator_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define outputAgitator_MASK               outputAgitator__MASK
#define outputAgitator_SHIFT              outputAgitator__SHIFT
#define outputAgitator_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define outputAgitator_PS                     (* (reg8 *) outputAgitator__PS)
/* Data Register */
#define outputAgitator_DR                     (* (reg8 *) outputAgitator__DR)
/* Port Number */
#define outputAgitator_PRT_NUM                (* (reg8 *) outputAgitator__PRT) 
/* Connect to Analog Globals */                                                  
#define outputAgitator_AG                     (* (reg8 *) outputAgitator__AG)                       
/* Analog MUX bux enable */
#define outputAgitator_AMUX                   (* (reg8 *) outputAgitator__AMUX) 
/* Bidirectional Enable */                                                        
#define outputAgitator_BIE                    (* (reg8 *) outputAgitator__BIE)
/* Bit-mask for Aliased Register Access */
#define outputAgitator_BIT_MASK               (* (reg8 *) outputAgitator__BIT_MASK)
/* Bypass Enable */
#define outputAgitator_BYP                    (* (reg8 *) outputAgitator__BYP)
/* Port wide control signals */                                                   
#define outputAgitator_CTL                    (* (reg8 *) outputAgitator__CTL)
/* Drive Modes */
#define outputAgitator_DM0                    (* (reg8 *) outputAgitator__DM0) 
#define outputAgitator_DM1                    (* (reg8 *) outputAgitator__DM1)
#define outputAgitator_DM2                    (* (reg8 *) outputAgitator__DM2) 
/* Input Buffer Disable Override */
#define outputAgitator_INP_DIS                (* (reg8 *) outputAgitator__INP_DIS)
/* LCD Common or Segment Drive */
#define outputAgitator_LCD_COM_SEG            (* (reg8 *) outputAgitator__LCD_COM_SEG)
/* Enable Segment LCD */
#define outputAgitator_LCD_EN                 (* (reg8 *) outputAgitator__LCD_EN)
/* Slew Rate Control */
#define outputAgitator_SLW                    (* (reg8 *) outputAgitator__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define outputAgitator_PRTDSI__CAPS_SEL       (* (reg8 *) outputAgitator__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define outputAgitator_PRTDSI__DBL_SYNC_IN    (* (reg8 *) outputAgitator__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define outputAgitator_PRTDSI__OE_SEL0        (* (reg8 *) outputAgitator__PRTDSI__OE_SEL0) 
#define outputAgitator_PRTDSI__OE_SEL1        (* (reg8 *) outputAgitator__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define outputAgitator_PRTDSI__OUT_SEL0       (* (reg8 *) outputAgitator__PRTDSI__OUT_SEL0) 
#define outputAgitator_PRTDSI__OUT_SEL1       (* (reg8 *) outputAgitator__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define outputAgitator_PRTDSI__SYNC_OUT       (* (reg8 *) outputAgitator__PRTDSI__SYNC_OUT) 


#if defined(outputAgitator__INTSTAT)  /* Interrupt Registers */

    #define outputAgitator_INTSTAT                (* (reg8 *) outputAgitator__INTSTAT)
    #define outputAgitator_SNAP                   (* (reg8 *) outputAgitator__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_outputAgitator_H */


/* [] END OF FILE */
