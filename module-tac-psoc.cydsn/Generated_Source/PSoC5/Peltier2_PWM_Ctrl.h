/*******************************************************************************
* File Name: Peltier2_PWM_Ctrl.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_Peltier2_PWM_Ctrl_H)
#define CY_PWM_Peltier2_PWM_Ctrl_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Peltier2_PWM_Ctrl_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Peltier2_PWM_Ctrl_Resolution                     (16u)
#define Peltier2_PWM_Ctrl_UsingFixedFunction             (0u)
#define Peltier2_PWM_Ctrl_DeadBandMode                   (0u)
#define Peltier2_PWM_Ctrl_KillModeMinTime                (0u)
#define Peltier2_PWM_Ctrl_KillMode                       (0u)
#define Peltier2_PWM_Ctrl_PWMMode                        (0u)
#define Peltier2_PWM_Ctrl_PWMModeIsCenterAligned         (0u)
#define Peltier2_PWM_Ctrl_DeadBandUsed                   (0u)
#define Peltier2_PWM_Ctrl_DeadBand2_4                    (0u)

#if !defined(Peltier2_PWM_Ctrl_PWMUDB_genblk8_stsreg__REMOVED)
    #define Peltier2_PWM_Ctrl_UseStatus                  (1u)
#else
    #define Peltier2_PWM_Ctrl_UseStatus                  (0u)
#endif /* !defined(Peltier2_PWM_Ctrl_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Peltier2_PWM_Ctrl_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Peltier2_PWM_Ctrl_UseControl                 (1u)
#else
    #define Peltier2_PWM_Ctrl_UseControl                 (0u)
#endif /* !defined(Peltier2_PWM_Ctrl_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Peltier2_PWM_Ctrl_UseOneCompareMode              (1u)
#define Peltier2_PWM_Ctrl_MinimumKillTime                (1u)
#define Peltier2_PWM_Ctrl_EnableMode                     (0u)

#define Peltier2_PWM_Ctrl_CompareMode1SW                 (0u)
#define Peltier2_PWM_Ctrl_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Peltier2_PWM_Ctrl__B_PWM__DISABLED 0
#define Peltier2_PWM_Ctrl__B_PWM__ASYNCHRONOUS 1
#define Peltier2_PWM_Ctrl__B_PWM__SINGLECYCLE 2
#define Peltier2_PWM_Ctrl__B_PWM__LATCHED 3
#define Peltier2_PWM_Ctrl__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Peltier2_PWM_Ctrl__B_PWM__DBMDISABLED 0
#define Peltier2_PWM_Ctrl__B_PWM__DBM_2_4_CLOCKS 1
#define Peltier2_PWM_Ctrl__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Peltier2_PWM_Ctrl__B_PWM__ONE_OUTPUT 0
#define Peltier2_PWM_Ctrl__B_PWM__TWO_OUTPUTS 1
#define Peltier2_PWM_Ctrl__B_PWM__DUAL_EDGE 2
#define Peltier2_PWM_Ctrl__B_PWM__CENTER_ALIGN 3
#define Peltier2_PWM_Ctrl__B_PWM__DITHER 5
#define Peltier2_PWM_Ctrl__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Peltier2_PWM_Ctrl__B_PWM__LESS_THAN 1
#define Peltier2_PWM_Ctrl__B_PWM__LESS_THAN_OR_EQUAL 2
#define Peltier2_PWM_Ctrl__B_PWM__GREATER_THAN 3
#define Peltier2_PWM_Ctrl__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Peltier2_PWM_Ctrl__B_PWM__EQUAL 0
#define Peltier2_PWM_Ctrl__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Peltier2_PWM_Ctrl_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Peltier2_PWM_Ctrl_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Peltier2_PWM_Ctrl_PWMModeIsCenterAligned) */
        #if (Peltier2_PWM_Ctrl_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Peltier2_PWM_Ctrl_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Peltier2_PWM_Ctrl_DeadBandMode == Peltier2_PWM_Ctrl__B_PWM__DBM_256_CLOCKS || \
            Peltier2_PWM_Ctrl_DeadBandMode == Peltier2_PWM_Ctrl__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Peltier2_PWM_Ctrl_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Peltier2_PWM_Ctrl_KillModeMinTime) */

        /* Backup control register */
        #if(Peltier2_PWM_Ctrl_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Peltier2_PWM_Ctrl_UseControl) */

    #endif /* (!Peltier2_PWM_Ctrl_UsingFixedFunction) */

}Peltier2_PWM_Ctrl_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Peltier2_PWM_Ctrl_Start(void) ;
void    Peltier2_PWM_Ctrl_Stop(void) ;

