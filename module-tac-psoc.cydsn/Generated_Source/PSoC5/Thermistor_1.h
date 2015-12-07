/*******************************************************************************
* File Name: Thermistor_1.h
* Version 1.20
*
* Description:
*  This header file provides registers and constants associated with the
*  ThermistorCalc component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_THERMISTOR_CALC_Thermistor_1_H)
#define CY_THERMISTOR_CALC_Thermistor_1_H

#include "cyfitter.h"
#include "CyLib.h"

#define Thermistor_1_IMPLEMENTATION         (0u)
#define Thermistor_1_EQUATION_METHOD        (0u)
#define Thermistor_1_LUT_METHOD             (1u)

#if (Thermistor_1_IMPLEMENTATION == Thermistor_1_EQUATION_METHOD)
    #include <math.h>
#endif /* (Thermistor_1_IMPLEMENTATION == Thermistor_1_EQUATION_METHOD) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Thermistor_1_REF_RESISTOR           (10000)
#define Thermistor_1_REF_RES_SHIFT          (0u)
#define Thermistor_1_ACCURACY               (5u)
#define Thermistor_1_MIN_TEMP               (-20 * Thermistor_1_SCALE)


/***************************************
*        Function Prototypes
***************************************/

uint32 Thermistor_1_GetResistance(int16 vReference, int16 vThermistor)
                                      ;
int16 Thermistor_1_GetTemperature(uint32 resT) ;


/***************************************
*           API Constants
***************************************/

#define Thermistor_1_K2C                    (273.15)
#define Thermistor_1_SCALE                  (100)

#define Thermistor_1_THA               (0.0008731773)
#define Thermistor_1_THB               (0.0002539517)
#define Thermistor_1_THC               (1.815622E-07)


#endif /* CY_THERMISTOR_CALC_Thermistor_1_H */


/* [] END OF FILE */
