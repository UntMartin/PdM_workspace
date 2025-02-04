/*
 * API_Leds.h
 *
 *  Created on: 4 dic. 2021
 *      Author: martin
 */

#ifndef API_INC_API_LEDS_H_
#define API_INC_API_LEDS_H_

#include "stdint.h"
#include "stdbool.h"
#include "API_delay.h"


typedef enum{
    ESTADO_LED_STAND_BY,
    ESTADO_LED_ESPERA,
	ESTADO_LED_ACCESO_OK,
	ESTADO_LED_ACCESO_DENY
} estadoLEDs_t;



#define DELAY_STAND_BY_ON 70
#define DELAY_STAND_BY_OFF 1000
#define DELAY_ESPERA 200

void InicializarLeds(void);
void ActualizarLeds(void);
void SetearEstadoLed(uint8_t nuevoEstado);

#endif /* API_INC_API_LEDS_H_ */
