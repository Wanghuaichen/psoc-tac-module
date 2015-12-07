/*******************************************************************************
* File Name: Therm4.h  
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

#if !defined(CY_PINS_Therm4_H) /* Pins Therm4_H */
#define CY_PINS_Therm4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Therm4_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Therm4__PORT == 15 && ((Therm4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Therm4_Write(uint8 value) ;
void    Therm4_SetDriveMode(uint8 mode) ;
uint8   Therm4_ReadDataReg(void) ;
uint8   Therm4_Read(void) ;
uint8   Therm4_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Therm4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Therm4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Therm4_DM_RES_UP          PIN_DM_RES_UP
#define Therm4_DM_RES_DWN         PIN_DM_RES_DWN
#define Therm4_DM_OD_LO           PIN_DM_OD_LO
#define Therm4_DM_OD_HI           PIN_DM_OD_HI
#define Therm4_DM_STRONG          PIN_DM_STRONG
#define Therm4_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Therm4_MASK               Therm4__MASK
#define Therm4_SHIFT              Therm4__SHIFT
#define Therm4_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Therm4_PS                     (* (reg8 *) Therm4__PS)
/* Data Register */
#define Therm4_DR                     (* (reg8 *) Therm4__DR)
/* Port Number */
#define Therm4_PRT_NUM                (* (reg8 *) Therm4__PRT) 
/* Connect to Analog Globals */                                                  
#define Therm4_AG                     (* (reg8 *) Therm4__AG)                       
/* Analog MUX bux enable */
#define Therm4_AMUX                   (* (reg8 *) Therm4__AMUX) 
/* Bidirectional Enable */                                                        
#define Therm4_BIE                    (* (reg8 *) Therm4__BIE)
/* Bit-mask for Aliased Register Access */
#define Therm4_BIT_MASK               (* (reg8 *) Therm4__BIT_MASK)
/* Bypass Enable */
#define Therm4_BYP                    (* (reg8 *) Therm4__BYP)
/* Port wide control signals */                                                   
#define Therm4_CTL                    (* (reg8 *) Therm4__CTL)
/* Drive Modes */
#define Therm4_DM0                    (* (reg8 *) Therm4__DM0) 
#define Therm4_DM1                    (* (reg8 *) Therm4__DM1)
#define Therm4_DM2                    (* (reg8 *) Therm4__DM2) 
/* Input Buffer Disable Override */
#define Therm4_INP_DIS                (* (reg8 *) Therm4__INP_DIS)
/* LCD Common or Segment Drive */
#define Therm4_LCD_COM_SEG            (* (reg8 *) Therm4__LCD_COM_SEG)
/* Enable Segment LCD */
#define Therm4_LCD_EN                 (* (reg8 *) Therm4__LCD_EN)
/* Slew Rate Control */
#define Therm4_SLW                    (* (reg8 *) Therm4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Therm4_PRTDSI__CAPS_SEL       (* (reg8 *) Therm4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Therm4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Therm4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Therm4_PRTDSI__OE_SEL0        (* (reg8 *) Therm4__PRTDSI__OE_SEL0) 
#define Therm4_PRTDSI__OE_SEL1        (* (reg8 *) Therm4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Therm4_PRTDSI__OUT_SEL0       (* (reg8 *) Therm4__PRTDSI__OUT_SEL0) 
#define Therm4_PRTDSI__OUT_SEL1       (* (reg8 *) Therm4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Therm4_PRTDSI__SYNC_OUT       (* (reg8 *) Therm4__PRTDSI__SYNC_OUT) 


#if defined(Therm4__INTSTAT)  /* Interrupt Registers */

    #define Therm4_INTSTAT                (* (reg8 *) Therm4__INTSTAT)
    #define Therm4_SNAP                   (* (reg8 *) Therm4__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Therm4_H */


/* [] END OF FILE */
