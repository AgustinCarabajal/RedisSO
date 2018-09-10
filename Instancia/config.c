#include "config.h"

void iniciarInstancia(t_log *logger_connection){
	logger = log_create(PATH_LOGGER, "Instancia" , 1, LOG_LEVEL_INFO);
	logger_connection = log_create(PATH_LOGGER, "Conexion" , 1, LOG_LEVEL_INFO);
	conf = config_create(PATH_CONFIG);
	configurarInstancia(conf);

}


void configurarInstancia(t_config* conf){

	validarConfigInstancia(conf);

	instancia.ip = malloc(20);
	instancia.puerto=malloc(20);
	algoritmo_reemplazo = malloc(10);
	punto_montaje = malloc(100);

	strcpy(instancia.ip, config_get_string_value(conf,"IP_COORDINADOR"));
	strcpy(instancia.puerto, config_get_string_value(conf,"PUERTO_COORDINADOR"));
	strcpy(algoritmo_reemplazo, config_get_string_value(conf,"ALGORITMO_REEMPLAZO"));
	strcpy(punto_montaje,config_get_string_value(conf,"PUNTO_MONTAJE"));
	// strcpy(nombre_instancia, config_get_string_value(conf,"NOMBRE"));

	intervalo_dump = config_get_int_value(conf, "INTERVALO_DUMP");
}

void validarConfigInstancia(t_config* conf){

	if(!config_has_property(conf, "IP_COORDINADOR")||
		!config_has_property(conf, "PUERTO_COORDINADOR")||
		!config_has_property(conf, "ALGORITMO_REEMPLAZO")||
		!config_has_property(conf,"PUNTO_MONTAJE")||
		!config_has_property(conf,"NOMBRE")||
		!config_has_property(conf,"INTERVALO_DUMP")){

		log_error(logger,"Error de configuracion: faltan datos");
		exit(1);
	}
}


// //REPENSAR CON VARIOS RECV

void finalizarConfig(int sock){

	int header;
	char aux[2];
	char *buffer;

	// Inicializo la tabla de entradas
	tabla_entradas = dictionary_create();
	// Asigno un tamanio maximo a la tabla
	tabla_entradas -> table_max_size = 10000;

	log_info(logger,"Esperando datos de configuracion..");

	// Recibo la cantidad de entradas
	if(recv(sock, aux, 1, 0) < 0) {
		perror("Error al recibir la configuracion [Header 1]");
	} else {
		// Realizo el casteo del entero que recibo como header
		header = aux[0] - 48;
		// printf("\nMensaje Recibido: %d\n", header);

		// Recibo el buffer con el tamaño del header
		buffer = malloc(header + 1);
		if(recv(sock, buffer, header, 0) < 0) {
			perror("Error al recibir la configuracion [buffer 1]");
		} else {
			// Agrego la cantidad de entradas
			tabla_entradas -> elements_amount = atoi(buffer);
			printf("\nCantidad de entradas asignadas: %d\n", tabla_entradas -> elements_amount);
			free(buffer);
		}
	}

	// Recibo el tamanio de las entradas
	if(recv(sock, aux, 1, 0) < 0) {
		perror("Error al recibir la configuracion [Header 2]");
	} else {
		// Realizo el casteo del entero que recibo como header
		header = aux[0] - 48;
		// printf("\nMensaje Recibido: %d\n", header);

		// Recibo el buffer con el tamaño del header
		buffer = malloc(header + 1);
		if(recv(sock, buffer, header, 0) < 0) {
			perror("Error al recibir la configuracion [buffer 2]");
		} else {

			// calculo el tamanio de la tabla con la cantidad de entradas * el tamanio de cada una
			tabla_entradas -> table_current_size = tabla_entradas -> elements_amount * atoi(buffer);
			printf("\nTamanio de cada entrada: %s\n", buffer);
			printf("\nTamanio de la tabla: %d\n\n", tabla_entradas -> table_current_size);
			free(buffer);
		}
	}
}

void show_info(conexion instancia) {
	printf("----------------------------\n\n");
	printf("App:\t\tInstancia\n");
	printf("Env:\t\tDesarrollo\n");
	printf("IP:\t\t%s\n", instancia.ip);
	printf("Port:\t\t%s\n\n", instancia.puerto);
	printf("----------------------------\n\n");
}

void liberar_memoria() {
  freeInstancia(instancia);
  log_destroy(logger);
  config_destroy(conf);
  free(algoritmo_reemplazo);
  free(punto_montaje);
}
