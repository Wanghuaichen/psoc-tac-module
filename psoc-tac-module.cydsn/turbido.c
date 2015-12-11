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
#include "turbido.h"


#define BUFFER_SIZE 500

#define SAMPLE_FREQ 1500
#define LED_FREQ 15

static int k = SAMPLE_FREQ/(LED_FREQ*2); 
float mean2[10] = {0};
float Turbidity_buffer[BUFFER_SIZE] = {0};

float buffer[BUFFER_SIZE] = {0};
int compteur = -1;
float accumulateur = 0;
int turbido_index = 0;
float mean= 0;

//-----------------------------------------------------------------------------

void meanTurbido(int pos,float* signalReception, float* moyenne)
{
    float signalOut = 0;
    int posMinusK = getBufferIndex(pos, -k, BUFFER_SIZE);
    int posMinus2K = getBufferIndex(pos, -2*k, BUFFER_SIZE);
    int posMinus75 = getBufferIndex(pos, -75, BUFFER_SIZE);

    accumulateur = accumulateur-signalReception[pos] +
                    2*signalReception[posMinusK] - signalReception [posMinus2K];

    if (accumulateur < 0)
	{
        signalOut = -signalReception[posMinus75];
    }
	else
    {
		signalOut = signalReception[posMinus75];
    }


    if ((pos % 1000) == 0)
    {
        compteur += 1;
	}

    moyenne[compteur] = moyenne[compteur]+signalOut/BUFFER_SIZE;
}

//-----------------------------------------------------------------------------

int getBufferIndex(int currentIndex, int increment, int bufferSize)
{
    int index = currentIndex + increment;
    if (index >= 0)
    {
       index = index%bufferSize;
    }
    else
    {
        index = bufferSize + index;
    }
    return index;
}


float updateTurbidoOutput(int16 Turbido_ADC_result)
{
    //simulation de la reception d'un echantillons
    
    int i =0;
    buffer[turbido_index] = ADC_TURBIDO_CountsTo_Volts(Turbido_ADC_result);

    meanTurbido(turbido_index, buffer, mean2);
    turbido_index = getBufferIndex(turbido_index, 1, BUFFER_SIZE);
    
    if(compteur >= 11)
    {
        mean = 0;
        for(i = 1; i<10;i++)
        {
            mean += mean2[i];
        }

        mean = mean/9;
        
        compteur = 0;
        
        for(i = 0; i<11;i++)
        {
            mean2[i] = 0;
        }
    }   
    
    return mean;
}

void initTurbido()
{
    ADC_TURBIDO_Start();
    Turbido_PGA_Start();
    ClockTurbido_Start();
}

/* [] END OF FILE */