#if (Peltier2_PWM_Ctrl_UseStatus || Peltier2_PWM_Ctrl_UsingFixedFunction)
    void  Peltier2_PWM_Ctrl_SetInterruptMode(uint8 interruptMode) ;
    uint8 Peltier2_PWM_Ctrl_ReadStatusRegister(void) ;
#endif /* (Peltier2_PWM_Ctrl_UseStatus || Peltier2_PWM_Ctrl_UsingFixedFunction) */

#define Peltier2_PWM_Ctrl_GetInterruptSource() Peltier2_PWM_Ctrl_ReadStatusRegister()

#if (Peltier2_PWM_Ctrl_UseControl)
    uint8 Peltier2_PWM_Ctrl_ReadControlRegister(void) ;
    void  Peltier2_PWM_Ctrl_WriteControlRegister(uint8 control)
          ;
#endif /* (Peltier2_PWM_Ctrl_UseControl) */

#if (Peltier2_PWM_Ctrl_UseOneCompareMode)
   #if (Peltier2_PWM_Ctrl_CompareMode1SW)
       void    Peltier2_PWM_Ctrl_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Peltier2_PWM_Ctrl_CompareMode1SW) */
#else
    #if (Peltier2_PWM_Ctrl_CompareMode1SW)
        void    Peltier2_PWM_Ctrl_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Peltier2_PWM_Ctrl_CompareMode1SW) */
    #if (Peltier2_PWM_Ctrl_CompareMode2SW)
        void    Peltier2_PWM_Ctrl_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Peltier2_PWM_Ctrl_CompareMode2SW) */
#endif /* (Peltier2_PWM_Ctrl_UseOneCompareMode) */

#if (!Peltier2_PWM_Ctrl_UsingFixedFunction)
    uint16   Peltier2_PWM_Ctrl_ReadCounter(void) ;
    uint16 Peltier2_PWM_Ctrl_ReadCapture(void) ;

    #if (Peltier2_PWM_Ctrl_UseStatus)
            void Peltier2_PWM_Ctrl_ClearFIFO(void) ;
    #endif /* (Peltier2_PWM_Ctrl_UseStatus) */

    void    Peltier2_PWM_Ctrl_WriteCounter(uint16 counter)
            ;
#endif /* (!Peltier2_PWM_Ctrl_UsingFixedFunction) */

void    Peltier2_PWM_Ctrl_WritePeriod(uint16 period)
        ;
uint16 Peltier2_PWM_Ctrl_ReadPeriod(void) ;

#if (Peltier2_PWM_Ctrl_UseOneCompareMode)
    void    Peltier2_PWM_Ctrl_WriteCompare(uint16 compare)
            ;
    uint16 Peltier2_PWM_Ctrl_ReadCompare(void) ;
#else
    void    Peltier2_PWM_Ctrl_WriteCompare1(uint16 compare)
            ;
    uint16 Peltier2_PWM_Ctrl_ReadCompare1(void) ;
    void    Peltier2_PWM_Ctrl_WriteCompare2(uint16 compare)
            ;
    uint16 Peltier2_PWM_Ctrl_ReadCompare2(void) ;
#endif /* (Peltier2_PWM_Ctrl_UseOneCompareMode) */


#if (Peltier2_PWM_Ctrl_DeadBandUsed)
    void    Peltier2_PWM_Ctrl_WriteDeadTime(uint8 deadtime) ;
    uint8   Peltier2_PWM_Ctrl_ReadDeadTime(void) ;
#endif /* (Peltier2_PWM_Ctrl_DeadBandUsed) */

