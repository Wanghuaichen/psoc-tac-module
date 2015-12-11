/*******************************************************************************
* File Name: PELTIER2_Heat.h  
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

#if !defined(CY_PINS_PELTIER2_Heat_H) /* Pins PELTIER2_Heat_H */
#define CY_PINS_PELTIER2_Heat_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PELTIER2_Heat_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PELTIER2_Heat__PORT == 15 && ((PELTIER2_Heat__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PELTIER2_Heat_Write(uint8 value) ;
void    PELTIER2_Heat_SetDriveMode(uint8 mode) ;
uint8   PELTIER2_Heat_ReadDataReg(void) ;
uint8   PELTIER2_Heat_Read(void) ;
uint8   PELTIER2_Heat_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PELTIER2_Heat_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PELTIER2_Heat_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PELTIER2_Heat_DM_RES_UP          PIN_DM_RES_UP
#define PELTIER2_Heat_DM_RES_DWN         PIN_DM_RES_DWN
#define PELTIER2_Heat_DM_OD_LO           PIN_DM_OD_LO
#define PELTIER2_Heat_DM_OD_HI           PIN_DM_OD_HI
#define PELTIER2_Heat_DM_STRONG          PIN_DM_STRONG
#define PELTIER2_Heat_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PELTIER2_Heat_MASK               PELTIER2_Heat__MASK
#define PELTIER2_Heat_SHIFT              PELTIER2_Heat__SHIFT
#define PELTIER2_Heat_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PELTIER2_Heat_PS                     (* (reg8 *) PELTIER2_Heat__PS)
/* Data Register */
#define PELTIER2_Heat_DR                     (* (reg8 *) PELTIER2_Heat__DR)
/* Port Number */
#define PELTIER2_Heat_PRT_NUM                (* (reg8 *) PELTIER2_Heat__PRT) 
/* Connect to Analog Globals */                                                  
#define PELTIER2_Heat_AG                     (* (reg8 *) PELTIER2_Heat__AG)                       
/* Analog MUX bux enable */
#define PELTIER2_Heat_AMUX                   (* (reg8 *) PELTIER2_Heat__AMUX) 
/* Bidirectional Enable */                                                        
#define PELTIER2_Heat_BIE                    (* (reg8 *) PELTIER2_Heat__BIE)
/* Bit-mask for Aliased Register Access */
#define PELTIER2_Heat_BIT_MASK               (* (reg8 *) PELTIER2_Heat__BIT_MASK)
/* Bypass Enable */
#define PELTIER2_Heat_BYP                    (* (reg8 *) PELTIER2_Heat__BYP)
/* Port wide control signals */                                                   
#define PELTIER2_Heat_CTL                    (* (reg8 *) PELTIER2_Heat__CTL)
/* Drive Modes */
#define PELTIER2_Heat_DM0                    (* (reg8 *) PELTIER2_Heat__DM0) 
#define PELTIER2_Heat_DM1                    (* (reg8 *) PELTIER2_Heat__DM1)
#define PELTIER2_Heat_DM2                    (* (reg8 *) PELTIER2_Heat__DM2) 
/* Input Buffer Disable Override */
#define PELTIER2_Heat_INP_DIS                (* (reg8 *) PELTIER2_Heat__INP_DIS)
/* LCD Common or Segment Drive */
#define PELTIER2_Heat_LCD_COM_SEG            (* (reg8 *) PELTIER2_Heat__LCD_COM_SEG)
/* Enable Segment LCD */
#define PELTIER2_Heat_LCD_EN                 (* (reg8 *) PELTIER2_Heat__LCD_EN)
/* Slew Rate Control */
#define PELTIER2_Heat_SLW                    (* (reg8 *) PELTIER2_Heat__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PELTIER2_Heat_PRTDSI__CAPS_SEL       (* (reg8 *) PELTIER2_Heat__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PELTIER2_Heat_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PELTIER2_Heat__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PELTIER2_Heat_PRTDSI__OE_SEL0        (* (reg8 *) PELTIER2_Heat__PRTDSI__OE_SEL0) 
#define PELTIER2_Heat_PRTDSI__OE_SEL1        (* (reg8 *) PELTIER2_Heat__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PELTIER2_Heat_PRTDSI__OUT_SEL0       (* (reg8 *) PELTIER2_Heat__PRTDSI__OUT_SEL0) 
#define PELTIER2_Heat_PRTDSI__OUT_SEL1       (* (reg8 *) PELTIER2_Heat__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PELTIER2_Heat_PRTDSI__SYNC_OUT       (* (reg8 *) PELTIER2_Heat__PRTDSI__SYNC_OUT) 


#if defined(PELTIER2_Heat__INTSTAT)  /* Interrupt Registers */

    #define PELTIER2_Heat_INTSTAT                (* (reg8 *) PELTIER2_Heat__INTSTAT)
    #define PELTIER2_Heat_SNAP                   (* (reg8 *) PELTIER2_Heat__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PELTIER2_Heat_H */


/* [] END OF FILE */
