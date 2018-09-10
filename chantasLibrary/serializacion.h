#ifndef SERIALIZACION
#define SERIALIZACION

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


	char* serializarOperacion(operacion_esi* paquete);
	char* serializarOperacionSET(operacion_esi_set* paquete);
	void llenar_operacion(operacion_esi* package, char** clave);
	void llenar_operacion_set(operacion_esi_set* package, char** clave,char** valor);
	void eliminarPaquete(char** paquete);
	char* serializar(char *code, char *clave);


#endif
