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

#ifndef __FAN_CONTROLER_H__
#define __FAN_CONTROLER_H__
    
#include <project.h>
#include "Defines.h"
    
void changeFanSpeed(uint8 percentage, uint8 module);
int8 changeFanState(uint8 fanEnableState, uint8 module);

#endif

/* [] END OF FILE */
