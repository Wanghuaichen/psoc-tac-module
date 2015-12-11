/*******************************************************************************
* File Name: peltier_control.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_peltier_control_H) /* CY_CONTROL_REG_peltier_control_H */
#define CY_CONTROL_REG_peltier_control_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} peltier_control_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    peltier_control_Write(uint8 control) ;
uint8   peltier_control_Read(void) ;

void peltier_control_SaveConfig(void) ;
void peltier_control_RestoreConfig(void) ;
void peltier_control_Sleep(void) ; 
void peltier_control_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define peltier_control_Control        (* (reg8 *) peltier_control_Sync_ctrl_reg__CONTROL_REG )
#define peltier_control_Control_PTR    (  (reg8 *) peltier_control_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_peltier_control_H */


/* [] END OF FILE */
