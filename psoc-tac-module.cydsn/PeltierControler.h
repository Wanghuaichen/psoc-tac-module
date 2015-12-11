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

#ifndef __PELTIER_CONTROLER_H__
#define __PELTIER_CONTROLER_H__
    
#include <project.h>
#include "Defines.h"
#include <stdio.h>
#include <stdlib.h>
    
uint8 changePeltierPWMValue(int8 desiredPercentage, uint8 module);
uint8 changePeltierModuleState(uint8 peltierEnableState, uint8 module);
uint8 changePeltierModuleCurrentDirection(CurrentDirectionType direction,  uint8 module);
    
#endif
/* [] END OF FILE */
