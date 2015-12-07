/*******************************************************************************
* File Name: TurbidoISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_TurbidoISR_H)
#define CY_ISR_TurbidoISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void TurbidoISR_Start(void);
void TurbidoISR_StartEx(cyisraddress address);
void TurbidoISR_Stop(void);

CY_ISR_PROTO(TurbidoISR_Interrupt);

void TurbidoISR_SetVector(cyisraddress address);
cyisraddress TurbidoISR_GetVector(void);

void TurbidoISR_SetPriority(uint8 priority);
uint8 TurbidoISR_GetPriority(void);

void TurbidoISR_Enable(void);
uint8 TurbidoISR_GetState(void);
void TurbidoISR_Disable(void);

void TurbidoISR_SetPending(void);
void TurbidoISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the TurbidoISR ISR. */
#define TurbidoISR_INTC_VECTOR            ((reg32 *) TurbidoISR__INTC_VECT)

/* Address of the TurbidoISR ISR priority. */
#define TurbidoISR_INTC_PRIOR             ((reg8 *) TurbidoISR__INTC_PRIOR_REG)

/* Priority of the TurbidoISR interrupt. */
#define TurbidoISR_INTC_PRIOR_NUMBER      TurbidoISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable TurbidoISR interrupt. */
#define TurbidoISR_INTC_SET_EN            ((reg32 *) TurbidoISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the TurbidoISR interrupt. */
#define TurbidoISR_INTC_CLR_EN            ((reg32 *) TurbidoISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the TurbidoISR interrupt state to pending. */
#define TurbidoISR_INTC_SET_PD            ((reg32 *) TurbidoISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the TurbidoISR interrupt. */
#define TurbidoISR_INTC_CLR_PD            ((reg32 *) TurbidoISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_TurbidoISR_H */


/* [] END OF FILE */
