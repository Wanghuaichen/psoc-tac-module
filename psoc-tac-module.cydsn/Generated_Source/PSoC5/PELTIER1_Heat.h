/*******************************************************************************
* File Name: PELTIER1_Heat.h  
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

#if !defined(CY_PINS_PELTIER1_Heat_H) /* Pins PELTIER1_Heat_H */
#define CY_PINS_PELTIER1_Heat_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PELTIER1_Heat_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PELTIER1_Heat__PORT == 15 && ((PELTIER1_Heat__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PELTIER1_Heat_Write(uint8 value) ;
void    PELTIER1_Heat_SetDriveMode(uint8 mode) ;
uint8   PELTIER1_Heat_ReadDataReg(void) ;
uint8   PELTIER1_Heat_Read(void) ;
uint8   PELTIER1_Heat_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PELTIER1_Heat_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PELTIER1_Heat_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PELTIER1_Heat_DM_RES_UP          PIN_DM_RES_UP
#define PELTIER1_Heat_DM_RES_DWN         PIN_DM_RES_DWN
#define PELTIER1_Heat_DM_OD_LO           PIN_DM_OD_LO
#define PELTIER1_Heat_DM_OD_HI           PIN_DM_OD_HI
#define PELTIER1_Heat_DM_STRONG          PIN_DM_STRONG
#define PELTIER1_Heat_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PELTIER1_Heat_MASK               PELTIER1_Heat__MASK
#define PELTIER1_Heat_SHIFT              PELTIER1_Heat__SHIFT
#define PELTIER1_Heat_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PELTIER1_Heat_PS                     (* (reg8 *) PELTIER1_Heat__PS)
/* Data Register */
#define PELTIER1_Heat_DR                     (* (reg8 *) PELTIER1_Heat__DR)
/* Port Number */
#define PELTIER1_Heat_PRT_NUM                (* (reg8 *) PELTIER1_Heat__PRT) 
/* Connect to Analog Globals */                                                  
#define PELTIER1_Heat_AG                     (* (reg8 *) PELTIER1_Heat__AG)                       
/* Analog MUX bux enable */
#define PELTIER1_Heat_AMUX                   (* (reg8 *) PELTIER1_Heat__AMUX) 
/* Bidirectional Enable */                                                        
#define PELTIER1_Heat_BIE                    (* (reg8 *) PELTIER1_Heat__BIE)
/* Bit-mask for Aliased Register Access */
#define PELTIER1_Heat_BIT_MASK               (* (reg8 *) PELTIER1_Heat__BIT_MASK)
/* Bypass Enable */
#define PELTIER1_Heat_BYP                    (* (reg8 *) PELTIER1_Heat__BYP)
/* Port wide control signals */                                                   
#define PELTIER1_Heat_CTL                    (* (reg8 *) PELTIER1_Heat__CTL)
/* Drive Modes */
#define PELTIER1_Heat_DM0                    (* (reg8 *) PELTIER1_Heat__DM0) 
#define PELTIER1_Heat_DM1                    (* (reg8 *) PELTIER1_Heat__DM1)
#define PELTIER1_Heat_DM2                    (* (reg8 *) PELTIER1_Heat__DM2) 
/* Input Buffer Disable Override */
#define PELTIER1_Heat_INP_DIS                (* (reg8 *) PELTIER1_Heat__INP_DIS)
/* LCD Common or Segment Drive */
#define PELTIER1_Heat_LCD_COM_SEG            (* (reg8 *) PELTIER1_Heat__LCD_COM_SEG)
/* Enable Segment LCD */
#define PELTIER1_Heat_LCD_EN                 (* (reg8 *) PELTIER1_Heat__LCD_EN)
/* Slew Rate Control */
#define PELTIER1_Heat_SLW                    (* (reg8 *) PELTIER1_Heat__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PELTIER1_Heat_PRTDSI__CAPS_SEL       (* (reg8 *) PELTIER1_Heat__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PELTIER1_Heat_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PELTIER1_Heat__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PELTIER1_Heat_PRTDSI__OE_SEL0        (* (reg8 *) PELTIER1_Heat__PRTDSI__OE_SEL0) 
#define PELTIER1_Heat_PRTDSI__OE_SEL1        (* (reg8 *) PELTIER1_Heat__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PELTIER1_Heat_PRTDSI__OUT_SEL0       (* (reg8 *) PELTIER1_Heat__PRTDSI__OUT_SEL0) 
#define PELTIER1_Heat_PRTDSI__OUT_SEL1       (* (reg8 *) PELTIER1_Heat__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PELTIER1_Heat_PRTDSI__SYNC_OUT       (* (reg8 *) PELTIER1_Heat__PRTDSI__SYNC_OUT) 


#if defined(PELTIER1_Heat__INTSTAT)  /* Interrupt Registers */

    #define PELTIER1_Heat_INTSTAT                (* (reg8 *) PELTIER1_Heat__INTSTAT)
    #define PELTIER1_Heat_SNAP                   (* (reg8 *) PELTIER1_Heat__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PELTIER1_Heat_H */


/* [] END OF FILE */
