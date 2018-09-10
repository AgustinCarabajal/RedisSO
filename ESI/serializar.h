#ifndef SERIALIZAR
#define SERIALIZAR

	#include <stdio.h>
	#include <stdlib.h>

	char* serializar(char* codigoOperacion, char*clave);
	char* serializar_set(char* codigoOperacion, char* clave, char* valor);
	void eliminarPaquete(char** paquete);

#endif