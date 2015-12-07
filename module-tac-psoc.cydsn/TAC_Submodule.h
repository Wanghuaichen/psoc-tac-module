/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef TAC_SUBMODULE_H
#define TAC_SUBMODULE_H
    
#include <project.h>
#include "Defines.h"
#include <stdio.h>
#include <stdlib.h>
#include "Termistor.h"

void updatePeltierOutput(uint8 module, double CycleTime);
void updatePwmValueFromCalibrationTable(uint8 module);
Boolean areCalibrationValuesAvailable(uint8 module);
double getArraySum(int16* tab, int16 size);

#endif

/* [] END OF FILE */
