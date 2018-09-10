/*
 * deserializacion.h
 *
 *  Created on: 11 may. 2018
 *      Author: utnso
 */

#ifndef DESERIALIZACION_H_
#define DESERIALIZACION_H_

 	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <stdint.h>


	typedef struct{
		char* clave;
		uint32_t clave_long;
		uint32_t longitud_total;
	}__attribute__((packed))
	operacion_esi;

	typedef struct{
		char* clave;
		uint32_t clave_long;
		char* valor;
		uint32_t valor_long;
		uint32_t longitud_total;
	}__attribute__((packed))
	operacion_esi_set;

	int deserializar(operacion_esi* paquete, int socket);
	int deserializar_Set(operacion_esi_sets* paquete, int socket);

#endif /* DESERIALIZACION_H_ */
