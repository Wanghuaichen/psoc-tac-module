/*******************************************************************************
* File Name: peltierPWM.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "peltierPWM.h"

/* Error message for removed <resource> through optimization */
#ifdef peltierPWM_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* peltierPWM_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 peltierPWM_initVar = 0u;


/*******************************************************************************
* Function Name: peltierPWM_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  peltierPWM_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void peltierPWM_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(peltierPWM_initVar == 0u)
    {
        peltierPWM_Init();
        peltierPWM_initVar = 1u;
    }
    peltierPWM_Enable();

}


/*******************************************************************************
* Function Name: peltierPWM_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  peltierPWM_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void peltierPWM_Init(void) 
{
    #if (peltierPWM_UsingFixedFunction || peltierPWM_UseControl)
        uint8 ctrl;
    #endif /* (peltierPWM_UsingFixedFunction || peltierPWM_UseControl) */

    #if(!peltierPWM_UsingFixedFunction)
        #if(peltierPWM_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 peltierPWM_interruptState;
        #endif /* (peltierPWM_UseStatus) */
    #endif /* (!peltierPWM_UsingFixedFunction) */

    #if (peltierPWM_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        peltierPWM_CONTROL |= peltierPWM_CFG0_MODE;
        #if (peltierPWM_DeadBand2_4)
            peltierPWM_CONTROL |= peltierPWM_CFG0_DB;
        #endif /* (peltierPWM_DeadBand2_4) */

        ctrl = peltierPWM_CONTROL3 & ((uint8 )(~peltierPWM_CTRL_CMPMODE1_MASK));
        peltierPWM_CONTROL3 = ctrl | peltierPWM_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        peltierPWM_RT1 &= ((uint8)(~peltierPWM_RT1_MASK));
        peltierPWM_RT1 |= peltierPWM_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        peltierPWM_RT1 &= ((uint8)(~peltierPWM_SYNCDSI_MASK));
        peltierPWM_RT1 |= peltierPWM_SYNCDSI_EN;

    #elif (peltierPWM_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = peltierPWM_CONTROL & ((uint8)(~peltierPWM_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~peltierPWM_CTRL_CMPMODE1_MASK));
        peltierPWM_CONTROL = ctrl | peltierPWM_DEFAULT_COMPARE2_MODE |
                                   peltierPWM_DEFAULT_COMPARE1_MODE;
    #endif /* (peltierPWM_UsingFixedFunction) */

    #if (!peltierPWM_UsingFixedFunction)
        #if (peltierPWM_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            peltierPWM_AUX_CONTROLDP0 |= (peltierPWM_AUX_CTRL_FIFO0_CLR);
        #else /* (peltierPWM_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            peltierPWM_AUX_CONTROLDP0 |= (peltierPWM_AUX_CTRL_FIFO0_CLR);
            peltierPWM_AUX_CONTROLDP1 |= (peltierPWM_AUX_CTRL_FIFO0_CLR);
        #endif /* (peltierPWM_Resolution == 8) */

        peltierPWM_WriteCounter(peltierPWM_INIT_PERIOD_VALUE);
    #endif /* (!peltierPWM_UsingFixedFunction) */

    peltierPWM_WritePeriod(peltierPWM_INIT_PERIOD_VALUE);

        #if (peltierPWM_UseOneCompareMode)
            peltierPWM_WriteCompare(peltierPWM_INIT_COMPARE_VALUE1);
        #else
            peltierPWM_WriteCompare1(peltierPWM_INIT_COMPARE_VALUE1);
            peltierPWM_WriteCompare2(peltierPWM_INIT_COMPARE_VALUE2);
        #endif /* (peltierPWM_UseOneCompareMode) */

        #if (peltierPWM_KillModeMinTime)
            peltierPWM_WriteKillTime(peltierPWM_MinimumKillTime);
        #endif /* (peltierPWM_KillModeMinTime) */

        #if (peltierPWM_DeadBandUsed)
            peltierPWM_WriteDeadTime(peltierPWM_INIT_DEAD_TIME);
        #endif /* (peltierPWM_DeadBandUsed) */

    #if (peltierPWM_UseStatus || peltierPWM_UsingFixedFunction)
        peltierPWM_SetInterruptMode(peltierPWM_INIT_INTERRUPTS_MODE);
    #endif /* (peltierPWM_UseStatus || peltierPWM_UsingFixedFunction) */

    #if (peltierPWM_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        peltierPWM_GLOBAL_ENABLE |= peltierPWM_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        peltierPWM_CONTROL2 |= peltierPWM_CTRL2_IRQ_SEL;
    #else
        #if(peltierPWM_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            peltierPWM_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            peltierPWM_STATUS_AUX_CTRL |= peltierPWM_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(peltierPWM_interruptState);

            /* Clear the FIFO to enable the peltierPWM_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            peltierPWM_ClearFIFO();
        #endif /* (peltierPWM_UseStatus) */
    #endif /* (peltierPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: peltierPWM_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void peltierPWM_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (peltierPWM_UsingFixedFunction)
        peltierPWM_GLOBAL_ENABLE |= peltierPWM_BLOCK_EN_MASK;
        peltierPWM_GLOBAL_STBY_ENABLE |= peltierPWM_BLOCK_STBY_EN_MASK;
    #endif /* (peltierPWM_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (peltierPWM_UseControl || peltierPWM_UsingFixedFunction)
        peltierPWM_CONTROL |= peltierPWM_CTRL_ENABLE;
    #endif /* (peltierPWM_UseControl || peltierPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: peltierPWM_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void peltierPWM_Stop(void) 
{
    #if (peltierPWM_UseControl || peltierPWM_UsingFixedFunction)
        peltierPWM_CONTROL &= ((uint8)(~peltierPWM_CTRL_ENABLE));
    #endif /* (peltierPWM_UseControl || peltierPWM_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (peltierPWM_UsingFixedFunction)
        peltierPWM_GLOBAL_ENABLE &= ((uint8)(~peltierPWM_BLOCK_EN_MASK));
        peltierPWM_GLOBAL_STBY_ENABLE &= ((uint8)(~peltierPWM_BLOCK_STBY_EN_MASK));
    #endif /* (peltierPWM_UsingFixedFunction) */
}

