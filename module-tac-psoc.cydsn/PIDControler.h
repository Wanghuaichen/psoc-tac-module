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

#ifndef __PID_CONTROLER_H__
#define __PID_CONTROLER_H__

#include <project.h>
#include "Defines.h"
    
#include "Termistor.h"
#include "PeltierControler.h"
#include "FanControler.h"
#include "ComputerCommunication.h"
    
void resetPIDSumError();
void updatePeltierOutput(uint8 module, double dt);

#endif
/* [] END OF FILE */
