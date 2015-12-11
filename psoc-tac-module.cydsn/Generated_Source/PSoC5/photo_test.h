/*******************************************************************************
* File Name: photo_test.h  
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

#if !defined(CY_PINS_photo_test_H) /* Pins photo_test_H */
#define CY_PINS_photo_test_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "photo_test_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 photo_test__PORT == 15 && ((photo_test__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    photo_test_Write(uint8 value) ;
void    photo_test_SetDriveMode(uint8 mode) ;
uint8   photo_test_ReadDataReg(void) ;
uint8   photo_test_Read(void) ;
uint8   photo_test_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define photo_test_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define photo_test_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define photo_test_DM_RES_UP          PIN_DM_RES_UP
#define photo_test_DM_RES_DWN         PIN_DM_RES_DWN
#define photo_test_DM_OD_LO           PIN_DM_OD_LO
#define photo_test_DM_OD_HI           PIN_DM_OD_HI
#define photo_test_DM_STRONG          PIN_DM_STRONG
#define photo_test_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define photo_test_MASK               photo_test__MASK
#define photo_test_SHIFT              photo_test__SHIFT
#define photo_test_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define photo_test_PS                     (* (reg8 *) photo_test__PS)
/* Data Register */
#define photo_test_DR                     (* (reg8 *) photo_test__DR)
/* Port Number */
#define photo_test_PRT_NUM                (* (reg8 *) photo_test__PRT) 
/* Connect to Analog Globals */                                                  
#define photo_test_AG                     (* (reg8 *) photo_test__AG)                       
/* Analog MUX bux enable */
#define photo_test_AMUX                   (* (reg8 *) photo_test__AMUX) 
/* Bidirectional Enable */                                                        
#define photo_test_BIE                    (* (reg8 *) photo_test__BIE)
/* Bit-mask for Aliased Register Access */
#define photo_test_BIT_MASK               (* (reg8 *) photo_test__BIT_MASK)
/* Bypass Enable */
#define photo_test_BYP                    (* (reg8 *) photo_test__BYP)
/* Port wide control signals */                                                   
#define photo_test_CTL                    (* (reg8 *) photo_test__CTL)
/* Drive Modes */
#define photo_test_DM0                    (* (reg8 *) photo_test__DM0) 
#define photo_test_DM1                    (* (reg8 *) photo_test__DM1)
#define photo_test_DM2                    (* (reg8 *) photo_test__DM2) 
/* Input Buffer Disable Override */
#define photo_test_INP_DIS                (* (reg8 *) photo_test__INP_DIS)
/* LCD Common or Segment Drive */
#define photo_test_LCD_COM_SEG            (* (reg8 *) photo_test__LCD_COM_SEG)
/* Enable Segment LCD */
#define photo_test_LCD_EN                 (* (reg8 *) photo_test__LCD_EN)
/* Slew Rate Control */
#define photo_test_SLW                    (* (reg8 *) photo_test__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define photo_test_PRTDSI__CAPS_SEL       (* (reg8 *) photo_test__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define photo_test_PRTDSI__DBL_SYNC_IN    (* (reg8 *) photo_test__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define photo_test_PRTDSI__OE_SEL0        (* (reg8 *) photo_test__PRTDSI__OE_SEL0) 
#define photo_test_PRTDSI__OE_SEL1        (* (reg8 *) photo_test__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define photo_test_PRTDSI__OUT_SEL0       (* (reg8 *) photo_test__PRTDSI__OUT_SEL0) 
#define photo_test_PRTDSI__OUT_SEL1       (* (reg8 *) photo_test__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define photo_test_PRTDSI__SYNC_OUT       (* (reg8 *) photo_test__PRTDSI__SYNC_OUT) 


#if defined(photo_test__INTSTAT)  /* Interrupt Registers */

    #define photo_test_INTSTAT                (* (reg8 *) photo_test__INTSTAT)
    #define photo_test_SNAP                   (* (reg8 *) photo_test__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_photo_test_H */


/* [] END OF FILE */
