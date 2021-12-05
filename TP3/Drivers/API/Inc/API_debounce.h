/*
 * API_debounce.h
 *
 *  Created on: 9 nov. 2021
 *      Author: martin
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

// Nuevo tipo de datos enumerado llamado estadoMEF_t
typedef enum{
    ESTADO_B_UP,
    ESTADO_B_DOWN,
    ESTADO_B_RISING,
    ESTADO_B_FALLING
} estadoMEF_t;

// Variable de estado (global)
estadoMEF_t estadoActual;

// Prototipos de funciones
void InicializarMEF(void );
void ActualizarMEF(void);





#endif /* API_INC_API_DEBOUNCE_H_ */
