/*******************************************************************************
* File Name: pwmFan.c
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

#include "pwmFan.h"

/* Error message for removed <resource> through optimization */
#ifdef pwmFan_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* pwmFan_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 pwmFan_initVar = 0u;


/*******************************************************************************
* Function Name: pwmFan_Start
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
*  pwmFan_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void pwmFan_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(pwmFan_initVar == 0u)
    {
        pwmFan_Init();
        pwmFan_initVar = 1u;
    }
    pwmFan_Enable();

}


/*******************************************************************************
* Function Name: pwmFan_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  pwmFan_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void pwmFan_Init(void) 
{
    #if (pwmFan_UsingFixedFunction || pwmFan_UseControl)
        uint8 ctrl;
    #endif /* (pwmFan_UsingFixedFunction || pwmFan_UseControl) */

    #if(!pwmFan_UsingFixedFunction)
        #if(pwmFan_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 pwmFan_interruptState;
        #endif /* (pwmFan_UseStatus) */
    #endif /* (!pwmFan_UsingFixedFunction) */

    #if (pwmFan_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        pwmFan_CONTROL |= pwmFan_CFG0_MODE;
        #if (pwmFan_DeadBand2_4)
            pwmFan_CONTROL |= pwmFan_CFG0_DB;
        #endif /* (pwmFan_DeadBand2_4) */

        ctrl = pwmFan_CONTROL3 & ((uint8 )(~pwmFan_CTRL_CMPMODE1_MASK));
        pwmFan_CONTROL3 = ctrl | pwmFan_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        pwmFan_RT1 &= ((uint8)(~pwmFan_RT1_MASK));
        pwmFan_RT1 |= pwmFan_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        pwmFan_RT1 &= ((uint8)(~pwmFan_SYNCDSI_MASK));
        pwmFan_RT1 |= pwmFan_SYNCDSI_EN;

    #elif (pwmFan_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = pwmFan_CONTROL & ((uint8)(~pwmFan_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~pwmFan_CTRL_CMPMODE1_MASK));
        pwmFan_CONTROL = ctrl | pwmFan_DEFAULT_COMPARE2_MODE |
                                   pwmFan_DEFAULT_COMPARE1_MODE;
    #endif /* (pwmFan_UsingFixedFunction) */

    #if (!pwmFan_UsingFixedFunction)
        #if (pwmFan_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            pwmFan_AUX_CONTROLDP0 |= (pwmFan_AUX_CTRL_FIFO0_CLR);
        #else /* (pwmFan_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            pwmFan_AUX_CONTROLDP0 |= (pwmFan_AUX_CTRL_FIFO0_CLR);
            pwmFan_AUX_CONTROLDP1 |= (pwmFan_AUX_CTRL_FIFO0_CLR);
        #endif /* (pwmFan_Resolution == 8) */

        pwmFan_WriteCounter(pwmFan_INIT_PERIOD_VALUE);
    #endif /* (!pwmFan_UsingFixedFunction) */

    pwmFan_WritePeriod(pwmFan_INIT_PERIOD_VALUE);

        #if (pwmFan_UseOneCompareMode)
            pwmFan_WriteCompare(pwmFan_INIT_COMPARE_VALUE1);
        #else
            pwmFan_WriteCompare1(pwmFan_INIT_COMPARE_VALUE1);
            pwmFan_WriteCompare2(pwmFan_INIT_COMPARE_VALUE2);
        #endif /* (pwmFan_UseOneCompareMode) */

        #if (pwmFan_KillModeMinTime)
            pwmFan_WriteKillTime(pwmFan_MinimumKillTime);
        #endif /* (pwmFan_KillModeMinTime) */

        #if (pwmFan_DeadBandUsed)
            pwmFan_WriteDeadTime(pwmFan_INIT_DEAD_TIME);
        #endif /* (pwmFan_DeadBandUsed) */

    #if (pwmFan_UseStatus || pwmFan_UsingFixedFunction)
        pwmFan_SetInterruptMode(pwmFan_INIT_INTERRUPTS_MODE);
    #endif /* (pwmFan_UseStatus || pwmFan_UsingFixedFunction) */

    #if (pwmFan_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        pwmFan_GLOBAL_ENABLE |= pwmFan_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        pwmFan_CONTROL2 |= pwmFan_CTRL2_IRQ_SEL;
    #else
        #if(pwmFan_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            pwmFan_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            pwmFan_STATUS_AUX_CTRL |= pwmFan_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(pwmFan_interruptState);

            /* Clear the FIFO to enable the pwmFan_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            pwmFan_ClearFIFO();
        #endif /* (pwmFan_UseStatus) */
    #endif /* (pwmFan_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwmFan_Enable
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
void pwmFan_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (pwmFan_UsingFixedFunction)
        pwmFan_GLOBAL_ENABLE |= pwmFan_BLOCK_EN_MASK;
        pwmFan_GLOBAL_STBY_ENABLE |= pwmFan_BLOCK_STBY_EN_MASK;
    #endif /* (pwmFan_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (pwmFan_UseControl || pwmFan_UsingFixedFunction)
        pwmFan_CONTROL |= pwmFan_CTRL_ENABLE;
    #endif /* (pwmFan_UseControl || pwmFan_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwmFan_Stop
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
void pwmFan_Stop(void) 
{
    #if (pwmFan_UseControl || pwmFan_UsingFixedFunction)
        pwmFan_CONTROL &= ((uint8)(~pwmFan_CTRL_ENABLE));
    #endif /* (pwmFan_UseControl || pwmFan_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (pwmFan_UsingFixedFunction)
        pwmFan_GLOBAL_ENABLE &= ((uint8)(~pwmFan_BLOCK_EN_MASK));
        pwmFan_GLOBAL_STBY_ENABLE &= ((uint8)(~pwmFan_BLOCK_STBY_EN_MASK));
    #endif /* (pwmFan_UsingFixedFunction) */
}

