/*
 * API_delay.c
 *
 *  Created on: 5 nov. 2021
 *      Author: Martin Juarez
 */


#include "API_delay.h"
#include "stm32f4xx_hal.h"



void delayInit( delay_t * delay, tick_t duration )
{
	delay->duration = duration;
	delay->running = 0;
}


bool_t delayRead( delay_t * delay )
{
	bool_t done=0;
	uint32_t resta;

	if((delay->running) == 0)
	{
		delay->startTime = HAL_GetTick();
		delay->running = 1;
	}
	else
	{
		resta = HAL_GetTick() - delay->startTime;
		if(resta >= (delay->duration))
		{
			done=1;
			delay->running = 0;
		}
	}
	return done;
}


void delayWrite( delay_t * delay, tick_t duration )
{
	delay->duration = duration;
}