#if ( Peltier2_PWM_Ctrl_KillModeMinTime)
    void Peltier2_PWM_Ctrl_WriteKillTime(uint8 killtime) ;
    uint8 Peltier2_PWM_Ctrl_ReadKillTime(void) ;
#endif /* ( Peltier2_PWM_Ctrl_KillModeMinTime) */

void Peltier2_PWM_Ctrl_Init(void) ;
void Peltier2_PWM_Ctrl_Enable(void) ;
void Peltier2_PWM_Ctrl_Sleep(void) ;
void Peltier2_PWM_Ctrl_Wakeup(void) ;
void Peltier2_PWM_Ctrl_SaveConfig(void) ;
void Peltier2_PWM_Ctrl_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Peltier2_PWM_Ctrl_INIT_PERIOD_VALUE          (299u)
#define Peltier2_PWM_Ctrl_INIT_COMPARE_VALUE1        (1u)
#define Peltier2_PWM_Ctrl_INIT_COMPARE_VALUE2        (63u)
#define Peltier2_PWM_Ctrl_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Peltier2_PWM_Ctrl_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Peltier2_PWM_Ctrl_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Peltier2_PWM_Ctrl_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Peltier2_PWM_Ctrl_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Peltier2_PWM_Ctrl_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Peltier2_PWM_Ctrl_CTRL_CMPMODE2_SHIFT)
#define Peltier2_PWM_Ctrl_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Peltier2_PWM_Ctrl_CTRL_CMPMODE1_SHIFT)
#define Peltier2_PWM_Ctrl_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Peltier2_PWM_Ctrl_UsingFixedFunction)
   #define Peltier2_PWM_Ctrl_PERIOD_LSB              (*(reg16 *) Peltier2_PWM_Ctrl_PWMHW__PER0)
   #define Peltier2_PWM_Ctrl_PERIOD_LSB_PTR          ( (reg16 *) Peltier2_PWM_Ctrl_PWMHW__PER0)
   #define Peltier2_PWM_Ctrl_COMPARE1_LSB            (*(reg16 *) Peltier2_PWM_Ctrl_PWMHW__CNT_CMP0)
   #define Peltier2_PWM_Ctrl_COMPARE1_LSB_PTR        ( (reg16 *) Peltier2_PWM_Ctrl_PWMHW__CNT_CMP0)
   #define Peltier2_PWM_Ctrl_COMPARE2_LSB            (0x00u)
   #define Peltier2_PWM_Ctrl_COMPARE2_LSB_PTR        (0x00u)
   #define Peltier2_PWM_Ctrl_COUNTER_LSB             (*(reg16 *) Peltier2_PWM_Ctrl_PWMHW__CNT_CMP0)
   #define Peltier2_PWM_Ctrl_COUNTER_LSB_PTR         ( (reg16 *) Peltier2_PWM_Ctrl_PWMHW__CNT_CMP0)
   #define Peltier2_PWM_Ctrl_CAPTURE_LSB             (*(reg16 *) Peltier2_PWM_Ctrl_PWMHW__CAP0)
   #define Peltier2_PWM_Ctrl_CAPTURE_LSB_PTR         ( (reg16 *) Peltier2_PWM_Ctrl_PWMHW__CAP0)
   #define Peltier2_PWM_Ctrl_RT1                     (*(reg8 *)  Peltier2_PWM_Ctrl_PWMHW__RT1)
   #define Peltier2_PWM_Ctrl_RT1_PTR                 ( (reg8 *)  Peltier2_PWM_Ctrl_PWMHW__RT1)

