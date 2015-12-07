/*******************************************************************************
* File Name: outputAgitator2.h  
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

#if !defined(CY_PINS_outputAgitator2_H) /* Pins outputAgitator2_H */
#define CY_PINS_outputAgitator2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "outputAgitator2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 outputAgitator2__PORT == 15 && ((outputAgitator2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    outputAgitator2_Write(uint8 value) ;
void    outputAgitator2_SetDriveMode(uint8 mode) ;
uint8   outputAgitator2_ReadDataReg(void) ;
uint8   outputAgitator2_Read(void) ;
uint8   outputAgitator2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define outputAgitator2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define outputAgitator2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define outputAgitator2_DM_RES_UP          PIN_DM_RES_UP
#define outputAgitator2_DM_RES_DWN         PIN_DM_RES_DWN
#define outputAgitator2_DM_OD_LO           PIN_DM_OD_LO
#define outputAgitator2_DM_OD_HI           PIN_DM_OD_HI
#define outputAgitator2_DM_STRONG          PIN_DM_STRONG
#define outputAgitator2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define outputAgitator2_MASK               outputAgitator2__MASK
#define outputAgitator2_SHIFT              outputAgitator2__SHIFT
#define outputAgitator2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define outputAgitator2_PS                     (* (reg8 *) outputAgitator2__PS)
/* Data Register */
#define outputAgitator2_DR                     (* (reg8 *) outputAgitator2__DR)
/* Port Number */
#define outputAgitator2_PRT_NUM                (* (reg8 *) outputAgitator2__PRT) 
/* Connect to Analog Globals */                                                  
#define outputAgitator2_AG                     (* (reg8 *) outputAgitator2__AG)                       
/* Analog MUX bux enable */
#define outputAgitator2_AMUX                   (* (reg8 *) outputAgitator2__AMUX) 
/* Bidirectional Enable */                                                        
#define outputAgitator2_BIE                    (* (reg8 *) outputAgitator2__BIE)
/* Bit-mask for Aliased Register Access */
#define outputAgitator2_BIT_MASK               (* (reg8 *) outputAgitator2__BIT_MASK)
/* Bypass Enable */
#define outputAgitator2_BYP                    (* (reg8 *) outputAgitator2__BYP)
/* Port wide control signals */                                                   
#define outputAgitator2_CTL                    (* (reg8 *) outputAgitator2__CTL)
/* Drive Modes */
#define outputAgitator2_DM0                    (* (reg8 *) outputAgitator2__DM0) 
#define outputAgitator2_DM1                    (* (reg8 *) outputAgitator2__DM1)
#define outputAgitator2_DM2                    (* (reg8 *) outputAgitator2__DM2) 
/* Input Buffer Disable Override */
#define outputAgitator2_INP_DIS                (* (reg8 *) outputAgitator2__INP_DIS)
/* LCD Common or Segment Drive */
#define outputAgitator2_LCD_COM_SEG            (* (reg8 *) outputAgitator2__LCD_COM_SEG)
/* Enable Segment LCD */
#define outputAgitator2_LCD_EN                 (* (reg8 *) outputAgitator2__LCD_EN)
/* Slew Rate Control */
#define outputAgitator2_SLW                    (* (reg8 *) outputAgitator2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define outputAgitator2_PRTDSI__CAPS_SEL       (* (reg8 *) outputAgitator2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define outputAgitator2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) outputAgitator2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define outputAgitator2_PRTDSI__OE_SEL0        (* (reg8 *) outputAgitator2__PRTDSI__OE_SEL0) 
#define outputAgitator2_PRTDSI__OE_SEL1        (* (reg8 *) outputAgitator2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define outputAgitator2_PRTDSI__OUT_SEL0       (* (reg8 *) outputAgitator2__PRTDSI__OUT_SEL0) 
#define outputAgitator2_PRTDSI__OUT_SEL1       (* (reg8 *) outputAgitator2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define outputAgitator2_PRTDSI__SYNC_OUT       (* (reg8 *) outputAgitator2__PRTDSI__SYNC_OUT) 


#if defined(outputAgitator2__INTSTAT)  /* Interrupt Registers */

    #define outputAgitator2_INTSTAT                (* (reg8 *) outputAgitator2__INTSTAT)
    #define outputAgitator2_SNAP                   (* (reg8 *) outputAgitator2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_outputAgitator2_H */


/* [] END OF FILE */
