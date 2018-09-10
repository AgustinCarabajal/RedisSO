#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdint.h>
#include "deserializacion.h"



int deserializar(operacion_esi* paquete, int socket){

	int estado;
	int size_buffer;
	char* buffer = malloc(size_buffer = sizeof(uint32_t));

	uint32_t = clave_long;
	estado = recv(socket,buffer,sizeof(paquete->clave_long),0);
	memcpy(&(clave_long),buffer,size_buffer);
	if(!estado)
		return 0;

	estado = recv(socket,paquete->clave,clave_long,0);
	if(!estado)
			return 0;

	free(buffer);

	return estado;
}

int deserializar_Set(operacion_esi_set* paquete, int socket){

	int estado;
	int size_buffer;
	char* buffer = malloc(size_buffer = sizeof(uint32_t));

	uint32_t = clave_long;
	estado = recv(socket,buffer,sizeof(paquete->clave_long),0);
	memcpy(&(clave_long),buffer,size_buffer);
	if(!estado)
		return 0;

	estado = recv(socket,paquete->clave,clave_long,0);
	if(!estado)
			return 0;


	uint32_t = valor_long;
	estado = recv(socket,buffer,sizeof(paquete->valor_long),0);
	memcpy(&(valor_long),buffer,size_buffer);
	if(!estado)
		return 0;

	estado = recv(socket,buffer,paquete->valor,valor_long,0);
	if(!estado)
		return 0;

	free(buffer);

	return estado;
}