#else
   #if (Peltier2_PWM_Ctrl_Resolution == 8u) /* 8bit - PWM */

       #if(Peltier2_PWM_Ctrl_PWMModeIsCenterAligned)
           #define Peltier2_PWM_Ctrl_PERIOD_LSB      (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Peltier2_PWM_Ctrl_PERIOD_LSB_PTR  ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Peltier2_PWM_Ctrl_PERIOD_LSB      (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Peltier2_PWM_Ctrl_PERIOD_LSB_PTR  ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Peltier2_PWM_Ctrl_PWMModeIsCenterAligned) */

       #define Peltier2_PWM_Ctrl_COMPARE1_LSB        (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Peltier2_PWM_Ctrl_COMPARE1_LSB_PTR    ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Peltier2_PWM_Ctrl_COMPARE2_LSB        (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Peltier2_PWM_Ctrl_COMPARE2_LSB_PTR    ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Peltier2_PWM_Ctrl_COUNTERCAP_LSB      (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Peltier2_PWM_Ctrl_COUNTERCAP_LSB_PTR  ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Peltier2_PWM_Ctrl_COUNTER_LSB         (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Peltier2_PWM_Ctrl_COUNTER_LSB_PTR     ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Peltier2_PWM_Ctrl_CAPTURE_LSB         (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Peltier2_PWM_Ctrl_CAPTURE_LSB_PTR     ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Peltier2_PWM_Ctrl_PWMModeIsCenterAligned)
               #define Peltier2_PWM_Ctrl_PERIOD_LSB      (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Peltier2_PWM_Ctrl_PERIOD_LSB_PTR  ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Peltier2_PWM_Ctrl_PERIOD_LSB      (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Peltier2_PWM_Ctrl_PERIOD_LSB_PTR  ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Peltier2_PWM_Ctrl_PWMModeIsCenterAligned) */

            #define Peltier2_PWM_Ctrl_COMPARE1_LSB       (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Peltier2_PWM_Ctrl_COMPARE1_LSB_PTR   ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Peltier2_PWM_Ctrl_COMPARE2_LSB       (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Peltier2_PWM_Ctrl_COMPARE2_LSB_PTR   ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Peltier2_PWM_Ctrl_COUNTERCAP_LSB     (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Peltier2_PWM_Ctrl_COUNTERCAP_LSB_PTR ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Peltier2_PWM_Ctrl_COUNTER_LSB        (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Peltier2_PWM_Ctrl_COUNTER_LSB_PTR    ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Peltier2_PWM_Ctrl_CAPTURE_LSB        (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Peltier2_PWM_Ctrl_CAPTURE_LSB_PTR    ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Peltier2_PWM_Ctrl_PWMModeIsCenterAligned)
               #define Peltier2_PWM_Ctrl_PERIOD_LSB      (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Peltier2_PWM_Ctrl_PERIOD_LSB_PTR  ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Peltier2_PWM_Ctrl_PERIOD_LSB      (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Peltier2_PWM_Ctrl_PERIOD_LSB_PTR  ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Peltier2_PWM_Ctrl_PWMModeIsCenterAligned) */

            #define Peltier2_PWM_Ctrl_COMPARE1_LSB       (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Peltier2_PWM_Ctrl_COMPARE1_LSB_PTR   ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Peltier2_PWM_Ctrl_COMPARE2_LSB       (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Peltier2_PWM_Ctrl_COMPARE2_LSB_PTR   ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Peltier2_PWM_Ctrl_COUNTERCAP_LSB     (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Peltier2_PWM_Ctrl_COUNTERCAP_LSB_PTR ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Peltier2_PWM_Ctrl_COUNTER_LSB        (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Peltier2_PWM_Ctrl_COUNTER_LSB_PTR    ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Peltier2_PWM_Ctrl_CAPTURE_LSB        (*(reg16 *) Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Peltier2_PWM_Ctrl_CAPTURE_LSB_PTR    ((reg16 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Peltier2_PWM_Ctrl_AUX_CONTROLDP1          (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Peltier2_PWM_Ctrl_AUX_CONTROLDP1_PTR      ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Peltier2_PWM_Ctrl_Resolution == 8) */

   #define Peltier2_PWM_Ctrl_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Peltier2_PWM_Ctrl_AUX_CONTROLDP0          (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Peltier2_PWM_Ctrl_AUX_CONTROLDP0_PTR      ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Peltier2_PWM_Ctrl_UsingFixedFunction) */

#if(Peltier2_PWM_Ctrl_KillModeMinTime )
    #define Peltier2_PWM_Ctrl_KILLMODEMINTIME        (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Peltier2_PWM_Ctrl_KILLMODEMINTIME_PTR    ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Peltier2_PWM_Ctrl_KillModeMinTime ) */

