/*******************************************************************************
* File Name: fanPeltier1.h  
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

#if !defined(CY_PINS_fanPeltier1_H) /* Pins fanPeltier1_H */
#define CY_PINS_fanPeltier1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "fanPeltier1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 fanPeltier1__PORT == 15 && ((fanPeltier1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    fanPeltier1_Write(uint8 value) ;
void    fanPeltier1_SetDriveMode(uint8 mode) ;
uint8   fanPeltier1_ReadDataReg(void) ;
uint8   fanPeltier1_Read(void) ;
uint8   fanPeltier1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define fanPeltier1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define fanPeltier1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define fanPeltier1_DM_RES_UP          PIN_DM_RES_UP
#define fanPeltier1_DM_RES_DWN         PIN_DM_RES_DWN
#define fanPeltier1_DM_OD_LO           PIN_DM_OD_LO
#define fanPeltier1_DM_OD_HI           PIN_DM_OD_HI
#define fanPeltier1_DM_STRONG          PIN_DM_STRONG
#define fanPeltier1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define fanPeltier1_MASK               fanPeltier1__MASK
#define fanPeltier1_SHIFT              fanPeltier1__SHIFT
#define fanPeltier1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define fanPeltier1_PS                     (* (reg8 *) fanPeltier1__PS)
/* Data Register */
#define fanPeltier1_DR                     (* (reg8 *) fanPeltier1__DR)
/* Port Number */
#define fanPeltier1_PRT_NUM                (* (reg8 *) fanPeltier1__PRT) 
/* Connect to Analog Globals */                                                  
#define fanPeltier1_AG                     (* (reg8 *) fanPeltier1__AG)                       
/* Analog MUX bux enable */
#define fanPeltier1_AMUX                   (* (reg8 *) fanPeltier1__AMUX) 
/* Bidirectional Enable */                                                        
#define fanPeltier1_BIE                    (* (reg8 *) fanPeltier1__BIE)
/* Bit-mask for Aliased Register Access */
#define fanPeltier1_BIT_MASK               (* (reg8 *) fanPeltier1__BIT_MASK)
/* Bypass Enable */
#define fanPeltier1_BYP                    (* (reg8 *) fanPeltier1__BYP)
/* Port wide control signals */                                                   
#define fanPeltier1_CTL                    (* (reg8 *) fanPeltier1__CTL)
/* Drive Modes */
#define fanPeltier1_DM0                    (* (reg8 *) fanPeltier1__DM0) 
#define fanPeltier1_DM1                    (* (reg8 *) fanPeltier1__DM1)
#define fanPeltier1_DM2                    (* (reg8 *) fanPeltier1__DM2) 
/* Input Buffer Disable Override */
#define fanPeltier1_INP_DIS                (* (reg8 *) fanPeltier1__INP_DIS)
/* LCD Common or Segment Drive */
#define fanPeltier1_LCD_COM_SEG            (* (reg8 *) fanPeltier1__LCD_COM_SEG)
/* Enable Segment LCD */
#define fanPeltier1_LCD_EN                 (* (reg8 *) fanPeltier1__LCD_EN)
/* Slew Rate Control */
#define fanPeltier1_SLW                    (* (reg8 *) fanPeltier1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define fanPeltier1_PRTDSI__CAPS_SEL       (* (reg8 *) fanPeltier1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define fanPeltier1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) fanPeltier1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define fanPeltier1_PRTDSI__OE_SEL0        (* (reg8 *) fanPeltier1__PRTDSI__OE_SEL0) 
#define fanPeltier1_PRTDSI__OE_SEL1        (* (reg8 *) fanPeltier1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define fanPeltier1_PRTDSI__OUT_SEL0       (* (reg8 *) fanPeltier1__PRTDSI__OUT_SEL0) 
#define fanPeltier1_PRTDSI__OUT_SEL1       (* (reg8 *) fanPeltier1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define fanPeltier1_PRTDSI__SYNC_OUT       (* (reg8 *) fanPeltier1__PRTDSI__SYNC_OUT) 


#if defined(fanPeltier1__INTSTAT)  /* Interrupt Registers */

    #define fanPeltier1_INTSTAT                (* (reg8 *) fanPeltier1__INTSTAT)
    #define fanPeltier1_SNAP                   (* (reg8 *) fanPeltier1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_fanPeltier1_H */


/* [] END OF FILE */
