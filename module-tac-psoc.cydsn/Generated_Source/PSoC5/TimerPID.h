/*******************************************************************************
* File Name: TimerPID.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_TimerPID_H)
#define CY_Timer_v2_60_TimerPID_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 TimerPID_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define TimerPID_Resolution                 24u
#define TimerPID_UsingFixedFunction         0u
#define TimerPID_UsingHWCaptureCounter      0u
#define TimerPID_SoftwareCaptureMode        0u
#define TimerPID_SoftwareTriggerMode        0u
#define TimerPID_UsingHWEnable              0u
#define TimerPID_EnableTriggerMode          0u
#define TimerPID_InterruptOnCaptureCount    0u
#define TimerPID_RunModeUsed                0u
#define TimerPID_ControlRegRemoved          0u

#if defined(TimerPID_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define TimerPID_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (TimerPID_UsingFixedFunction)
    #define TimerPID_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define TimerPID_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End TimerPID_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!TimerPID_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (TimerPID_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!TimerPID_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}TimerPID_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    TimerPID_Start(void) ;
void    TimerPID_Stop(void) ;

void    TimerPID_SetInterruptMode(uint8 interruptMode) ;
uint8   TimerPID_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define TimerPID_GetInterruptSource() TimerPID_ReadStatusRegister()

#if(!TimerPID_UDB_CONTROL_REG_REMOVED)
    uint8   TimerPID_ReadControlRegister(void) ;
    void    TimerPID_WriteControlRegister(uint8 control) ;
#endif /* (!TimerPID_UDB_CONTROL_REG_REMOVED) */

uint32  TimerPID_ReadPeriod(void) ;
void    TimerPID_WritePeriod(uint32 period) ;
uint32  TimerPID_ReadCounter(void) ;
void    TimerPID_WriteCounter(uint32 counter) ;
uint32  TimerPID_ReadCapture(void) ;
void    TimerPID_SoftwareCapture(void) ;

#if(!TimerPID_UsingFixedFunction) /* UDB Prototypes */
    #if (TimerPID_SoftwareCaptureMode)
        void    TimerPID_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!TimerPID_UsingFixedFunction) */

    #if (TimerPID_SoftwareTriggerMode)
        void    TimerPID_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (TimerPID_SoftwareTriggerMode) */

    #if (TimerPID_EnableTriggerMode)
        void    TimerPID_EnableTrigger(void) ;
        void    TimerPID_DisableTrigger(void) ;
    #endif /* (TimerPID_EnableTriggerMode) */


    #if(TimerPID_InterruptOnCaptureCount)
        void    TimerPID_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (TimerPID_InterruptOnCaptureCount) */

    #if (TimerPID_UsingHWCaptureCounter)
        void    TimerPID_SetCaptureCount(uint8 captureCount) ;
        uint8   TimerPID_ReadCaptureCount(void) ;
    #endif /* (TimerPID_UsingHWCaptureCounter) */

    void TimerPID_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void TimerPID_Init(void)          ;
void TimerPID_Enable(void)        ;
void TimerPID_SaveConfig(void)    ;
void TimerPID_RestoreConfig(void) ;
void TimerPID_Sleep(void)         ;
void TimerPID_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define TimerPID__B_TIMER__CM_NONE 0
#define TimerPID__B_TIMER__CM_RISINGEDGE 1
#define TimerPID__B_TIMER__CM_FALLINGEDGE 2
#define TimerPID__B_TIMER__CM_EITHEREDGE 3
#define TimerPID__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define TimerPID__B_TIMER__TM_NONE 0x00u
#define TimerPID__B_TIMER__TM_RISINGEDGE 0x04u
#define TimerPID__B_TIMER__TM_FALLINGEDGE 0x08u
#define TimerPID__B_TIMER__TM_EITHEREDGE 0x0Cu
#define TimerPID__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define TimerPID_INIT_PERIOD             11999999u
#define TimerPID_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << TimerPID_CTRL_CAP_MODE_SHIFT))
#define TimerPID_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << TimerPID_CTRL_TRIG_MODE_SHIFT))
#if (TimerPID_UsingFixedFunction)
    #define TimerPID_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << TimerPID_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << TimerPID_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define TimerPID_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << TimerPID_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerPID_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerPID_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (TimerPID_UsingFixedFunction) */
