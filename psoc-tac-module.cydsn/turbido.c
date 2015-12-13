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

/** Circular buffer size */
#define BUFFER_SIZE 500

/** sampling frequencie */
#define SAMPLE_FREQ 1500
/** LED flashing frequencie */
#define LED_FREQ 15

/** Number of sumple in half a periode*/
static int k = SAMPLE_FREQ/(LED_FREQ*2);

/** Buffer of signal mean*/
float mean2[10] = {0};

float buffer[BUFFER_SIZE] = {0};
int compteur = -1;
float accumulateur = 0;
int turbido_index = 0;
float mean= 0;

/**
 * Compute a coherent index for a circular buffer form a current index, an increment and the buffer size.
 * @param currenIndex 
 *  The index we are starting from.
 * @param increment
 *  The distance we want to cross.
 * @buffersize
 *  The size of the buffer, index going form  to bufferSize - 1.
 * @return Thee new buffer index.
 */
int getBufferIndex(int currentIndex, int increment, int bufferSize);

/**
 * Compute the convolution with a square signal and update a sliding window average
 *
 * @param pos
 *  Current position on the sample buffer
 * @param signalReception
 *  A buffer fill with our sample
 * @param moyenne
 *  A buffer containing our averrage
 */
void meanTurbido(int pos, float* signalReception, float* moyenne);

//-----------------------------------------------------------------------------

void meanTurbido(int pos,float* signalReception, float* moyenne)
{
    // C'est une convolution avec un signal carré.
    // Donc quand tu fais "glisser" ton signal carré d'un échantillon au suivant, 
    // la convolution reste identique aux edge près!
    // Tu gardes donc la même valeur qu'avant. Mais tu dois venir changer les edges. 
    // Ceux qui étaient à +1 passent à -1 donc tu soustraits 2 * Signal à cet endroit 
    // et les edge positifs tu additionnes 2 * Signal pour compenser.
    // Comme on a choisi un signal carré de 2 périodes, on a 3 edges intermédiaires comme 
    // je viens de l'expliquer plus 2 extrémités pour lesquelles la valeur passe de 0 (pas de convolution)
    // à 1 (début de convolution) donc on ajoute 1 * signal et pour la fin de la convolution (valeur -1 du carré) 
    // vers pas de convolution (valeur 0) donc tu ajoutes aussi 1 * Signal.

    float signalOut = 0;
    // we get the value at half a period, a period and -75 in order to perform a simple 
    // convolution with a square signal
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

//-----------------------------------------------------------------------------

float updateTurbidoOutput(int16 Turbido_ADC_result)
{    
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

//-----------------------------------------------------------------------------

void initTurbido()
{
    ADC_TURBIDO_Start();
    Turbido_PGA_Start();
    ClockTurbido_Start();
}

/* [] END OF FILE */
