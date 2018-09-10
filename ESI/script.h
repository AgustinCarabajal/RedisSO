#ifndef SCRIPT_H
#define SCRIPT_H

	#include <stdio.h>
	#include <stdlib.h>

	void envio_sentencias(char* path_script,int socketPlani,int socketCoord);
	int confirmacion(int socket);
	char* serializar(char *code, char *clave);
	char* serializar_set(char *code, char *clave, char *valor);
	void eliminarPaquete(char** buffer);
	void envio_operaciones(char* operacion, char* clave, int socket);
	void envio_operacion_set(char* operacion, char* clave, char* valor, int socket);




#endif
