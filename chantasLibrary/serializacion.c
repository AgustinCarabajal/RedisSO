#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "serializacion.h"


char* serializarOperacion(operacion_esi* paquete){

	char* paqueteSerializado = malloc(paquete->longitud_total);

	int offset = 0;
	int size_envio;

	size_envio = sizeof(paquete->clave_long);
	memcpy(paqueteSerializado + offset, &(paquete->clave_long), size_envio);
	offset += size_envio;

	size_envio = paquete->clave_long;
	memcpy(paqueteSerializado+offset, paquete->clave,size_envio);
	offset += size_envio;

	return paqueteSerializado;
}

char* serializarOperacionSET(operacion_esi_set* paquete){

	char* paqueteSerializado = malloc(paquete->longitud_total);

	int offset = 0;
	int size_envio;

	size_envio = sizeof(paquete->clave_long);
	memcpy(paqueteSerializado + offset, &(paquete->clave_long), size_envio);
	offset += size_envio;

	size_envio = paquete->clave_long;
	memcpy(paqueteSerializado+offset, paquete->clave,size_envio);
	offset += size_envio;

	size_envio = sizeof(paquete->valor_long);
	memcpy(paqueteSerializado + offset, &(paquete->valor_long), size_envio);
	offset += size_envio;

	size_envio = paquete->valor_long;
	memcpy(paqueteSerializado+offset, paquete->valor,size_envio);
	offset += size_envio;

	return paqueteSerializado;
}



void llenar_operacion(operacion_esi* package, char** clave){

	package->clave = *clave;
	package->clave_long = strlen(*clave) +1;

	package->longitud_total =sizeof(package->clave_long)+package->clave_long;
}

void llenar_operacion_set(operacion_esi_set* package, char** clave,char** valor){

	package->clave = *clave;
	package->clave_long = strlen(*clave) +1;

	package->valor = *valor;
	package->valor_long = strlen(*valor) +1;

	package->longitud_total =sizeof(package->clave_long)+package->clave_long+sizeof(package->valor_long)+package->valor_long;
}

void eliminarPaquete(char** paquete){
	free(*paquete);
}

char* serializar(char *code, char *clave){

	int messageLength = sizeof(clave);

	char *buffer = malloc (sizeof(code) + 4 + messageLength);

	memcpy(buffer, code, sizeof(code));

	memcpy(buffer + sizeof(code), &messageLength, 4);

	memcpy(buffer + 4, clave, messageLength);

	return buffer;
}