#if (peltierPWM_UseOneCompareMode)
    #if (peltierPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: peltierPWM_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void peltierPWM_SetCompareMode(uint8 comparemode) 
        {
            #if(peltierPWM_UsingFixedFunction)

                #if(0 != peltierPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << peltierPWM_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != peltierPWM_CTRL_CMPMODE1_SHIFT) */

                peltierPWM_CONTROL3 &= ((uint8)(~peltierPWM_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                peltierPWM_CONTROL3 |= comparemodemasked;

            #elif (peltierPWM_UseControl)

                #if(0 != peltierPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << peltierPWM_CTRL_CMPMODE1_SHIFT)) &
                                                peltierPWM_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & peltierPWM_CTRL_CMPMODE1_MASK;
                #endif /* (0 != peltierPWM_CTRL_CMPMODE1_SHIFT) */

                #if(0 != peltierPWM_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << peltierPWM_CTRL_CMPMODE2_SHIFT)) &
                                               peltierPWM_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & peltierPWM_CTRL_CMPMODE2_MASK;
                #endif /* (0 != peltierPWM_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                peltierPWM_CONTROL &= ((uint8)(~(peltierPWM_CTRL_CMPMODE1_MASK |
                                            peltierPWM_CTRL_CMPMODE2_MASK)));
                peltierPWM_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (peltierPWM_UsingFixedFunction) */
        }
    #endif /* peltierPWM_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (peltierPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: peltierPWM_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void peltierPWM_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != peltierPWM_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << peltierPWM_CTRL_CMPMODE1_SHIFT)) &
                                           peltierPWM_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & peltierPWM_CTRL_CMPMODE1_MASK;
            #endif /* (0 != peltierPWM_CTRL_CMPMODE1_SHIFT) */

            #if (peltierPWM_UseControl)
                peltierPWM_CONTROL &= ((uint8)(~peltierPWM_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                peltierPWM_CONTROL |= comparemodemasked;
            #endif /* (peltierPWM_UseControl) */
        }
    #endif /* peltierPWM_CompareMode1SW */

#if (peltierPWM_CompareMode2SW)


    /*******************************************************************************
    * Function Name: peltierPWM_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void peltierPWM_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != peltierPWM_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << peltierPWM_CTRL_CMPMODE2_SHIFT)) &
                                                 peltierPWM_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & peltierPWM_CTRL_CMPMODE2_MASK;
        #endif /* (0 != peltierPWM_CTRL_CMPMODE2_SHIFT) */

        #if (peltierPWM_UseControl)
            peltierPWM_CONTROL &= ((uint8)(~peltierPWM_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            peltierPWM_CONTROL |= comparemodemasked;
        #endif /* (peltierPWM_UseControl) */
    }
    #endif /*peltierPWM_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!peltierPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: peltierPWM_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void peltierPWM_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(peltierPWM_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: peltierPWM_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint8 peltierPWM_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(peltierPWM_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG8(peltierPWM_CAPTURE_LSB_PTR));
    }

    #if (peltierPWM_UseStatus)


        /*******************************************************************************
        * Function Name: peltierPWM_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void peltierPWM_ClearFIFO(void) 
        {
            while(0u != (peltierPWM_ReadStatusRegister() & peltierPWM_STATUS_FIFONEMPTY))
            {
                (void)peltierPWM_ReadCapture();
            }
        }

    #endif /* peltierPWM_UseStatus */

#endif /* !peltierPWM_UsingFixedFunction */


/*******************************************************************************
* Function Name: peltierPWM_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void peltierPWM_WritePeriod(uint8 period) 
{
    #if(peltierPWM_UsingFixedFunction)
        CY_SET_REG16(peltierPWM_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(peltierPWM_PERIOD_LSB_PTR, period);
    #endif /* (peltierPWM_UsingFixedFunction) */
}

