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

/** Get an index at a distance from a current index.
 *
 * @param currentIndex the index from which you want a new index
 * @param increment the distance between the current index and the one you want
 * @param bufferSize the size of the buffer you want to index
 */
#include <project.h>

/**
 * Update the buffer when a new sample is available.
 * If enougth sample have been received perform a mean to generate a result
 */
float updateTurbidoOutput(int16 Turbido_ADC_result);

/**
 * Initialise the top design block needed by the tac.
 */
void initTurbido();

/* [] END OF FILE */
