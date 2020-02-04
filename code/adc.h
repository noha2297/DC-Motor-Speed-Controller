/*
 * adc.h
 *
 *  Created on: Jan 5, 2020
 *      Author: Noha Gamal
 */

#ifndef ADC_H_
#define ADC_H_

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

#define INTERRPUT 0

typedef enum
{
	FCPU_DIV2  , FCPU_2  , FCPU_4 , FCPU_8 , FCPU_16 , FCPU_32 , FCPU_64 , FCPU_128
}ADC_Clock;

typedef enum
{
	ADC_ch0 , ADC_ch1 , ADC_ch2 , ADC_ch3 , ADC_ch4 , ADC_ch5 , ADC_ch6 , ADC_ch7
}ADC_Channel;

typedef enum
{
	AREFF ,AVCC_External , Reserved , Internal_Voltage
}ADC_RefrenceVolt;
/*
typedef enum
{
	polling , interrupt
}ADC_State;
*/
typedef struct
{
	ADC_Clock clock;
	ADC_RefrenceVolt Vref;
}ADC_ConfigType;

/* ****************************************************************************** */
/* *************************** Function Prototype ******************************* */
/* ***************************************************************************** */

void ADC_init(const ADC_ConfigType * a_configType_Ptr);
uint16 ADC_readChannel (uint8 a_channelNum);


#endif /* ADC_H_ */
