/*******************************************************************************
* File Name: fanPeltier.h  
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

#if !defined(CY_PINS_fanPeltier_H) /* Pins fanPeltier_H */
#define CY_PINS_fanPeltier_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "fanPeltier_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 fanPeltier__PORT == 15 && ((fanPeltier__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    fanPeltier_Write(uint8 value) ;
void    fanPeltier_SetDriveMode(uint8 mode) ;
uint8   fanPeltier_ReadDataReg(void) ;
uint8   fanPeltier_Read(void) ;
uint8   fanPeltier_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define fanPeltier_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define fanPeltier_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define fanPeltier_DM_RES_UP          PIN_DM_RES_UP
#define fanPeltier_DM_RES_DWN         PIN_DM_RES_DWN
#define fanPeltier_DM_OD_LO           PIN_DM_OD_LO
#define fanPeltier_DM_OD_HI           PIN_DM_OD_HI
#define fanPeltier_DM_STRONG          PIN_DM_STRONG
#define fanPeltier_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define fanPeltier_MASK               fanPeltier__MASK
#define fanPeltier_SHIFT              fanPeltier__SHIFT
#define fanPeltier_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define fanPeltier_PS                     (* (reg8 *) fanPeltier__PS)
/* Data Register */
#define fanPeltier_DR                     (* (reg8 *) fanPeltier__DR)
/* Port Number */
#define fanPeltier_PRT_NUM                (* (reg8 *) fanPeltier__PRT) 
/* Connect to Analog Globals */                                                  
#define fanPeltier_AG                     (* (reg8 *) fanPeltier__AG)                       
/* Analog MUX bux enable */
#define fanPeltier_AMUX                   (* (reg8 *) fanPeltier__AMUX) 
/* Bidirectional Enable */                                                        
#define fanPeltier_BIE                    (* (reg8 *) fanPeltier__BIE)
/* Bit-mask for Aliased Register Access */
#define fanPeltier_BIT_MASK               (* (reg8 *) fanPeltier__BIT_MASK)
/* Bypass Enable */
#define fanPeltier_BYP                    (* (reg8 *) fanPeltier__BYP)
/* Port wide control signals */                                                   
#define fanPeltier_CTL                    (* (reg8 *) fanPeltier__CTL)
/* Drive Modes */
#define fanPeltier_DM0                    (* (reg8 *) fanPeltier__DM0) 
#define fanPeltier_DM1                    (* (reg8 *) fanPeltier__DM1)
#define fanPeltier_DM2                    (* (reg8 *) fanPeltier__DM2) 
/* Input Buffer Disable Override */
#define fanPeltier_INP_DIS                (* (reg8 *) fanPeltier__INP_DIS)
/* LCD Common or Segment Drive */
#define fanPeltier_LCD_COM_SEG            (* (reg8 *) fanPeltier__LCD_COM_SEG)
/* Enable Segment LCD */
#define fanPeltier_LCD_EN                 (* (reg8 *) fanPeltier__LCD_EN)
/* Slew Rate Control */
#define fanPeltier_SLW                    (* (reg8 *) fanPeltier__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define fanPeltier_PRTDSI__CAPS_SEL       (* (reg8 *) fanPeltier__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define fanPeltier_PRTDSI__DBL_SYNC_IN    (* (reg8 *) fanPeltier__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define fanPeltier_PRTDSI__OE_SEL0        (* (reg8 *) fanPeltier__PRTDSI__OE_SEL0) 
#define fanPeltier_PRTDSI__OE_SEL1        (* (reg8 *) fanPeltier__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define fanPeltier_PRTDSI__OUT_SEL0       (* (reg8 *) fanPeltier__PRTDSI__OUT_SEL0) 
#define fanPeltier_PRTDSI__OUT_SEL1       (* (reg8 *) fanPeltier__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define fanPeltier_PRTDSI__SYNC_OUT       (* (reg8 *) fanPeltier__PRTDSI__SYNC_OUT) 


#if defined(fanPeltier__INTSTAT)  /* Interrupt Registers */

    #define fanPeltier_INTSTAT                (* (reg8 *) fanPeltier__INTSTAT)
    #define fanPeltier_SNAP                   (* (reg8 *) fanPeltier__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_fanPeltier_H */


/* [] END OF FILE */
