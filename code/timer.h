/*
 * timer.h
 *
 *  Created on: Jan 6, 2020
 *      Author: Noha Gamal
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "micro_config.h"
#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	TIMER_0_2_Normal  , TIMER_0_2_PWM=8 , TIMER_0_2_CTC =1 , TIMER_0_2_Fast_PWM =9
}TIMER_0_2_waveGnerationMode;

typedef enum
{
	TIMER1_Normal  , TIMER1_PWMPhase8  , TIMER1_PWMPhase9 , TIMER1_PWMPhase10,
	TIMER1_CTC_OCR1A  , TIMER1_FastPWM_8 ,  TIMER1_FastPWM_9 , TIMER1_FastPWM_10 ,
	TIMER1_PhaseFreq_ICR1 , TIMER1_PhaseFreq_OCR1A , TIMER1_Phase_ICR1 ,
	TIMER1_Phase_OCR1A ,TIMER1_CTC_ICR1 , TIMER1_Reserved  , TIMER1_FastPWM_ICR1 ,
	TIMER1_FastPWM_OCR1A

}TIMER1_waveGnerationMode;

typedef enum
{
	NonPWM_normal , NonPWM_toggle , NonPWM_clear , NonPWM_set
}TIMER_compOutModeNonPWM;

typedef enum
{
	FastPWM_normal , FastPWM_reserved  , FastPWM_toggle =1, FastPWM_clear  , FastPWM_set
}TIMER_compOutModeFastPWM;

typedef enum
{
	PhaseCorrect_normal , PhaseCorrect_reserved , PhaseCorrect_toggle =1 , PhaseCorrect_clear  , PhaseCorrect_set
}TIMER_compOutModePhaseCorrectPWM;

typedef enum
{
	TIMER_0_1_No_clock , TIMER_0_1_FCPU , TIMER_0_1_FCPU_8 , TIMER_0_1_FCPU_64 ,
	TIMER_0_1_FCPU_256 , TIMER_0_1_FCPU_1024 , TIMER_0_1_ExternalOnFalling ,TIMER_0_1_ExternalOnRising

}TIMER_0_1_clock;
typedef enum
{
	TIMER2_No_clock , TIMER2_FCPU , TIMER2_FCPU_8 , TIMER2_FCPU_32 ,
	TIMER2_FCPU_64 ,TIMER2_FCPU_128, TIMER2_FCPU_256 , TIMER2_FCPU_1024
}TIMER2_clock;

typedef enum
{
	timer0  , timer1  , timer2
}TIMER_channel;

typedef struct
{
	TIMER_channel  channel;
	union Timer_WaveMode
	{
		TIMER_0_2_waveGnerationMode TIMER_0_2_waveMode;
		TIMER1_waveGnerationMode TIMER1_waveMode;
	}waveMode;

	union CompOutMode
	{
		TIMER_compOutModeNonPWM compNonPWM;
		TIMER_compOutModeFastPWM compFastPWM;
		TIMER_compOutModePhaseCorrectPWM PhaseCorrect;
	}compOut , Timer1compOut1B;
	union Timer_clock
	{
		TIMER_0_1_clock Timer_0_1_clock;
		TIMER2_clock Timer_2_clock;

	}clock;

	uint16 initalValue; 				/* SET =0 as an initial value */
	uint16 finalValue; 				/* SET =0 as an initial value */
	uint16 Timer1_compValChannelB ;	/* SET =0 as an initial value */
	uint16 Timer1_compValChannelA ;	/* SET =0 as an initial value */
}TIMER_config;


/*******************************************************************************
 *                         Function Prototype                                   *
 *******************************************************************************/



void TIMER_init(const TIMER_config  * configOfTimer );

static void TIMER0_initNonPWM(const TIMER_config  * configOfTimer);
static void TIMER0_initPWM( const TIMER_config  * configOfTimer );

static void TIMER2_initNonPWM(const TIMER_config  * configOfTimer);
static void TIMER2_initPWM( const TIMER_config  * configOfTimer );

static void TIMER1_initNonPWM( const TIMER_config  * configOfTimer );
static void TIMER1_initPWM( const TIMER_config  * configOfTimer );



#endif /* TIMER_H_ */
