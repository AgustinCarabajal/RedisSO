#ifndef CONEXION
#define CONEXION


	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <sys/socket.h>
	#include <commons/log.h>
	#include <unistd.h>
	// #include "main_instancia.h"

	t_log *logger_connection;

	typedef struct{
		char* ip;
		char* puerto;
	}conexion;

	conexion instancia;

	int conectar_server(conexion instancia);
	void configuracion_definitiva(int socket);
	void freeInstancia(conexion instancia);

#endif
