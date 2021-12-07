/*
 * API_Acceso.c
 *
 *  Created on: 4 dic. 2021
 *      Author: martin
 */


#include "API_delay.h"
#include "API_Acceso.h"
#include "API_Teclado.h"
#include "API_Leds.h"
#include "API_uart.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

static uint8_t digito1;
static uint8_t digito2;
static uint8_t digito3;
static uint8_t digito4;

static delay_t AccesoDelayActual;

estadoMEF_t estadoActual;

void InicializarAcceso(void)
{
	estadoActual = ESTADO_STAND_BY;
	SetearEstadoLed(ESTADO_LED_STAND_BY);
}


void ActualizarMEF(uint8_t boton)
{
	switch (estadoActual)
	{

	case ESTADO_STAND_BY:
		if(NADA > boton)
		{
			estadoActual = ESTADO_ESPERA_2;
			digito1 = boton;
			SetearEstadoLed(ESTADO_LED_ESPERA);
			delayInit(&AccesoDelayActual, TIMEOUT);  // Se acaba de introducir un numero, reinica el tiempo de espera
		}
		break;

	case ESTADO_ESPERA_2:
		if(NADA > boton)
		{
			estadoActual = ESTADO_ESPERA_3;
			digito2 = boton;
			delayInit(&AccesoDelayActual, TIMEOUT);   // Se acaba de introducir un numero, reinica el tiempo de espera
		}
		else
		{
			if(NADA == boton)
			{
				if(delayRead(&AccesoDelayActual))
				{
					estadoActual = ESTADO_STAND_BY;
					SetearEstadoLed(ESTADO_LED_STAND_BY);
				}
			}

			if(ESC == boton)
			{
				estadoActual = ESTADO_STAND_BY;
				SetearEstadoLed(ESTADO_LED_STAND_BY);
			}
		}
		break;


	case ESTADO_ESPERA_3:
		if(NADA > boton)
		{
			estadoActual = ESTADO_ESPERA_4;
			digito3 = boton;
			delayInit(&AccesoDelayActual, TIMEOUT);   // Se acaba de introducir un numero, reinica el tiempo de espera
		}
		else
		{
			if(NADA == boton)
			{
				if(delayRead(&AccesoDelayActual))
				{
					estadoActual = ESTADO_STAND_BY;
					SetearEstadoLed(ESTADO_LED_STAND_BY);
				}
			}

			if(ESC == boton)
			{
				estadoActual = ESTADO_STAND_BY;
				SetearEstadoLed(ESTADO_LED_STAND_BY);
			}
		}
		break;

	case ESTADO_ESPERA_4:
		if(NADA > boton)
		{
			estadoActual = ESTADO_ESPERA_ENT;
			digito4 = boton;
			delayInit(&AccesoDelayActual, TIMEOUT);   // Se acaba de introducir un numero, reinica el tiempo de espera
		}
		else
		{
			if(NADA == boton)
			{
				if(delayRead(&AccesoDelayActual))
				{
					estadoActual = ESTADO_STAND_BY;
					SetearEstadoLed(ESTADO_LED_STAND_BY);
				}
			}

			if(ESC == boton)
			{
				estadoActual = ESTADO_STAND_BY;
				SetearEstadoLed(ESTADO_LED_STAND_BY);
			}
		}
		break;


	case ESTADO_ESPERA_ENT:
		if(ENT == boton)
		{
			delayInit(&AccesoDelayActual, TIMEOUT);   // Se carga el tiempo durante el cual se avisara si el acceso fue concedido o no
			estadoActual = ESTADO_ACCESO;

			if((DIGITO_1 == digito1)&&(DIGITO_2 == digito2)&&(DIGITO_3 == digito3)&&(DIGITO_4 == digito4))
			{
				// Acceso concedido
				uartSendString("\n\n-    -   -  - --- Acceso Concedido! --- -  -   -    - \n\n\r");
				SetearEstadoLed(ESTADO_LED_ACCESO_OK);
			}
			else
			{
				// Acceso Denegado
				uartSendString("\n\n-    -   -  - --- Acceso Denegado! --- -  -   -    - \n\n\r");
				SetearEstadoLed(ESTADO_LED_ACCESO_DENY);
			}

		}
		else
		{
			if(NADA == boton)
			{
				if(delayRead(&AccesoDelayActual))
				{
					estadoActual = ESTADO_STAND_BY;
					SetearEstadoLed(ESTADO_LED_STAND_BY);
				}
			}

			if(ESC == boton)
			{
				estadoActual = ESTADO_STAND_BY;
				SetearEstadoLed(ESTADO_LED_STAND_BY);
			}
		}
		break;

	case ESTADO_ACCESO:
		if(delayRead(&AccesoDelayActual))
		{
			estadoActual = ESTADO_STAND_BY;
			SetearEstadoLed(ESTADO_LED_STAND_BY);
		}
		break;


		default:
			InicializarAcceso();
			break;
	}
}