#if(Peltier2_PWM_Ctrl_DeadBandMode == Peltier2_PWM_Ctrl__B_PWM__DBM_256_CLOCKS)
    #define Peltier2_PWM_Ctrl_DEADBAND_COUNT         (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Peltier2_PWM_Ctrl_DEADBAND_COUNT_PTR     ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Peltier2_PWM_Ctrl_DEADBAND_LSB_PTR       ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Peltier2_PWM_Ctrl_DEADBAND_LSB           (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Peltier2_PWM_Ctrl_DeadBandMode == Peltier2_PWM_Ctrl__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Peltier2_PWM_Ctrl_UsingFixedFunction)
        #define Peltier2_PWM_Ctrl_DEADBAND_COUNT         (*(reg8 *)  Peltier2_PWM_Ctrl_PWMHW__CFG0)
        #define Peltier2_PWM_Ctrl_DEADBAND_COUNT_PTR     ((reg8 *)   Peltier2_PWM_Ctrl_PWMHW__CFG0)
        #define Peltier2_PWM_Ctrl_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Peltier2_PWM_Ctrl_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Peltier2_PWM_Ctrl_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Peltier2_PWM_Ctrl_DEADBAND_COUNT         (*(reg8 *)  Peltier2_PWM_Ctrl_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Peltier2_PWM_Ctrl_DEADBAND_COUNT_PTR     ((reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Peltier2_PWM_Ctrl_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Peltier2_PWM_Ctrl_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Peltier2_PWM_Ctrl_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Peltier2_PWM_Ctrl_UsingFixedFunction) */
#endif /* (Peltier2_PWM_Ctrl_DeadBandMode == Peltier2_PWM_Ctrl__B_PWM__DBM_256_CLOCKS) */



