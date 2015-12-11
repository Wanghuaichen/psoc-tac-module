/*******************************************************************************
* File Name: PELTIER2_Cool.h  
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

#if !defined(CY_PINS_PELTIER2_Cool_H) /* Pins PELTIER2_Cool_H */
#define CY_PINS_PELTIER2_Cool_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PELTIER2_Cool_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PELTIER2_Cool__PORT == 15 && ((PELTIER2_Cool__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PELTIER2_Cool_Write(uint8 value) ;
void    PELTIER2_Cool_SetDriveMode(uint8 mode) ;
uint8   PELTIER2_Cool_ReadDataReg(void) ;
uint8   PELTIER2_Cool_Read(void) ;
uint8   PELTIER2_Cool_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PELTIER2_Cool_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PELTIER2_Cool_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PELTIER2_Cool_DM_RES_UP          PIN_DM_RES_UP
#define PELTIER2_Cool_DM_RES_DWN         PIN_DM_RES_DWN
#define PELTIER2_Cool_DM_OD_LO           PIN_DM_OD_LO
#define PELTIER2_Cool_DM_OD_HI           PIN_DM_OD_HI
#define PELTIER2_Cool_DM_STRONG          PIN_DM_STRONG
#define PELTIER2_Cool_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PELTIER2_Cool_MASK               PELTIER2_Cool__MASK
#define PELTIER2_Cool_SHIFT              PELTIER2_Cool__SHIFT
#define PELTIER2_Cool_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PELTIER2_Cool_PS                     (* (reg8 *) PELTIER2_Cool__PS)
/* Data Register */
#define PELTIER2_Cool_DR                     (* (reg8 *) PELTIER2_Cool__DR)
/* Port Number */
#define PELTIER2_Cool_PRT_NUM                (* (reg8 *) PELTIER2_Cool__PRT) 
/* Connect to Analog Globals */                                                  
#define PELTIER2_Cool_AG                     (* (reg8 *) PELTIER2_Cool__AG)                       
/* Analog MUX bux enable */
#define PELTIER2_Cool_AMUX                   (* (reg8 *) PELTIER2_Cool__AMUX) 
/* Bidirectional Enable */                                                        
#define PELTIER2_Cool_BIE                    (* (reg8 *) PELTIER2_Cool__BIE)
/* Bit-mask for Aliased Register Access */
#define PELTIER2_Cool_BIT_MASK               (* (reg8 *) PELTIER2_Cool__BIT_MASK)
/* Bypass Enable */
#define PELTIER2_Cool_BYP                    (* (reg8 *) PELTIER2_Cool__BYP)
/* Port wide control signals */                                                   
#define PELTIER2_Cool_CTL                    (* (reg8 *) PELTIER2_Cool__CTL)
/* Drive Modes */
#define PELTIER2_Cool_DM0                    (* (reg8 *) PELTIER2_Cool__DM0) 
#define PELTIER2_Cool_DM1                    (* (reg8 *) PELTIER2_Cool__DM1)
#define PELTIER2_Cool_DM2                    (* (reg8 *) PELTIER2_Cool__DM2) 
/* Input Buffer Disable Override */
#define PELTIER2_Cool_INP_DIS                (* (reg8 *) PELTIER2_Cool__INP_DIS)
/* LCD Common or Segment Drive */
#define PELTIER2_Cool_LCD_COM_SEG            (* (reg8 *) PELTIER2_Cool__LCD_COM_SEG)
/* Enable Segment LCD */
#define PELTIER2_Cool_LCD_EN                 (* (reg8 *) PELTIER2_Cool__LCD_EN)
/* Slew Rate Control */
#define PELTIER2_Cool_SLW                    (* (reg8 *) PELTIER2_Cool__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PELTIER2_Cool_PRTDSI__CAPS_SEL       (* (reg8 *) PELTIER2_Cool__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PELTIER2_Cool_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PELTIER2_Cool__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PELTIER2_Cool_PRTDSI__OE_SEL0        (* (reg8 *) PELTIER2_Cool__PRTDSI__OE_SEL0) 
#define PELTIER2_Cool_PRTDSI__OE_SEL1        (* (reg8 *) PELTIER2_Cool__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PELTIER2_Cool_PRTDSI__OUT_SEL0       (* (reg8 *) PELTIER2_Cool__PRTDSI__OUT_SEL0) 
#define PELTIER2_Cool_PRTDSI__OUT_SEL1       (* (reg8 *) PELTIER2_Cool__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PELTIER2_Cool_PRTDSI__SYNC_OUT       (* (reg8 *) PELTIER2_Cool__PRTDSI__SYNC_OUT) 


#if defined(PELTIER2_Cool__INTSTAT)  /* Interrupt Registers */

    #define PELTIER2_Cool_INTSTAT                (* (reg8 *) PELTIER2_Cool__INTSTAT)
    #define PELTIER2_Cool_SNAP                   (* (reg8 *) PELTIER2_Cool__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PELTIER2_Cool_H */


/* [] END OF FILE */
