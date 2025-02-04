/*
 * API_Teclado.c
 *
 *  Created on: 3 dic. 2021
 *      Author: martin
 */



#include "API_delay.h"
#include "API_Teclado.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#define DURACION 10

// Variable de estado (global)


static delay_t timeToCheck;
static uint8_t columna;
static uint8_t fila;
static uint8_t tecla;
static uint8_t valor;
static uint8_t retorno;
static uint8_t antiRebo;


void InicializarTeclado(void)
{
	columna = COLUMNA_1; // El teclado tiene 4 columnas, comenzamos por la 1ª

	delayInit(&timeToCheck, 50); // Iniciamos el timer para ir multiplexando el chequeo

	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOF_CLK_ENABLE();
	  __HAL_RCC_GPIOE_CLK_ENABLE();
	  __HAL_RCC_GPIOG_CLK_ENABLE();


	  GPIO_InitStruct.Pin = T_O1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	  HAL_GPIO_Init(T_O1_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = T_O2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	  HAL_GPIO_Init(T_O2_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = T_O3_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	  HAL_GPIO_Init(T_O3_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = T_O4_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	  HAL_GPIO_Init(T_O4_GPIO_Port, &GPIO_InitStruct);



	  GPIO_InitStruct.Pin = T_I1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(T_I1_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = T_I2_Pin|T_I3_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(T_I2_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = T_I4_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(T_I4_GPIO_Port, &GPIO_InitStruct);



	  HAL_GPIO_WritePin(T_O1_GPIO_Port, T_O1_Pin, GPIO_PIN_SET);  // encendemos la 1ª columna
	  HAL_GPIO_WritePin(T_O2_GPIO_Port, T_O2_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(T_O3_GPIO_Port, T_O3_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(T_O4_GPIO_Port, T_O4_Pin, GPIO_PIN_RESET);




	  tecla = 0;
	  valor = NADA;

}

// Función Actualizar MEF
uint8_t ChkTeclado(void)
{
	retorno = NADA;//NADA; // valor por defecto con el cual retornar.

	if(delayRead(&timeToCheck)) // verificamos si es momento de cambiar de columna
	{

		fila = ChkFila(); // verificamos
		switch (columna)
		{
			case COLUMNA_1:

				if(0 == antiRebo)
				{
					if(0 == fila)
					{
						HAL_GPIO_WritePin(T_O1_GPIO_Port, T_O1_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(T_O2_GPIO_Port, T_O2_Pin, GPIO_PIN_SET);
						columna = COLUMNA_2;
					}
					else
					{
						if(1 == fila) {
							valor = A_LEFT;
						}
						if(2 == fila){
							valor = 7;
						}
						if(3 == fila){
							valor = 4;
						}
						if(4 == fila){
							valor = 1;
						}
						antiRebo = 1;
						tecla = fila;
					}

				}
				else
				{
					if(ESPERA_SOLTAR > antiRebo)  // 60 ms
					{
						antiRebo++;

						if(RECHEKEAR == antiRebo) // Pasaron 40 ms, es momento de volver a chequear si sigue presionado el boton
						{
							if(tecla != fila) // si no sigue presionado el mismo boton
							{
								antiRebo = 0;	// se reinicia todas las variables
								tecla = 0;
								valor = NADA;
							}
						}
					}
					else
					{
						if(0 == fila) // Verificamos si ya se solto el boton
						{
							retorno = valor;
							antiRebo = 0;
							tecla = 0;
							valor = 0;
						}
					}
				}
				break;

			case COLUMNA_2:

				if(0 == antiRebo)
				{
					if(0 == fila)
					{
						HAL_GPIO_WritePin(T_O2_GPIO_Port, T_O2_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(T_O3_GPIO_Port, T_O3_Pin, GPIO_PIN_SET);
						columna = COLUMNA_3;
					}
					else
					{
						if(1 == fila) valor = 0;
						if(2 == fila) valor = 8;
						if(3 == fila) valor = 5;
						if(4 == fila) valor = 2;
						antiRebo = 1;
						tecla = fila;
					}

				}
				else
				{
					if(ESPERA_SOLTAR > antiRebo)  // 60 ms
					{
						antiRebo++;

						if(RECHEKEAR == antiRebo) // Pasaron 40 ms, es momento de volver a chequear si sigue presionado el boton
						{
							if(tecla != fila) // si no sigue presionado el mismo boton
							{
								antiRebo = 0;	// se reinicia todas las variables
								tecla = 0;
								valor = NADA;
							}
						}
					}
					else
					{
						if(0 == fila) // Verificamos si ya se solto el boton
						{
							retorno = valor;
							antiRebo = 0;
							tecla = 0;
							valor = 0;
						}
					}
				}
				break;


			case COLUMNA_3:

				if(0 == antiRebo)
				{
					if(0 == fila)
					{
						HAL_GPIO_WritePin(T_O3_GPIO_Port, T_O3_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(T_O4_GPIO_Port, T_O4_Pin, GPIO_PIN_SET);
						columna = COLUMNA_4;
					}
					else
					{
						if(1 == fila) valor = A_RIGHT;
						if(2 == fila) valor = 9;
						if(3 == fila) valor = 6;
						if(4 == fila) valor = 3;
						antiRebo = 1;
						tecla = fila;
					}

				}
				else
				{
					if(ESPERA_SOLTAR > antiRebo)  // 60 ms
					{
						antiRebo++;

						if(RECHEKEAR == antiRebo) // Pasaron 40 ms, es momento de volver a chequear si sigue presionado el boton
						{
							if(tecla != fila) // si no sigue presionado el mismo boton
							{
								antiRebo = 0;	// se reinicia todas las variables
								tecla = 0;
								valor = NADA;
							}
						}
					}
					else
					{
						if(0 == fila) // Verificamos si ya se solto el boton
						{
							retorno = valor;
							antiRebo = 0;
							tecla = 0;
							valor = 0;
						}
					}
				}
				break;


			case COLUMNA_4:

				if(0 == antiRebo)
				{
					if(0 == fila)
					{
						HAL_GPIO_WritePin(T_O4_GPIO_Port, T_O4_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(T_O1_GPIO_Port, T_O1_Pin, GPIO_PIN_SET);
						columna = COLUMNA_1;
					}
					else
					{
						if(1 == fila) valor = ENT;
						if(2 == fila) valor = ESC;
						if(3 == fila) valor = A_DOWN;
						if(4 == fila) valor = A_UP;
						antiRebo = 1;
						tecla = fila;
					}

				}
				else
				{
					if(ESPERA_SOLTAR > antiRebo)  // 60 ms
					{
						antiRebo++;

						if(RECHEKEAR == antiRebo) // Pasaron 40 ms, es momento de volver a chequear si sigue presionado el boton
						{
							if(tecla != fila) // si no sigue presionado el mismo boton
							{
								antiRebo = 0;	// se reinicia todas las variables
								tecla = 0;
								valor = NADA;
							}
						}
					}
					else
					{
						if(0 == fila) // Verificamos si ya se solto el boton
						{
							retorno = valor;
							antiRebo = 0;
							tecla = 0;
							valor = 0;
						}
					}
				}
				break;


			default:
				InicializarTeclado();
				break;
		}
	}

	return retorno;

}

uint8_t ChkFila(void){

	if(HAL_GPIO_ReadPin(T_I1_GPIO_Port, T_I1_Pin)) return 1;
	if(HAL_GPIO_ReadPin(T_I2_GPIO_Port, T_I2_Pin)) return 2;
	if(HAL_GPIO_ReadPin(T_I3_GPIO_Port, T_I3_Pin)) return 3;
	if(HAL_GPIO_ReadPin(T_I4_GPIO_Port, T_I4_Pin)) return 4;

	return 0; // Si no hay ninguna tecla presionada
}
