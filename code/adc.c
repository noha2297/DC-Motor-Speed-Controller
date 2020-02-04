/*
 * adc.c
 *
 *  Created on: Jan 5, 2020
 *      Author: Noha Gamal
 */
#include "adc.h"
volatile uint16 g_ADC_Val =0 ;

void ADC_init(const ADC_ConfigType * a_configType_Ptr )
{
	ADMUX = ADCSRA = 0;
	/* ADMUX Register Bits Description:
	 * Vref : we assign the Vref source through the Vref enum which in configType structure
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX |= (ADMUX | (a_configType_Ptr->Vref << REFS0));
	/*
	 * ADC-Clock : is assigned by the clock enum which in configType structure
	 * then we enable the ADC
	 */
	ADCSRA = (ADCSRA |a_configType_Ptr ->clock) | (1<< ADEN) ;
	/*
	 * if we are in the Interrupt mode  , then enable the ADC interrupt  .
	 * Otherwise we are in polling mode
	 */

#if INTERRPUT ==1
	ADCSRA |= (1 <<ADIE);
#endif

}
/*
 * if we are in the Interrupt mode  , The ISR fun will remain  .
 * Otherwise we are in polling mode and ISR is deleted
 */

#if INTERRPUT
 ISR (ADC_vect)
{
	 g_ADC_Val = ADC ;
}
#endif


uint16 ADC_readChannel (uint8 a_channelNum)
{
	a_channelNum &= 0x07; /*  channel number must be from 0 (0b000) --> 7 (0b111)  */
	ADMUX &=0XE0; /* clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX |=a_channelNum; /* choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA , ADSC); // ADCSRA |=(1<<ADSC);
	#if (INTERRPUT ==0) // polling
		while (BIT_IS_CLEAR(ADCSRA , ADIF));
		SET_BIT(ADCSRA , ADIF); /* clear ADIF by write '1' to it :) */
		 g_ADC_Val = ADC ;
	#endif
		 return g_ADC_Val;

}
