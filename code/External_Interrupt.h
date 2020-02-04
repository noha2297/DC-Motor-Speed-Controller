/*
 * External_Interrupt.h
 *
 *  Created on: Jan 8, 2020
 *      Author: Lenovo
 */

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

 typedef enum
  {
   LowLevel_0=0,AnyLogicalChange_0,FallingEdge_0,RisingEdge_0,
   LowLevel_1=0,AnyLogicalChange_1,FallingEdge_1,RisingEdge_1,
   FallingEdge_2=0,RisingEdge_2

  }Interrupt_SelectEdge;




  void Interrupt_init(uint8 InterruptPin,Interrupt_SelectEdge Edge_State);


#endif /* EXTERNAL_INTERRUPT_H_ */
