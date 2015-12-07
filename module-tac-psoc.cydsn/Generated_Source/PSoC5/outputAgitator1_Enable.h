/*******************************************************************************
* File Name: outputAgitator1_Enable.h  
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

#if !defined(CY_PINS_outputAgitator1_Enable_H) /* Pins outputAgitator1_Enable_H */
#define CY_PINS_outputAgitator1_Enable_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "outputAgitator1_Enable_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 outputAgitator1_Enable__PORT == 15 && ((outputAgitator1_Enable__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    outputAgitator1_Enable_Write(uint8 value) ;
void    outputAgitator1_Enable_SetDriveMode(uint8 mode) ;
uint8   outputAgitator1_Enable_ReadDataReg(void) ;
uint8   outputAgitator1_Enable_Read(void) ;
uint8   outputAgitator1_Enable_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define outputAgitator1_Enable_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define outputAgitator1_Enable_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define outputAgitator1_Enable_DM_RES_UP          PIN_DM_RES_UP
#define outputAgitator1_Enable_DM_RES_DWN         PIN_DM_RES_DWN
#define outputAgitator1_Enable_DM_OD_LO           PIN_DM_OD_LO
#define outputAgitator1_Enable_DM_OD_HI           PIN_DM_OD_HI
#define outputAgitator1_Enable_DM_STRONG          PIN_DM_STRONG
#define outputAgitator1_Enable_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define outputAgitator1_Enable_MASK               outputAgitator1_Enable__MASK
#define outputAgitator1_Enable_SHIFT              outputAgitator1_Enable__SHIFT
#define outputAgitator1_Enable_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define outputAgitator1_Enable_PS                     (* (reg8 *) outputAgitator1_Enable__PS)
/* Data Register */
#define outputAgitator1_Enable_DR                     (* (reg8 *) outputAgitator1_Enable__DR)
/* Port Number */
#define outputAgitator1_Enable_PRT_NUM                (* (reg8 *) outputAgitator1_Enable__PRT) 
/* Connect to Analog Globals */                                                  
#define outputAgitator1_Enable_AG                     (* (reg8 *) outputAgitator1_Enable__AG)                       
/* Analog MUX bux enable */
#define outputAgitator1_Enable_AMUX                   (* (reg8 *) outputAgitator1_Enable__AMUX) 
/* Bidirectional Enable */                                                        
#define outputAgitator1_Enable_BIE                    (* (reg8 *) outputAgitator1_Enable__BIE)
/* Bit-mask for Aliased Register Access */
#define outputAgitator1_Enable_BIT_MASK               (* (reg8 *) outputAgitator1_Enable__BIT_MASK)
/* Bypass Enable */
#define outputAgitator1_Enable_BYP                    (* (reg8 *) outputAgitator1_Enable__BYP)
/* Port wide control signals */                                                   
#define outputAgitator1_Enable_CTL                    (* (reg8 *) outputAgitator1_Enable__CTL)
/* Drive Modes */
#define outputAgitator1_Enable_DM0                    (* (reg8 *) outputAgitator1_Enable__DM0) 
#define outputAgitator1_Enable_DM1                    (* (reg8 *) outputAgitator1_Enable__DM1)
#define outputAgitator1_Enable_DM2                    (* (reg8 *) outputAgitator1_Enable__DM2) 
/* Input Buffer Disable Override */
#define outputAgitator1_Enable_INP_DIS                (* (reg8 *) outputAgitator1_Enable__INP_DIS)
/* LCD Common or Segment Drive */
#define outputAgitator1_Enable_LCD_COM_SEG            (* (reg8 *) outputAgitator1_Enable__LCD_COM_SEG)
/* Enable Segment LCD */
#define outputAgitator1_Enable_LCD_EN                 (* (reg8 *) outputAgitator1_Enable__LCD_EN)
/* Slew Rate Control */
#define outputAgitator1_Enable_SLW                    (* (reg8 *) outputAgitator1_Enable__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define outputAgitator1_Enable_PRTDSI__CAPS_SEL       (* (reg8 *) outputAgitator1_Enable__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define outputAgitator1_Enable_PRTDSI__DBL_SYNC_IN    (* (reg8 *) outputAgitator1_Enable__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define outputAgitator1_Enable_PRTDSI__OE_SEL0        (* (reg8 *) outputAgitator1_Enable__PRTDSI__OE_SEL0) 
#define outputAgitator1_Enable_PRTDSI__OE_SEL1        (* (reg8 *) outputAgitator1_Enable__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define outputAgitator1_Enable_PRTDSI__OUT_SEL0       (* (reg8 *) outputAgitator1_Enable__PRTDSI__OUT_SEL0) 
#define outputAgitator1_Enable_PRTDSI__OUT_SEL1       (* (reg8 *) outputAgitator1_Enable__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define outputAgitator1_Enable_PRTDSI__SYNC_OUT       (* (reg8 *) outputAgitator1_Enable__PRTDSI__SYNC_OUT) 


#if defined(outputAgitator1_Enable__INTSTAT)  /* Interrupt Registers */

    #define outputAgitator1_Enable_INTSTAT                (* (reg8 *) outputAgitator1_Enable__INTSTAT)
    #define outputAgitator1_Enable_SNAP                   (* (reg8 *) outputAgitator1_Enable__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_outputAgitator1_Enable_H */


/* [] END OF FILE */
