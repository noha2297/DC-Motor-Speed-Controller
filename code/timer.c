/*
 * timer.c
 *
 *  Created on: Jan 6, 2020
 *      Author: Noha Gamal
 */
#include "timer.h"



void TIMER_init(const TIMER_config  * configOfTimer  )
{

	if(configOfTimer ->channel == timer1)
	{
		//TIMER1_initNonPWM(configOfTimer);
		TIMER1_initPWM(configOfTimer);
	}
	else if (configOfTimer ->channel == timer0)
	{
		if(configOfTimer->waveMode.TIMER_0_2_waveMode == TIMER_0_2_Normal || configOfTimer->waveMode.TIMER_0_2_waveMode == TIMER_0_2_CTC)
			TIMER0_initNonPWM(configOfTimer);
		else
			TIMER0_initPWM(configOfTimer);
	}
	else
	{
		//TIMER2_initNonPWM(configOfTimer);
		TIMER2_initPWM(configOfTimer);
	}
}
static void TIMER0_initNonPWM( const TIMER_config  * configOfTimer )
{
	TCCR0 = (1<<FOC0) | (TCCR0 |  (configOfTimer ->waveMode.TIMER_0_2_waveMode <<WGM01 ) ) | (TCCR0 | (configOfTimer ->compOut .compNonPWM) <<COM00) |(TCCR0|configOfTimer->clock.Timer_0_1_clock);
	TCNT0=configOfTimer->initalValue;

	if (configOfTimer->waveMode.TIMER_0_2_waveMode == TIMER_0_2_Normal )
		TIMSK |= (1<<TOIE0);

	else if (configOfTimer->waveMode.TIMER_0_2_waveMode== TIMER_0_2_CTC)
	{
		TIMSK |= (1<<OCIE0);
		OCR0 = configOfTimer->finalValue;
	}
}
 static void TIMER0_initPWM( const TIMER_config  * configOfTimer )
 {
 	TCCR0 =  (TCCR0 |  (configOfTimer ->waveMode.TIMER_0_2_waveMode <<WGM01 ) ) | (TCCR0 | (configOfTimer ->compOut .compFastPWM) <<COM00) |(TCCR0|configOfTimer->clock.Timer_0_1_clock);
 	TCNT0=configOfTimer->initalValue;
 	OCR0 =configOfTimer->finalValue ;

 }

 static void TIMER2_initNonPWM( const TIMER_config  * configOfTimer )
 {
 	TCCR2 = (1<<FOC2) | (TCCR2 |  (configOfTimer ->waveMode.TIMER_0_2_waveMode <<WGM21 ) ) | (TCCR2 | (configOfTimer ->compOut .compNonPWM) <<COM20) |(TCCR2|configOfTimer->clock.Timer_2_clock);
 	TCNT2=configOfTimer->initalValue;

 	if (configOfTimer->waveMode.TIMER_0_2_waveMode == TIMER_0_2_Normal )
 		TIMSK |= (1<<TOIE2);

 	else if (configOfTimer->waveMode.TIMER_0_2_waveMode== TIMER_0_2_CTC)
 	{
 		TIMSK |= (1<<OCIE2);
 		OCR2 = configOfTimer->finalValue;
 	}
 }

 static void TIMER2_initPWM( const TIMER_config  * configOfTimer )
 {
 	TCCR2 =  (TCCR2 |  (configOfTimer ->waveMode.TIMER_0_2_waveMode <<WGM21 ) ) | (TCCR2 | (configOfTimer ->compOut .compFastPWM) <<COM20) |(TCCR0|configOfTimer->clock.Timer_2_clock);
 	TCNT2=configOfTimer->initalValue;
 	OCR2 =configOfTimer->finalValue ;

 }
static void TIMER1_initNonPWM( const TIMER_config  * configOfTimer )
{
	/*
	 * 1) Wave generation Mode table have 4 bits WGM10: WGM13 first 2 bits in TCCR1A  and the other  2bits in TCCR1
	 * So we take first 2 bits by clear the others and it is done by  make the Wave mode value & 0x03 " 0b00000011 "  and then put it in TCCR1A
	 * then we take the last 2 bits by clear the others and it is done by  make the Wave mode value & 0x0C " 0b00001100 "  and then put it in TCCR1B
	 * 2) we assign the  value of Compare out table of channel A/B COM1A0 /COM1B0
	 * 3) we assign the value of the clock in TCCR1B register
	 * 4)assign initial value in TCNT1 register
	 * 6) Put the top value in OCR1A or  ICR1 in case of CTC mode
	 * 7) enable the suitable interrupt
	 */
	TCCR1A = (1<<FOC1A) |(1<<FOC1B) | ( TCCR1A | (configOfTimer->waveMode.TIMER1_waveMode &0x03) ) | (TCCR1A |(configOfTimer->compOut.compNonPWM << COM1A0) ) | (TCCR1A |(configOfTimer->Timer1compOut1B.compNonPWM << COM1B0));
	TCCR1B = ( TCCR1B | ( (configOfTimer->waveMode.TIMER1_waveMode &0x0C) <<1 ) ) |(TCCR1B | configOfTimer->clock.Timer_0_1_clock);
	TCNT1=configOfTimer->initalValue;

	switch (configOfTimer->waveMode.TIMER1_waveMode)
	{
		case TIMER1_Normal: TIMSK |= (1<<TOIE1); break; // OCR1A VALUE ??

		case TIMER1_CTC_OCR1A : OCR1A = configOfTimer->finalValue;
								TIMSK |= (1<<OCIE1A); break;

		case TIMER1_CTC_ICR1 :  ICR1 = configOfTimer->finalValue;
								TIMSK |= (1<<OCIE1A); break;

	}
	OCR1B = configOfTimer ->Timer1_compValChannelB;

}

static void TIMER1_initPWM( const TIMER_config  * configOfTimer )
{

	TCCR1A =  (TCCR1A |  (configOfTimer ->waveMode.TIMER1_waveMode &0X03 ) ) |  (TCCR1A| (configOfTimer ->compOut .compFastPWM) <<COM1A0) | (TCCR1A| (configOfTimer ->Timer1compOut1B.compFastPWM <<COM1B0));
	TCCR1B = ( TCCR1B | ( (configOfTimer->waveMode.TIMER1_waveMode &0x0C) <<1 ) ) |(TCCR1B | configOfTimer->clock.Timer_0_1_clock);
	TCNT0=configOfTimer->initalValue;

	if (configOfTimer->waveMode.TIMER1_waveMode == TIMER1_FastPWM_OCR1A)
		OCR1A= configOfTimer->finalValue;

	else if (configOfTimer->waveMode.TIMER1_waveMode == TIMER1_FastPWM_ICR1)
	{
		ICR1 = configOfTimer->finalValue;
		OCR1A = configOfTimer -> Timer1_compValChannelA ;
	}


	OCR1B = configOfTimer ->Timer1_compValChannelB;


}


