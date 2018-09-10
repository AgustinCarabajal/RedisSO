#include "planificador.h"

int main (void)
{
  	// Inicializo los controladores basicos del planificador
  	init();
  	printf("\n");
  	log_info(logger, "Iniciando aplicacion..");
  	puerto = malloc(10);
  	strcpy(puerto, config_get_string_value(config,"PUERTO"));

  	fprintf (stdout, "\n--------------------\n\n");
  	fprintf (stdout, "App: \tPlanificador\n");
  	fprintf (stdout, "Env: \tDevelopment\n");
  	fprintf (stdout, "Port: \t%s\n\n", puerto);
  	fprintf (stdout, "--------------------\n\n");

 	//-----------------------------------------------------------------------------------
 	//COORD:

 	puerto_coord = malloc(50);
  	ip_coord = malloc(50);

 	ip_coord = config_get_string_value(config, "IP_COORD");
  	puerto_coord = config_get_string_value(config,"PUERTO_COORD");

  	socketCoord = conectar_servidor(ip_coord,puerto_coord);

  	free(puerto_coord);
  	free(ip_coord);

 	if (socketCoord > -1) {
    	fprintf (stdout, "[Planificador] Conexion exitosa..\n");
    	send(socketCoord, "PLN", 3, 0);
    	init_tabla(socketCoord, tabla_entradas);
  	}
 	
 	//-----------------------------------------------------------------------------------

 	// Escucho las conexiones entrantes y hago el handle de las current connections
  	pthread_create(&thread_conexion, NULL, (void *) init_connections, (void *) create_listenner(puerto));
   	pthread_create(&thread_procesos, NULL, (void *) planificacion, NULL);
  	pthread_create(&thread_ejecucion, NULL, (void *) ejecucion, NULL);
  	pthread_create(&thread_consola, NULL, (void *) consola, NULL);
  
	pthread_join(thread_conexion, NULL);
	pthread_join(thread_consola, NULL);
    pthread_join(thread_procesos, NULL);


  //FINALIZO PLANI
	config_destroy(config);
    free(puerto);
    log_destroy(logger);
	log_destroy(logger_connection);

  	return 0;
}

void init() {
  create_logger();
  create_config();
  validate_config();
  init_semaforos(semaforo);
  init_semaforos(semaforo_ready);
  init_semaforos(semaforo_exe);
}

void create_logger(){
	logger = log_create(LOGGER, "Planificador", 1, LOG_LEVEL_INFO);
 	logger_connection = log_create(LOGGER, "Connection", 1, LOG_LEVEL_INFO);
}

void create_config(){
	config = config_create(CONFIG);
}


void validate_config(){

	if(!config_has_property(config, "PUERTO")||
      !config_has_property(config, "ALGORITMO")||
      !config_has_property(config, "ALFA")||
      !config_has_property(config, "ESTIMACION")||
      !config_has_property(config, "IP_COORD")||
      !config_has_property(config, "PUERTO_COORD")||
      !config_has_property(config, "CLAVES")){

		log_error(logger, "Error: archivo configuracion");
		exit(1);
	}

}



