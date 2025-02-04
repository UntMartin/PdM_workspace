/*
 * API_Teclado.h
 *
 *  Created on: 3 dic. 2021
 *      Author: martin
 */

#ifndef API_INC_API_TECLADO_H_
#define API_INC_API_TECLADO_H_

#include "stdint.h"
#include "stdbool.h"

#define T_O1_Pin GPIO_PIN_9
#define T_O1_GPIO_Port GPIOG
#define T_O2_Pin GPIO_PIN_14
#define T_O2_GPIO_Port GPIOG
#define T_O3_Pin GPIO_PIN_15
#define T_O3_GPIO_Port GPIOF
#define T_O4_Pin GPIO_PIN_13
#define T_O4_GPIO_Port GPIOE

#define T_I1_Pin GPIO_PIN_14
#define T_I1_GPIO_Port GPIOF
#define T_I2_Pin GPIO_PIN_11
#define T_I2_GPIO_Port GPIOE
#define T_I3_Pin GPIO_PIN_9
#define T_I3_GPIO_Port GPIOE
#define T_I4_Pin GPIO_PIN_13
#define T_I4_GPIO_Port GPIOF


typedef enum{
    COLUMNA_1,
	COLUMNA_2,
	COLUMNA_3,
	COLUMNA_4
} Teclado_t;

typedef enum{
    NADA = 100,
	ENT,
	ESC,
	A_UP,
	A_DOWN,
	A_LEFT,
	A_RIGHT
} TeclasNoNum_t;

#define RECHEKEAR 4      // Cantidad de entradas a la rutina de teclado (40ms), a partir del cual se vuelve a chequear la tecla presionada, para evitar el rebote y confirmar el boton presionado
#define ESPERA_SOLTAR 5  // Cantidad de entradas a la rutina de teclado (50ms), a partir del cual queda a la espera de que se suelte el boton


void InicializarTeclado(void); // Inicializa el Teclado, configurando los pines que usa, e inicializando el delay.

uint8_t ChkTeclado(void); // Esta Fn devuelve el valor de la tecla presionada, cuando se suelta el boton. devuele 100
						  // si no hay nada presionado. 101 al presionar enter y 102 al presionar escape

uint8_t ChkFila(void); // Esta Fn indica cual es la Fila en la que se presiono un boton.

#endif /* API_INC_API_TECLADO_H_ */
