/*
 * main.c
 *
 *  Created on: Apr 11, 2018
 *      Author: kanta
 */

#include "DAC.h"
#include "ADC.h"
#include "PIT.h"
#include "FLEX.h"
#include "NVIC.h"
#include "GPIO.h"


#define TOTAL_MUESTRAS 60000
#define RETRASO_MUESTRAS 7500
#define TERMINOS 8
#define VOLTAGE_OFF 1.5

#define ADC_channel 12


const ADC_ConfigType ADC_Config = {
							INTERRUPT_DISABLE,
							DIFFERENTIAL_DISABLE,
							MODE_12_BIT,
							BUS,
							ADC_channel,
							SAMPLE_32,
							CC_ENABLE,
							AVERAGE_ENABLE};
int main(void)
{
	uint16 contador;
	uint16 alpha = 0.1;
	uint16 ret = RETRASO_MUESTRAS;
	//tiempo de retraso de .25 y frecuencia de muestreo de 30kHz
	uint16 value[60000] = {0};
	uint16 output;

	/** Configuración para sw3 */
	GPIO_pinControlRegisterType interruptPullUpIO = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;
	GPIO_pinControlRegister(GPIO_A,BIT4,&interruptPullUpIO);
	GPIO_dataDirectionPIN(GPIO_A, GPIO_INPUT,BIT4);

	NVIC_setBASEPRI_threshold(PRIORITY_10);
	ADC0_init(&ADC_Config); /*! Configuration function for the ADC */
	FLEX_init();
	EnableInterrupts;

	for(;;)
	{
		if(TRUE == GPIO_getIRQStatus(GPIO_A))
		{
			GPIO_clearIRQStatus(GPIO_A);
			alpha = (alpha >= 1)? 0.1 : alpha + 0.1;
		}

		if(TRUE == getFTM0_flag())
		{
			for(contador = 0;contador < TOTAL_MUESTRAS - 1; contador++)
			{
				value[contador+1] = value[contador];
			}
			startConversion(ADC_channel);
			while(TRUE == ADC0_conversionComplete()){}
			value[0] = ADC0_readValue() - VOLTAGE_OFF;
			clearFTM0_flag();


			output = -alpha*value[0]  + VOLTAGE_OFF + (1 - alpha*alpha) *
					(value[ret] + alpha*value[2*ret] + alpha*alpha*value[3*ret]
					 + alpha*alpha*alpha*value[4*ret] + alpha*alpha*alpha*alpha*value[5*ret]
					 + alpha*alpha*alpha*alpha*alpha*value[6*ret] + alpha*alpha*alpha*alpha*alpha*alpha*value[7*ret]);
		}

		DAC0_newValue(output);

	}
}