#if (Peltier2_PWM_Ctrl_UsingFixedFunction)
    #define Peltier2_PWM_Ctrl_STATUS                 (*(reg8 *) Peltier2_PWM_Ctrl_PWMHW__SR0)
    #define Peltier2_PWM_Ctrl_STATUS_PTR             ((reg8 *) Peltier2_PWM_Ctrl_PWMHW__SR0)
    #define Peltier2_PWM_Ctrl_STATUS_MASK            (*(reg8 *) Peltier2_PWM_Ctrl_PWMHW__SR0)
    #define Peltier2_PWM_Ctrl_STATUS_MASK_PTR        ((reg8 *) Peltier2_PWM_Ctrl_PWMHW__SR0)
    #define Peltier2_PWM_Ctrl_CONTROL                (*(reg8 *) Peltier2_PWM_Ctrl_PWMHW__CFG0)
    #define Peltier2_PWM_Ctrl_CONTROL_PTR            ((reg8 *) Peltier2_PWM_Ctrl_PWMHW__CFG0)
    #define Peltier2_PWM_Ctrl_CONTROL2               (*(reg8 *) Peltier2_PWM_Ctrl_PWMHW__CFG1)
    #define Peltier2_PWM_Ctrl_CONTROL3               (*(reg8 *) Peltier2_PWM_Ctrl_PWMHW__CFG2)
    #define Peltier2_PWM_Ctrl_GLOBAL_ENABLE          (*(reg8 *) Peltier2_PWM_Ctrl_PWMHW__PM_ACT_CFG)
    #define Peltier2_PWM_Ctrl_GLOBAL_ENABLE_PTR      ( (reg8 *) Peltier2_PWM_Ctrl_PWMHW__PM_ACT_CFG)
    #define Peltier2_PWM_Ctrl_GLOBAL_STBY_ENABLE     (*(reg8 *) Peltier2_PWM_Ctrl_PWMHW__PM_STBY_CFG)
    #define Peltier2_PWM_Ctrl_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Peltier2_PWM_Ctrl_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Peltier2_PWM_Ctrl_BLOCK_EN_MASK          (Peltier2_PWM_Ctrl_PWMHW__PM_ACT_MSK)
    #define Peltier2_PWM_Ctrl_BLOCK_STBY_EN_MASK     (Peltier2_PWM_Ctrl_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Peltier2_PWM_Ctrl_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Peltier2_PWM_Ctrl_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Peltier2_PWM_Ctrl_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Peltier2_PWM_Ctrl_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Peltier2_PWM_Ctrl_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Peltier2_PWM_Ctrl_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Peltier2_PWM_Ctrl_CTRL_ENABLE            (uint8)((uint8)0x01u << Peltier2_PWM_Ctrl_CTRL_ENABLE_SHIFT)
    #define Peltier2_PWM_Ctrl_CTRL_RESET             (uint8)((uint8)0x01u << Peltier2_PWM_Ctrl_CTRL_RESET_SHIFT)
    #define Peltier2_PWM_Ctrl_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Peltier2_PWM_Ctrl_CTRL_CMPMODE2_SHIFT)
    #define Peltier2_PWM_Ctrl_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Peltier2_PWM_Ctrl_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Peltier2_PWM_Ctrl_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Peltier2_PWM_Ctrl_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Peltier2_PWM_Ctrl_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Peltier2_PWM_Ctrl_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Peltier2_PWM_Ctrl_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Peltier2_PWM_Ctrl_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Peltier2_PWM_Ctrl_STATUS_TC_INT_EN_MASK_SHIFT            (Peltier2_PWM_Ctrl_STATUS_TC_SHIFT - 4u)
    #define Peltier2_PWM_Ctrl_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Peltier2_PWM_Ctrl_STATUS_CMP1_INT_EN_MASK_SHIFT          (Peltier2_PWM_Ctrl_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Peltier2_PWM_Ctrl_STATUS_TC              (uint8)((uint8)0x01u << Peltier2_PWM_Ctrl_STATUS_TC_SHIFT)
    #define Peltier2_PWM_Ctrl_STATUS_CMP1            (uint8)((uint8)0x01u << Peltier2_PWM_Ctrl_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Peltier2_PWM_Ctrl_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Peltier2_PWM_Ctrl_STATUS_TC >> 4u)
    #define Peltier2_PWM_Ctrl_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Peltier2_PWM_Ctrl_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Peltier2_PWM_Ctrl_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Peltier2_PWM_Ctrl_RT1_MASK              (uint8)((uint8)0x03u << Peltier2_PWM_Ctrl_RT1_SHIFT)
    #define Peltier2_PWM_Ctrl_SYNC                  (uint8)((uint8)0x03u << Peltier2_PWM_Ctrl_RT1_SHIFT)
    #define Peltier2_PWM_Ctrl_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Peltier2_PWM_Ctrl_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Peltier2_PWM_Ctrl_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Peltier2_PWM_Ctrl_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Peltier2_PWM_Ctrl_SYNCDSI_SHIFT)


