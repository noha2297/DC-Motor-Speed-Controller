/*
 * project2.c
 *
 *  Created on: Jan 7, 2020
 *      Author: Lenovo
 */

#include "lcd.h"
#include "adc.h"
#include "timer.h"
#include "interrupt.h"
#include "External_Interrupt.h"

volatile uint8 flag=0;
ISR(INT1_vect)
{
	TOGGLE_BIT(PORTD , PD4);
	flag =!flag;
}
void TIMER0_PWM( const uint8 duty_cycle);
void ADC_setConfigration();
void TurnOnMotor();
void reverseMotorDir();
void portsSetConfig();

int main(void)
{

	uint16 res_value;
	SREG |=(1<<7); /* enable I bit*/
	portsSetConfig();
	ADC_setConfigration();
	Interrupt_init(INT1 ,RisingEdge_1 );
	LCD_init(); /* initialize LCD driver */
	/* display this string "ADC Value = " only once at LCD */
    LCD_displayString("ADC Value = ");
    PORTD&= ~(1<<PD4);
    while(1)
    {
    	LCD_goToRowColumn(0,12); /* display the number every time at this position */
		res_value = ADC_readChannel(0); /* read channel zero where the potentiometer is connect */
		TIMER0_PWM(res_value);
		LCD_intgerToString(res_value); /* display the ADC value on LCD screen */

    	if (flag ==0)
    	{
    		TurnOnMotor();
    	}

    	else if(flag==1)
    	{
    		reverseMotorDir();
    	}


    }
}

void portsSetConfig()
{
	DDRC = 0xff;
	DDRD|=(1<<PD0) |(1<<PD1) |(1<<PD2)|(1<<PD4);
	DDRD &=~(1<<PD3);
	DDRB |= (1<<PB0) |(1<<PB1) | (1<<PB3) ; /* OUTPUT */
}
void TurnOnMotor()
{
	SET_BIT(PORTB , PB0);
	CLEAR_BIT(PORTB , PB1);
}
void reverseMotorDir()
{
	SET_BIT(PORTB , PB1);
	CLEAR_BIT(PORTB , PB0);
}
void ADC_setConfigration()
{
	ADC_ConfigType  configType ;
	configType .clock = FCPU_8;
	configType.Vref = AREFF;
	ADC_init(&configType); /* initialize ADC driver */
}
void TIMER0_PWM( const uint8 duty_cycle)
{
	TIMER_config config ;
	config.channel= timer0;
	config.waveMode.TIMER_0_2_waveMode = TIMER_0_2_Fast_PWM;
	config.clock.Timer_0_1_clock = TIMER_0_1_FCPU_8;
	config.compOut.compFastPWM = FastPWM_clear; // Non inverting mode
	config.initalValue=0;
	config.finalValue=duty_cycle;
	//DDRB  = DDRB | (1<<PB3);
	TIMER_init(&config);
}
