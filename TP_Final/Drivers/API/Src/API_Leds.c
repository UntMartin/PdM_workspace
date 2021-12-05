/*
 * API_Leds.c
 *
 *  Created on: 4 dic. 2021
 *      Author: martin
 */
#include "stdint.h"
#include "stdbool.h"
#include "API_Leds.h"
#include "API_delay.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */


static delay_t LedDelayActual;

static estadoLEDs_t estadoActual;

static bool_t EstadoStandBy;


void InicializarLeds()
{

  BSP_LED_Init(LED1);  // verde
  BSP_LED_Init(LED2);  // azul
  BSP_LED_Init(LED3);  // rojo

  delayInit(&LedDelayActual, DELAY_STAND_BY_OFF);
  EstadoStandBy = 1;

}

void ActualizarLeds()
{

	if(delayRead(&LedDelayActual))
	{
		switch(estadoActual)
		{
			case ESTADO_LED_STAND_BY:

				if(EstadoStandBy)
				{
					EstadoStandBy = 0;
					BSP_LED_On(LED2);
					delayInit(&LedDelayActual, DELAY_STAND_BY_ON);
				}
				else
				{
					EstadoStandBy = 1;
					BSP_LED_Off(LED2);
					delayInit(&LedDelayActual, DELAY_STAND_BY_OFF);
				}
			break;

			case ESTADO_LED_ESPERA:

					BSP_LED_Toggle(LED2);

			break;

			default:

				break;
		}
	}

}

void SetearEstadoLed(uint8_t nuevoEstado)
{
	BSP_LED_Off(LED1);
	BSP_LED_Off(LED2);
	BSP_LED_Off(LED3);

	switch(nuevoEstado)
	{
		case ESTADO_LED_STAND_BY:

			  delayInit(&LedDelayActual, DELAY_STAND_BY_OFF);
			  EstadoStandBy = 1;
			  estadoActual = ESTADO_LED_STAND_BY;

		break;


		case ESTADO_LED_ESPERA:

			  delayInit(&LedDelayActual, DELAY_ESPERA);
			  estadoActual = ESTADO_LED_ESPERA;

		break;


		case ESTADO_LED_ACCESO_OK:

			  BSP_LED_On(LED1);
			  estadoActual = ESTADO_LED_ACCESO_OK;

		break;

		case ESTADO_LED_ACCESO_DENY:

			  BSP_LED_On(LED3);
			  estadoActual = ESTADO_LED_ACCESO_DENY;

		break;

	}



}





