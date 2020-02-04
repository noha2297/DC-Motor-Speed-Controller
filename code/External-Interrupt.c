/*
 * External-Interrupt.c
 *
 *  Created on: Jan 8, 2020
 *      Author: Lenovo
 */

#include "External_Interrupt.h"

 void Interrupt_init(uint8 InterruptPin,Interrupt_SelectEdge Edge_State)
 {
	 SET_BIT(SREG,7);

	 if (InterruptPin ==INT0 )
	 {
		 switch( Edge_State)
		 	  {
		 	 	 case   LowLevel_0:         CLEAR_BIT(MCUCR,ISC00);CLEAR_BIT(MCUCR,ISC01); break;
		 	 	 case   AnyLogicalChange_0: SET_BIT(MCUCR,ISC00);CLEAR_BIT(MCUCR,ISC01); break;
		 	 	 case   FallingEdge_0 :     CLEAR_BIT(MCUCR,ISC00);SET_BIT(MCUCR,ISC01); break;
		 	 	 case   RisingEdge_0:       SET_BIT(MCUCR,ISC00);SET_BIT(MCUCR,ISC01); break;
		 	  }
		 SET_BIT(GICR,INT0);
	 }
	 else if (InterruptPin ==INT1 )
	 {
		 switch( Edge_State)
		  {


		 case   LowLevel_1:         CLEAR_BIT(MCUCR,ISC10);CLEAR_BIT(MCUCR,ISC11); break;
	     case   AnyLogicalChange_1: SET_BIT(MCUCR,ISC10);CLEAR_BIT(MCUCR,ISC11); break;
		 case   FallingEdge_1 :     CLEAR_BIT(MCUCR,ISC10);SET_BIT(MCUCR,ISC11); break;
		 case   RisingEdge_1:       SET_BIT(MCUCR,ISC10);SET_BIT(MCUCR,ISC11); break;
		  }
		 SET_BIT(GICR,INT1);
	 }
	 else if (InterruptPin ==INT2 )
	 {
		 switch( Edge_State)
		  {
		 case   FallingEdge_2 :     CLEAR_BIT(MCUCSR,ISC2);break;
		 case   RisingEdge_2:       SET_BIT(MCUCSR,ISC2); break;
		  }
		 SET_BIT(GICR,INT2);
	 }

 }
