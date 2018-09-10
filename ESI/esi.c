#include <stdio.h>
#include <stdlib.h>
#include <commons/config.h>
#include <commons/log.h>
#include <arpa/inet.h>
#include <parsi/parser.h>
#include "conexionesESI.h"
#include "esi.h"
#include <string.h>

void finalizarESI(){
	log_destroy(logger);
	config_destroy(config);
}

void inicializarESI(){
	crearLogger();
	configurar_esi();
}

void crearLogger(){

	logger = log_create(LOGGER,"Proceso ESI",true,LOG_LEVEL_INFO);

}

void configurar_esi(){

	config = config_create(CONFIG);

	validar_config(config);

	//TO DO:googlear strdup();

	conexionCoordinador.puerto = malloc(10);
	conexionCoordinador.ip = malloc(16);
	conexionPlanificador.puerto = malloc(10);
	conexionPlanificador.ip = malloc(16);

	strcpy(conexionCoordinador.puerto,config_get_string_value(config,"PUERTO_COORDINADOR"));
	strcpy(conexionCoordinador.ip,config_get_string_value(config,"IP_COORDINADOR"));

	strcpy(conexionPlanificador.puerto,config_get_string_value(config,"PUERTO_PLANIFICADOR"));
	strcpy(conexionPlanificador.ip,config_get_string_value(config,"IP_PLANIFICADOR"));

	log_info(logger,"Configuracion de Coordinador:\tPuerto:%s\tIP:%s\n",conexionCoordinador.puerto,conexionCoordinador.ip);
	log_info(logger,"Configuracion de Planificador:\tPuerto:%s\tIP:%s\n",conexionPlanificador.puerto,conexionPlanificador.ip);

}


void validar_config(t_config* config){

	if(!config_has_property(config,"IP_COORDINADOR")||
	   !config_has_property(config,"IP_PLANIFICADOR")||
	   !config_has_property(config,"PUERTO_COORDINADOR")||
	   !config_has_property(config,"PUERTO_PLANIFICADOR")){

		log_error(logger, "Error: archivo configuracion");
		exit(1);
	}
}
