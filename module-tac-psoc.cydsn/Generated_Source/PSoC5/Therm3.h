/*******************************************************************************
* File Name: Therm3.h  
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

#if !defined(CY_PINS_Therm3_H) /* Pins Therm3_H */
#define CY_PINS_Therm3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Therm3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Therm3__PORT == 15 && ((Therm3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Therm3_Write(uint8 value) ;
void    Therm3_SetDriveMode(uint8 mode) ;
uint8   Therm3_ReadDataReg(void) ;
uint8   Therm3_Read(void) ;
uint8   Therm3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Therm3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Therm3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Therm3_DM_RES_UP          PIN_DM_RES_UP
#define Therm3_DM_RES_DWN         PIN_DM_RES_DWN
#define Therm3_DM_OD_LO           PIN_DM_OD_LO
#define Therm3_DM_OD_HI           PIN_DM_OD_HI
#define Therm3_DM_STRONG          PIN_DM_STRONG
#define Therm3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Therm3_MASK               Therm3__MASK
#define Therm3_SHIFT              Therm3__SHIFT
#define Therm3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Therm3_PS                     (* (reg8 *) Therm3__PS)
/* Data Register */
#define Therm3_DR                     (* (reg8 *) Therm3__DR)
/* Port Number */
#define Therm3_PRT_NUM                (* (reg8 *) Therm3__PRT) 
/* Connect to Analog Globals */                                                  
#define Therm3_AG                     (* (reg8 *) Therm3__AG)                       
/* Analog MUX bux enable */
#define Therm3_AMUX                   (* (reg8 *) Therm3__AMUX) 
/* Bidirectional Enable */                                                        
#define Therm3_BIE                    (* (reg8 *) Therm3__BIE)
/* Bit-mask for Aliased Register Access */
#define Therm3_BIT_MASK               (* (reg8 *) Therm3__BIT_MASK)
/* Bypass Enable */
#define Therm3_BYP                    (* (reg8 *) Therm3__BYP)
/* Port wide control signals */                                                   
#define Therm3_CTL                    (* (reg8 *) Therm3__CTL)
/* Drive Modes */
#define Therm3_DM0                    (* (reg8 *) Therm3__DM0) 
#define Therm3_DM1                    (* (reg8 *) Therm3__DM1)
#define Therm3_DM2                    (* (reg8 *) Therm3__DM2) 
/* Input Buffer Disable Override */
#define Therm3_INP_DIS                (* (reg8 *) Therm3__INP_DIS)
/* LCD Common or Segment Drive */
#define Therm3_LCD_COM_SEG            (* (reg8 *) Therm3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Therm3_LCD_EN                 (* (reg8 *) Therm3__LCD_EN)
/* Slew Rate Control */
#define Therm3_SLW                    (* (reg8 *) Therm3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Therm3_PRTDSI__CAPS_SEL       (* (reg8 *) Therm3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Therm3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Therm3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Therm3_PRTDSI__OE_SEL0        (* (reg8 *) Therm3__PRTDSI__OE_SEL0) 
#define Therm3_PRTDSI__OE_SEL1        (* (reg8 *) Therm3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Therm3_PRTDSI__OUT_SEL0       (* (reg8 *) Therm3__PRTDSI__OUT_SEL0) 
#define Therm3_PRTDSI__OUT_SEL1       (* (reg8 *) Therm3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Therm3_PRTDSI__SYNC_OUT       (* (reg8 *) Therm3__PRTDSI__SYNC_OUT) 


#if defined(Therm3__INTSTAT)  /* Interrupt Registers */

    #define Therm3_INTSTAT                (* (reg8 *) Therm3__INTSTAT)
    #define Therm3_SNAP                   (* (reg8 *) Therm3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Therm3_H */


/* [] END OF FILE */
