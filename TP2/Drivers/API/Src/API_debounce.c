/*
 * API_debounce.c
 *
 *  Created on: 9 nov. 2021
 *      Author: martin
 */

#include "API_debounce.h"
#include "API_delay.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#define DURACION 40

// Variable de estado (global)


static delay_t tiempo;




void InicializarMEF(void)
{
	estadoActual = ESTADO_B_UP;
	delayInit(&tiempo, DURACION);
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
}

// Función Actualizar MEF
void ActualizarMEF(void)
{
	switch (estadoActual)
	{
		case ESTADO_B_UP:
			if(BSP_PB_GetState(BUTTON_USER))
			{
				delayStart(&tiempo);
				estadoActual = ESTADO_B_FALLING;
			}
			break;

		case ESTADO_B_FALLING:
			if(delayRead(&tiempo))
			{
				if(BSP_PB_GetState(BUTTON_USER)) estadoActual = ESTADO_B_DOWN;
				else estadoActual = ESTADO_B_UP;
			}
			break;
		case ESTADO_B_DOWN:
			if(!BSP_PB_GetState(BUTTON_USER))
			{
				delayStart(&tiempo);
				estadoActual = ESTADO_B_RISING;
			}
			break;

		case ESTADO_B_RISING:
			if(delayRead(&tiempo))
			{
				if(!BSP_PB_GetState(BUTTON_USER)) estadoActual = ESTADO_B_UP;
				else estadoActual = ESTADO_B_DOWN;
			}
			break;

		default:
			InicializarMEF();
			break;
	}
}
