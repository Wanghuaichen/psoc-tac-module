/*******************************************************************************
* File Name: Therm1.h  
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

#if !defined(CY_PINS_Therm1_H) /* Pins Therm1_H */
#define CY_PINS_Therm1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Therm1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Therm1__PORT == 15 && ((Therm1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Therm1_Write(uint8 value) ;
void    Therm1_SetDriveMode(uint8 mode) ;
uint8   Therm1_ReadDataReg(void) ;
uint8   Therm1_Read(void) ;
uint8   Therm1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Therm1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Therm1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Therm1_DM_RES_UP          PIN_DM_RES_UP
#define Therm1_DM_RES_DWN         PIN_DM_RES_DWN
#define Therm1_DM_OD_LO           PIN_DM_OD_LO
#define Therm1_DM_OD_HI           PIN_DM_OD_HI
#define Therm1_DM_STRONG          PIN_DM_STRONG
#define Therm1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Therm1_MASK               Therm1__MASK
#define Therm1_SHIFT              Therm1__SHIFT
#define Therm1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Therm1_PS                     (* (reg8 *) Therm1__PS)
/* Data Register */
#define Therm1_DR                     (* (reg8 *) Therm1__DR)
/* Port Number */
#define Therm1_PRT_NUM                (* (reg8 *) Therm1__PRT) 
/* Connect to Analog Globals */                                                  
#define Therm1_AG                     (* (reg8 *) Therm1__AG)                       
/* Analog MUX bux enable */
#define Therm1_AMUX                   (* (reg8 *) Therm1__AMUX) 
/* Bidirectional Enable */                                                        
#define Therm1_BIE                    (* (reg8 *) Therm1__BIE)
/* Bit-mask for Aliased Register Access */
#define Therm1_BIT_MASK               (* (reg8 *) Therm1__BIT_MASK)
/* Bypass Enable */
#define Therm1_BYP                    (* (reg8 *) Therm1__BYP)
/* Port wide control signals */                                                   
#define Therm1_CTL                    (* (reg8 *) Therm1__CTL)
/* Drive Modes */
#define Therm1_DM0                    (* (reg8 *) Therm1__DM0) 
#define Therm1_DM1                    (* (reg8 *) Therm1__DM1)
#define Therm1_DM2                    (* (reg8 *) Therm1__DM2) 
/* Input Buffer Disable Override */
#define Therm1_INP_DIS                (* (reg8 *) Therm1__INP_DIS)
/* LCD Common or Segment Drive */
#define Therm1_LCD_COM_SEG            (* (reg8 *) Therm1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Therm1_LCD_EN                 (* (reg8 *) Therm1__LCD_EN)
/* Slew Rate Control */
#define Therm1_SLW                    (* (reg8 *) Therm1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Therm1_PRTDSI__CAPS_SEL       (* (reg8 *) Therm1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Therm1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Therm1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Therm1_PRTDSI__OE_SEL0        (* (reg8 *) Therm1__PRTDSI__OE_SEL0) 
#define Therm1_PRTDSI__OE_SEL1        (* (reg8 *) Therm1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Therm1_PRTDSI__OUT_SEL0       (* (reg8 *) Therm1__PRTDSI__OUT_SEL0) 
#define Therm1_PRTDSI__OUT_SEL1       (* (reg8 *) Therm1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Therm1_PRTDSI__SYNC_OUT       (* (reg8 *) Therm1__PRTDSI__SYNC_OUT) 


#if defined(Therm1__INTSTAT)  /* Interrupt Registers */

    #define Therm1_INTSTAT                (* (reg8 *) Therm1__INTSTAT)
    #define Therm1_SNAP                   (* (reg8 *) Therm1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Therm1_H */


/* [] END OF FILE */