#if (pwmFan_UseOneCompareMode)
    #if (pwmFan_CompareMode1SW)


        /*******************************************************************************
        * Function Name: pwmFan_SetCompareMode
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
        void pwmFan_SetCompareMode(uint8 comparemode) 
        {
            #if(pwmFan_UsingFixedFunction)

                #if(0 != pwmFan_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << pwmFan_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != pwmFan_CTRL_CMPMODE1_SHIFT) */

                pwmFan_CONTROL3 &= ((uint8)(~pwmFan_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                pwmFan_CONTROL3 |= comparemodemasked;

            #elif (pwmFan_UseControl)

                #if(0 != pwmFan_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << pwmFan_CTRL_CMPMODE1_SHIFT)) &
                                                pwmFan_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & pwmFan_CTRL_CMPMODE1_MASK;
                #endif /* (0 != pwmFan_CTRL_CMPMODE1_SHIFT) */

                #if(0 != pwmFan_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << pwmFan_CTRL_CMPMODE2_SHIFT)) &
                                               pwmFan_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & pwmFan_CTRL_CMPMODE2_MASK;
                #endif /* (0 != pwmFan_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                pwmFan_CONTROL &= ((uint8)(~(pwmFan_CTRL_CMPMODE1_MASK |
                                            pwmFan_CTRL_CMPMODE2_MASK)));
                pwmFan_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (pwmFan_UsingFixedFunction) */
        }
    #endif /* pwmFan_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (pwmFan_CompareMode1SW)


        /*******************************************************************************
        * Function Name: pwmFan_SetCompareMode1
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
        void pwmFan_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != pwmFan_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << pwmFan_CTRL_CMPMODE1_SHIFT)) &
                                           pwmFan_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & pwmFan_CTRL_CMPMODE1_MASK;
            #endif /* (0 != pwmFan_CTRL_CMPMODE1_SHIFT) */

            #if (pwmFan_UseControl)
                pwmFan_CONTROL &= ((uint8)(~pwmFan_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                pwmFan_CONTROL |= comparemodemasked;
            #endif /* (pwmFan_UseControl) */
        }
    #endif /* pwmFan_CompareMode1SW */

#if (pwmFan_CompareMode2SW)


    /*******************************************************************************
    * Function Name: pwmFan_SetCompareMode2
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
    void pwmFan_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != pwmFan_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << pwmFan_CTRL_CMPMODE2_SHIFT)) &
                                                 pwmFan_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & pwmFan_CTRL_CMPMODE2_MASK;
        #endif /* (0 != pwmFan_CTRL_CMPMODE2_SHIFT) */

        #if (pwmFan_UseControl)
            pwmFan_CONTROL &= ((uint8)(~pwmFan_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            pwmFan_CONTROL |= comparemodemasked;
        #endif /* (pwmFan_UseControl) */
    }
    #endif /*pwmFan_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!pwmFan_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: pwmFan_WriteCounter
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
    void pwmFan_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(pwmFan_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: pwmFan_ReadCounter
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
    uint8 pwmFan_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(pwmFan_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG8(pwmFan_CAPTURE_LSB_PTR));
    }

    #if (pwmFan_UseStatus)


        /*******************************************************************************
        * Function Name: pwmFan_ClearFIFO
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
        void pwmFan_ClearFIFO(void) 
        {
            while(0u != (pwmFan_ReadStatusRegister() & pwmFan_STATUS_FIFONEMPTY))
            {
                (void)pwmFan_ReadCapture();
            }
        }

    #endif /* pwmFan_UseStatus */

#endif /* !pwmFan_UsingFixedFunction */


/*******************************************************************************
* Function Name: pwmFan_WritePeriod
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
void pwmFan_WritePeriod(uint8 period) 
{
    #if(pwmFan_UsingFixedFunction)
        CY_SET_REG16(pwmFan_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(pwmFan_PERIOD_LSB_PTR, period);
    #endif /* (pwmFan_UsingFixedFunction) */
}

#if (pwmFan_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: pwmFan_WriteCompare
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
    void pwmFan_WriteCompare(uint8 compare) \
                                       
    {
        #if(pwmFan_UsingFixedFunction)
            CY_SET_REG16(pwmFan_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(pwmFan_COMPARE1_LSB_PTR, compare);
        #endif /* (pwmFan_UsingFixedFunction) */

        #if (pwmFan_PWMMode == pwmFan__B_PWM__DITHER)
            #if(pwmFan_UsingFixedFunction)
                CY_SET_REG16(pwmFan_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG8(pwmFan_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (pwmFan_UsingFixedFunction) */
        #endif /* (pwmFan_PWMMode == pwmFan__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: pwmFan_WriteCompare1
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
    void pwmFan_WriteCompare1(uint8 compare) \
                                        
    {
        #if(pwmFan_UsingFixedFunction)
            CY_SET_REG16(pwmFan_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(pwmFan_COMPARE1_LSB_PTR, compare);
        #endif /* (pwmFan_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: pwmFan_WriteCompare2
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
    void pwmFan_WriteCompare2(uint8 compare) \
                                        
    {
        #if(pwmFan_UsingFixedFunction)
            CY_SET_REG16(pwmFan_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(pwmFan_COMPARE2_LSB_PTR, compare);
        #endif /* (pwmFan_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (pwmFan_DeadBandUsed)


    /*******************************************************************************
    * Function Name: pwmFan_WriteDeadTime
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
    void pwmFan_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!pwmFan_DeadBand2_4)
            CY_SET_REG8(pwmFan_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            pwmFan_DEADBAND_COUNT &= ((uint8)(~pwmFan_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(pwmFan_DEADBAND_COUNT_SHIFT)
                pwmFan_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << pwmFan_DEADBAND_COUNT_SHIFT)) &
                                                    pwmFan_DEADBAND_COUNT_MASK;
            #else
                pwmFan_DEADBAND_COUNT |= deadtime & pwmFan_DEADBAND_COUNT_MASK;
            #endif /* (pwmFan_DEADBAND_COUNT_SHIFT) */

        #endif /* (!pwmFan_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: pwmFan_ReadDeadTime
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
    uint8 pwmFan_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!pwmFan_DeadBand2_4)
            return (CY_GET_REG8(pwmFan_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(pwmFan_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(pwmFan_DEADBAND_COUNT & pwmFan_DEADBAND_COUNT_MASK)) >>
                                                                           pwmFan_DEADBAND_COUNT_SHIFT));
            #else
                return (pwmFan_DEADBAND_COUNT & pwmFan_DEADBAND_COUNT_MASK);
            #endif /* (pwmFan_DEADBAND_COUNT_SHIFT) */
        #endif /* (!pwmFan_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (pwmFan_UseStatus || pwmFan_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: pwmFan_SetInterruptMode
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
    void pwmFan_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(pwmFan_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: pwmFan_ReadStatusRegister
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
    uint8 pwmFan_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(pwmFan_STATUS_PTR));
    }

#endif /* (pwmFan_UseStatus || pwmFan_UsingFixedFunction) */


#if (pwmFan_UseControl)


    /*******************************************************************************
    * Function Name: pwmFan_ReadControlRegister
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
    uint8 pwmFan_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(pwmFan_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: pwmFan_WriteControlRegister
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
    void pwmFan_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(pwmFan_CONTROL_PTR, control);
    }

#endif /* (pwmFan_UseControl) */


#if (!pwmFan_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: pwmFan_ReadCapture
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
    uint8 pwmFan_ReadCapture(void) 
    {
        return (CY_GET_REG8(pwmFan_CAPTURE_LSB_PTR));
    }

#endif /* (!pwmFan_UsingFixedFunction) */


#if (pwmFan_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: pwmFan_ReadCompare
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
    uint8 pwmFan_ReadCompare(void) 
    {
        #if(pwmFan_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(pwmFan_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(pwmFan_COMPARE1_LSB_PTR));
        #endif /* (pwmFan_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: pwmFan_ReadCompare1
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
    uint8 pwmFan_ReadCompare1(void) 
    {
        return (CY_GET_REG8(pwmFan_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: pwmFan_ReadCompare2
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
    uint8 pwmFan_ReadCompare2(void) 
    {
        return (CY_GET_REG8(pwmFan_COMPARE2_LSB_PTR));
    }

#endif /* (pwmFan_UseOneCompareMode) */


/*******************************************************************************
* Function Name: pwmFan_ReadPeriod
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
uint8 pwmFan_ReadPeriod(void) 
{
    #if(pwmFan_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(pwmFan_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(pwmFan_PERIOD_LSB_PTR));
    #endif /* (pwmFan_UsingFixedFunction) */
}

#if ( pwmFan_KillModeMinTime)


    /*******************************************************************************
    * Function Name: pwmFan_WriteKillTime
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
    void pwmFan_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(pwmFan_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: pwmFan_ReadKillTime
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
    uint8 pwmFan_ReadKillTime(void) 
    {
        return (CY_GET_REG8(pwmFan_KILLMODEMINTIME_PTR));
    }

#endif /* ( pwmFan_KillModeMinTime) */

/* [] END OF FILE */
