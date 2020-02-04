/*
 * interrupt.c
 *
 *  Created on: Jan 7, 2020
 *      Author: Noha&Somaya ----->princess
 *
 */

#include "interrupt.h"

void INT1_INIT ()
{
	MCUCR |= (1<<ISC10)|(1<<ISC11);
	GICR |=(1<<INT1);
	//SREG |=(1<<7);

}


