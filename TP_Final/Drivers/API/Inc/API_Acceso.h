/*
 * API_Acceso.h
 *
 *  Created on: 4 dic. 2021
 *      Author: martin
 */

#ifndef API_INC_API_ACCESO_H_
#define API_INC_API_ACCESO_H_

#include "stdint.h"
#include "stdbool.h"


// Nuevo tipo de datos enumerado llamado estadoMEF_t
typedef enum{
    ESTADO_STAND_BY,
    ESTADO_ESPERA_2,
    ESTADO_ESPERA_3,
    ESTADO_ESPERA_4,
    ESTADO_ESPERA_ENT,
	ESTADO_ACCESO
} estadoMEF_t;

// Variable de estado (global)


#define TIMEOUT 3000  // Tiempo de espera para volver a StandBy

#define DIGITO_1 2  // Clave harcodeada
#define DIGITO_2 3
#define DIGITO_3 8
#define DIGITO_4 5


void InicializarAcceso(void);
void ActualizarMEF(uint8_t boton);


#endif /* API_INC_API_ACCESO_H_ */