#if (peltierPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: peltierPWM_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void peltierPWM_WriteCompare(uint8 compare) \
                                       
    {
        #if(peltierPWM_UsingFixedFunction)
            CY_SET_REG16(peltierPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(peltierPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (peltierPWM_UsingFixedFunction) */

        #if (peltierPWM_PWMMode == peltierPWM__B_PWM__DITHER)
            #if(peltierPWM_UsingFixedFunction)
                CY_SET_REG16(peltierPWM_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG8(peltierPWM_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (peltierPWM_UsingFixedFunction) */
        #endif /* (peltierPWM_PWMMode == peltierPWM__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: peltierPWM_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void peltierPWM_WriteCompare1(uint8 compare) \
                                        
    {
        #if(peltierPWM_UsingFixedFunction)
            CY_SET_REG16(peltierPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(peltierPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (peltierPWM_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: peltierPWM_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void peltierPWM_WriteCompare2(uint8 compare) \
                                        
    {
        #if(peltierPWM_UsingFixedFunction)
            CY_SET_REG16(peltierPWM_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(peltierPWM_COMPARE2_LSB_PTR, compare);
        #endif /* (peltierPWM_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (peltierPWM_DeadBandUsed)


    /*******************************************************************************
    * Function Name: peltierPWM_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void peltierPWM_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!peltierPWM_DeadBand2_4)
            CY_SET_REG8(peltierPWM_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            peltierPWM_DEADBAND_COUNT &= ((uint8)(~peltierPWM_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(peltierPWM_DEADBAND_COUNT_SHIFT)
                peltierPWM_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << peltierPWM_DEADBAND_COUNT_SHIFT)) &
                                                    peltierPWM_DEADBAND_COUNT_MASK;
            #else
                peltierPWM_DEADBAND_COUNT |= deadtime & peltierPWM_DEADBAND_COUNT_MASK;
            #endif /* (peltierPWM_DEADBAND_COUNT_SHIFT) */

        #endif /* (!peltierPWM_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: peltierPWM_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 peltierPWM_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!peltierPWM_DeadBand2_4)
            return (CY_GET_REG8(peltierPWM_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(peltierPWM_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(peltierPWM_DEADBAND_COUNT & peltierPWM_DEADBAND_COUNT_MASK)) >>
                                                                           peltierPWM_DEADBAND_COUNT_SHIFT));
            #else
                return (peltierPWM_DEADBAND_COUNT & peltierPWM_DEADBAND_COUNT_MASK);
            #endif /* (peltierPWM_DEADBAND_COUNT_SHIFT) */
        #endif /* (!peltierPWM_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (peltierPWM_UseStatus || peltierPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: peltierPWM_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void peltierPWM_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(peltierPWM_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: peltierPWM_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 peltierPWM_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(peltierPWM_STATUS_PTR));
    }

#endif /* (peltierPWM_UseStatus || peltierPWM_UsingFixedFunction) */


#if (peltierPWM_UseControl)


    /*******************************************************************************
    * Function Name: peltierPWM_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 peltierPWM_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(peltierPWM_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: peltierPWM_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void peltierPWM_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(peltierPWM_CONTROL_PTR, control);
    }

#endif /* (peltierPWM_UseControl) */


#if (!peltierPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: peltierPWM_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint8 peltierPWM_ReadCapture(void) 
    {
        return (CY_GET_REG8(peltierPWM_CAPTURE_LSB_PTR));
    }

#endif /* (!peltierPWM_UsingFixedFunction) */


#if (peltierPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: peltierPWM_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint8 peltierPWM_ReadCompare(void) 
    {
        #if(peltierPWM_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(peltierPWM_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(peltierPWM_COMPARE1_LSB_PTR));
        #endif /* (peltierPWM_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: peltierPWM_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 peltierPWM_ReadCompare1(void) 
    {
        return (CY_GET_REG8(peltierPWM_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: peltierPWM_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 peltierPWM_ReadCompare2(void) 
    {
        return (CY_GET_REG8(peltierPWM_COMPARE2_LSB_PTR));
    }

#endif /* (peltierPWM_UseOneCompareMode) */


/*******************************************************************************
* Function Name: peltierPWM_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint8 peltierPWM_ReadPeriod(void) 
{
    #if(peltierPWM_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(peltierPWM_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(peltierPWM_PERIOD_LSB_PTR));
    #endif /* (peltierPWM_UsingFixedFunction) */
}

#if ( peltierPWM_KillModeMinTime)


    /*******************************************************************************
    * Function Name: peltierPWM_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void peltierPWM_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(peltierPWM_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: peltierPWM_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 peltierPWM_ReadKillTime(void) 
    {
        return (CY_GET_REG8(peltierPWM_KILLMODEMINTIME_PTR));
    }

#endif /* ( peltierPWM_KillModeMinTime) */

/* [] END OF FILE */