#define TimerPID_INIT_CAPTURE_COUNT      (2u)
#define TimerPID_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << TimerPID_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (TimerPID_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define TimerPID_STATUS         (*(reg8 *) TimerPID_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define TimerPID_STATUS_MASK    (*(reg8 *) TimerPID_TimerHW__SR0 )
    #define TimerPID_CONTROL        (*(reg8 *) TimerPID_TimerHW__CFG0)
    #define TimerPID_CONTROL2       (*(reg8 *) TimerPID_TimerHW__CFG1)
    #define TimerPID_CONTROL2_PTR   ( (reg8 *) TimerPID_TimerHW__CFG1)
    #define TimerPID_RT1            (*(reg8 *) TimerPID_TimerHW__RT1)
    #define TimerPID_RT1_PTR        ( (reg8 *) TimerPID_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define TimerPID_CONTROL3       (*(reg8 *) TimerPID_TimerHW__CFG2)
        #define TimerPID_CONTROL3_PTR   ( (reg8 *) TimerPID_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define TimerPID_GLOBAL_ENABLE  (*(reg8 *) TimerPID_TimerHW__PM_ACT_CFG)
    #define TimerPID_GLOBAL_STBY_ENABLE  (*(reg8 *) TimerPID_TimerHW__PM_STBY_CFG)

    #define TimerPID_CAPTURE_LSB         (* (reg16 *) TimerPID_TimerHW__CAP0 )
    #define TimerPID_CAPTURE_LSB_PTR       ((reg16 *) TimerPID_TimerHW__CAP0 )
    #define TimerPID_PERIOD_LSB          (* (reg16 *) TimerPID_TimerHW__PER0 )
    #define TimerPID_PERIOD_LSB_PTR        ((reg16 *) TimerPID_TimerHW__PER0 )
    #define TimerPID_COUNTER_LSB         (* (reg16 *) TimerPID_TimerHW__CNT_CMP0 )
    #define TimerPID_COUNTER_LSB_PTR       ((reg16 *) TimerPID_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define TimerPID_BLOCK_EN_MASK                     TimerPID_TimerHW__PM_ACT_MSK
    #define TimerPID_BLOCK_STBY_EN_MASK                TimerPID_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define TimerPID_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define TimerPID_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define TimerPID_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define TimerPID_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define TimerPID_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define TimerPID_CTRL_ENABLE                        ((uint8)((uint8)0x01u << TimerPID_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TimerPID_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define TimerPID_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << TimerPID_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define TimerPID_CTRL_MODE_SHIFT                 0x01u
        #define TimerPID_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << TimerPID_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define TimerPID_CTRL_RCOD_SHIFT        0x02u
        #define TimerPID_CTRL_ENBL_SHIFT        0x00u
        #define TimerPID_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define TimerPID_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << TimerPID_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define TimerPID_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << TimerPID_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define TimerPID_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << TimerPID_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define TimerPID_CTRL_RCOD       ((uint8)((uint8)0x03u << TimerPID_CTRL_RCOD_SHIFT))
        #define TimerPID_CTRL_ENBL       ((uint8)((uint8)0x80u << TimerPID_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define TimerPID_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define TimerPID_RT1_MASK                        ((uint8)((uint8)0x03u << TimerPID_RT1_SHIFT))
    #define TimerPID_SYNC                            ((uint8)((uint8)0x03u << TimerPID_RT1_SHIFT))
    #define TimerPID_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define TimerPID_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << TimerPID_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define TimerPID_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << TimerPID_SYNCDSI_SHIFT))

    #define TimerPID_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << TimerPID_CTRL_MODE_SHIFT))
    #define TimerPID_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << TimerPID_CTRL_MODE_SHIFT))
    #define TimerPID_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << TimerPID_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerPID_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerPID_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerPID_STATUS_TC_INT_MASK_SHIFT        (TimerPID_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerPID_STATUS_CAPTURE_INT_MASK_SHIFT   (TimerPID_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define TimerPID_STATUS_TC                       ((uint8)((uint8)0x01u << TimerPID_STATUS_TC_SHIFT))
    #define TimerPID_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << TimerPID_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define TimerPID_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << TimerPID_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define TimerPID_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << TimerPID_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define TimerPID_STATUS              (* (reg8 *) TimerPID_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define TimerPID_STATUS_MASK         (* (reg8 *) TimerPID_TimerUDB_rstSts_stsreg__MASK_REG)
    #define TimerPID_STATUS_AUX_CTRL     (* (reg8 *) TimerPID_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define TimerPID_CONTROL             (* (reg8 *) TimerPID_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(TimerPID_Resolution <= 8u) /* 8-bit Timer */
        #define TimerPID_CAPTURE_LSB         (* (reg8 *) TimerPID_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define TimerPID_CAPTURE_LSB_PTR       ((reg8 *) TimerPID_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define TimerPID_PERIOD_LSB          (* (reg8 *) TimerPID_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define TimerPID_PERIOD_LSB_PTR        ((reg8 *) TimerPID_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define TimerPID_COUNTER_LSB         (* (reg8 *) TimerPID_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define TimerPID_COUNTER_LSB_PTR       ((reg8 *) TimerPID_TimerUDB_sT24_timerdp_u0__A0_REG )
    #elif(TimerPID_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define TimerPID_CAPTURE_LSB         (* (reg16 *) TimerPID_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define TimerPID_CAPTURE_LSB_PTR       ((reg16 *) TimerPID_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define TimerPID_PERIOD_LSB          (* (reg16 *) TimerPID_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define TimerPID_PERIOD_LSB_PTR        ((reg16 *) TimerPID_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define TimerPID_COUNTER_LSB         (* (reg16 *) TimerPID_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define TimerPID_COUNTER_LSB_PTR       ((reg16 *) TimerPID_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define TimerPID_CAPTURE_LSB         (* (reg16 *) TimerPID_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define TimerPID_CAPTURE_LSB_PTR       ((reg16 *) TimerPID_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define TimerPID_PERIOD_LSB          (* (reg16 *) TimerPID_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define TimerPID_PERIOD_LSB_PTR        ((reg16 *) TimerPID_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define TimerPID_COUNTER_LSB         (* (reg16 *) TimerPID_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
            #define TimerPID_COUNTER_LSB_PTR       ((reg16 *) TimerPID_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(TimerPID_Resolution <= 24u)/* 24-bit Timer */
        #define TimerPID_CAPTURE_LSB         (* (reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define TimerPID_CAPTURE_LSB_PTR       ((reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define TimerPID_PERIOD_LSB          (* (reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define TimerPID_PERIOD_LSB_PTR        ((reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define TimerPID_COUNTER_LSB         (* (reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define TimerPID_COUNTER_LSB_PTR       ((reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define TimerPID_CAPTURE_LSB         (* (reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define TimerPID_CAPTURE_LSB_PTR       ((reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define TimerPID_PERIOD_LSB          (* (reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define TimerPID_PERIOD_LSB_PTR        ((reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define TimerPID_COUNTER_LSB         (* (reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define TimerPID_COUNTER_LSB_PTR       ((reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define TimerPID_CAPTURE_LSB         (* (reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define TimerPID_CAPTURE_LSB_PTR       ((reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define TimerPID_PERIOD_LSB          (* (reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define TimerPID_PERIOD_LSB_PTR        ((reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define TimerPID_COUNTER_LSB         (* (reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
            #define TimerPID_COUNTER_LSB_PTR       ((reg32 *) TimerPID_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define TimerPID_COUNTER_LSB_PTR_8BIT       ((reg8 *) TimerPID_TimerUDB_sT24_timerdp_u0__A0_REG )
    
    #if (TimerPID_UsingHWCaptureCounter)
        #define TimerPID_CAP_COUNT              (*(reg8 *) TimerPID_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerPID_CAP_COUNT_PTR          ( (reg8 *) TimerPID_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerPID_CAPTURE_COUNT_CTRL     (*(reg8 *) TimerPID_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define TimerPID_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) TimerPID_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (TimerPID_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define TimerPID_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define TimerPID_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define TimerPID_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define TimerPID_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define TimerPID_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define TimerPID_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << TimerPID_CTRL_INTCNT_SHIFT))
    #define TimerPID_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << TimerPID_CTRL_TRIG_MODE_SHIFT))
    #define TimerPID_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << TimerPID_CTRL_TRIG_EN_SHIFT))
    #define TimerPID_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << TimerPID_CTRL_CAP_MODE_SHIFT))
    #define TimerPID_CTRL_ENABLE                    ((uint8)((uint8)0x01u << TimerPID_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define TimerPID_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define TimerPID_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define TimerPID_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define TimerPID_STATUS_TC_INT_MASK_SHIFT       TimerPID_STATUS_TC_SHIFT
    #define TimerPID_STATUS_CAPTURE_INT_MASK_SHIFT  TimerPID_STATUS_CAPTURE_SHIFT
    #define TimerPID_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define TimerPID_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define TimerPID_STATUS_FIFOFULL_INT_MASK_SHIFT TimerPID_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define TimerPID_STATUS_TC                      ((uint8)((uint8)0x01u << TimerPID_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define TimerPID_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << TimerPID_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerPID_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << TimerPID_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerPID_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << TimerPID_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define TimerPID_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << TimerPID_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define TimerPID_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << TimerPID_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerPID_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << TimerPID_STATUS_FIFOFULL_SHIFT))

    #define TimerPID_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define TimerPID_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define TimerPID_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define TimerPID_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define TimerPID_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define TimerPID_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_TimerPID_H */


/* [] END OF FILE */