#else
    #define Peltier2_PWM_Ctrl_STATUS                (*(reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Peltier2_PWM_Ctrl_STATUS_PTR            ((reg8 *)    Peltier2_PWM_Ctrl_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Peltier2_PWM_Ctrl_STATUS_MASK           (*(reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Peltier2_PWM_Ctrl_STATUS_MASK_PTR       ((reg8 *)    Peltier2_PWM_Ctrl_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Peltier2_PWM_Ctrl_STATUS_AUX_CTRL       (*(reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Peltier2_PWM_Ctrl_CONTROL               (*(reg8 *)   Peltier2_PWM_Ctrl_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Peltier2_PWM_Ctrl_CONTROL_PTR           ((reg8 *)    Peltier2_PWM_Ctrl_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Peltier2_PWM_Ctrl_CTRL_ENABLE_SHIFT      (0x07u)
    #define Peltier2_PWM_Ctrl_CTRL_RESET_SHIFT       (0x06u)
    #define Peltier2_PWM_Ctrl_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Peltier2_PWM_Ctrl_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Peltier2_PWM_Ctrl_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Peltier2_PWM_Ctrl_CTRL_ENABLE            (uint8)((uint8)0x01u << Peltier2_PWM_Ctrl_CTRL_ENABLE_SHIFT)
    #define Peltier2_PWM_Ctrl_CTRL_RESET             (uint8)((uint8)0x01u << Peltier2_PWM_Ctrl_CTRL_RESET_SHIFT)
    #define Peltier2_PWM_Ctrl_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Peltier2_PWM_Ctrl_CTRL_CMPMODE2_SHIFT)
    #define Peltier2_PWM_Ctrl_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Peltier2_PWM_Ctrl_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Peltier2_PWM_Ctrl_STATUS_KILL_SHIFT          (0x05u)
    #define Peltier2_PWM_Ctrl_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Peltier2_PWM_Ctrl_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Peltier2_PWM_Ctrl_STATUS_TC_SHIFT            (0x02u)
    #define Peltier2_PWM_Ctrl_STATUS_CMP2_SHIFT          (0x01u)
    #define Peltier2_PWM_Ctrl_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Peltier2_PWM_Ctrl_STATUS_KILL_INT_EN_MASK_SHIFT          (Peltier2_PWM_Ctrl_STATUS_KILL_SHIFT)
    #define Peltier2_PWM_Ctrl_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Peltier2_PWM_Ctrl_STATUS_FIFONEMPTY_SHIFT)
    #define Peltier2_PWM_Ctrl_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Peltier2_PWM_Ctrl_STATUS_FIFOFULL_SHIFT)
    #define Peltier2_PWM_Ctrl_STATUS_TC_INT_EN_MASK_SHIFT            (Peltier2_PWM_Ctrl_STATUS_TC_SHIFT)
    #define Peltier2_PWM_Ctrl_STATUS_CMP2_INT_EN_MASK_SHIFT          (Peltier2_PWM_Ctrl_STATUS_CMP2_SHIFT)
    #define Peltier2_PWM_Ctrl_STATUS_CMP1_INT_EN_MASK_SHIFT          (Peltier2_PWM_Ctrl_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Peltier2_PWM_Ctrl_STATUS_KILL            (uint8)((uint8)0x00u << Peltier2_PWM_Ctrl_STATUS_KILL_SHIFT )
    #define Peltier2_PWM_Ctrl_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Peltier2_PWM_Ctrl_STATUS_FIFOFULL_SHIFT)
    #define Peltier2_PWM_Ctrl_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Peltier2_PWM_Ctrl_STATUS_FIFONEMPTY_SHIFT)
    #define Peltier2_PWM_Ctrl_STATUS_TC              (uint8)((uint8)0x01u << Peltier2_PWM_Ctrl_STATUS_TC_SHIFT)
    #define Peltier2_PWM_Ctrl_STATUS_CMP2            (uint8)((uint8)0x01u << Peltier2_PWM_Ctrl_STATUS_CMP2_SHIFT)
    #define Peltier2_PWM_Ctrl_STATUS_CMP1            (uint8)((uint8)0x01u << Peltier2_PWM_Ctrl_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Peltier2_PWM_Ctrl_STATUS_KILL_INT_EN_MASK            (Peltier2_PWM_Ctrl_STATUS_KILL)
    #define Peltier2_PWM_Ctrl_STATUS_FIFOFULL_INT_EN_MASK        (Peltier2_PWM_Ctrl_STATUS_FIFOFULL)
    #define Peltier2_PWM_Ctrl_STATUS_FIFONEMPTY_INT_EN_MASK      (Peltier2_PWM_Ctrl_STATUS_FIFONEMPTY)
    #define Peltier2_PWM_Ctrl_STATUS_TC_INT_EN_MASK              (Peltier2_PWM_Ctrl_STATUS_TC)
    #define Peltier2_PWM_Ctrl_STATUS_CMP2_INT_EN_MASK            (Peltier2_PWM_Ctrl_STATUS_CMP2)
    #define Peltier2_PWM_Ctrl_STATUS_CMP1_INT_EN_MASK            (Peltier2_PWM_Ctrl_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Peltier2_PWM_Ctrl_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Peltier2_PWM_Ctrl_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Peltier2_PWM_Ctrl_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Peltier2_PWM_Ctrl_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Peltier2_PWM_Ctrl_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Peltier2_PWM_Ctrl_UsingFixedFunction */

#endif  /* CY_PWM_Peltier2_PWM_Ctrl_H */


/* [] END OF FILE */
