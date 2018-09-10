#ifndef CONEXIONES
#define CONEXIONES

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <string.h>
	#include <commons/log.h>

	typedef struct{ // Estructura que contiene datos para la conexión de un socket
		char* ip;
		char* puerto;
	} datos_conexion;

	int crearSocketListener(datos_conexion serverData, t_log* serverLogger); //Crea un socket servidor y devuelve su id
	int conectarseAServer(datos_conexion clientData, t_log* clientLogger); //Crea un socket cliente y devuelve su id

#endif
