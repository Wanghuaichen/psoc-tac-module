/*******************************************************************************
* File Name: Peltier2_Ctrl.h  
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

#if !defined(CY_CONTROL_REG_Peltier2_Ctrl_H) /* CY_CONTROL_REG_Peltier2_Ctrl_H */
#define CY_CONTROL_REG_Peltier2_Ctrl_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} Peltier2_Ctrl_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Peltier2_Ctrl_Write(uint8 control) ;
uint8   Peltier2_Ctrl_Read(void) ;

void Peltier2_Ctrl_SaveConfig(void) ;
void Peltier2_Ctrl_RestoreConfig(void) ;
void Peltier2_Ctrl_Sleep(void) ; 
void Peltier2_Ctrl_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Peltier2_Ctrl_Control        (* (reg8 *) Peltier2_Ctrl_Sync_ctrl_reg__CONTROL_REG )
#define Peltier2_Ctrl_Control_PTR    (  (reg8 *) Peltier2_Ctrl_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Peltier2_Ctrl_H */


/* [] END OF FILE */
