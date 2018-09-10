#include <stdio.h>
#include <stdlib.h>
#include <commons/config.h>
#include <commons/log.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <parsi/parser.h>
#include <unistd.h>
#include "esi.h"
#include "script.h"
#include <netdb.h>
#include "conexionesESI.h"


int main(int argc, char* argv[]){

	inicializarESI();

	printf("------------------------------------------------------------\n");
	log_info(logger,"Conectandose con Coordinador..");
	socketCoord = conectar_servidor(conexionCoordinador);
	log_info(logger,"Conectado a Coordinador");
	

	printf("------------------------------------------------------------\n");
	log_info(logger,"Conectandose con Planificador");
	socketPlani = conectar_servidor(conexionPlanificador);
	log_info(logger,"Conectado a Planificador");
	printf("------------------------------------------------------------\n");

	//libero la memoria de las conexiones
	free(conexionCoordinador.puerto);
	free(conexionCoordinador.ip);
	free(conexionPlanificador.puerto);
	free(conexionPlanificador.ip);


	envio_sentencias(argv[1],socketPlani,socketCoord); //hago funcionalidad de esi.


	finalizarESI();
	close(socketPlani);
	close(socketCoord);
	return 0;
}


