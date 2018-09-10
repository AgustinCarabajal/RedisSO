#ifndef CONEXIONES_ESI
#define CONEXIONES_ESI


		#include <stdlib.h>
		#include <stdio.h>
		#include <arpa/inet.h>

		typedef struct{
			char* ip;
			char* puerto;
		}datos_conexion;

		datos_conexion conexionCoordinador;
		datos_conexion conexionPlanificador;

		int conectar_servidor(datos_conexion server);


#endif //CONEXIONES_ESI
