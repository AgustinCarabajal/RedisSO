#include "main_coordinador.h"

int main(void){
	
	inicializarCoordinador();
	iniciarConexionConClientes();
	finalizarCoordinador();
	return 0;
}


void inicializarCoordinador(){
	iniciarLogs();
	log_info(log_Config,"Iniciando aplicacion...\n");
	log_info(log_Config,"Cargando datos...");
	iniciarArchivoConfig();
	iniciarSemaforo(sem_config);
	iniciarSemaforo(sem_lista);
	iniciarListaInstancias();

	printf ("\n--------------------\n\n");
 	printf ("App: \tCoordinador\n");
	printf ("Port: \t%s\n\n", config_get_string_value(archivo,"PUERTO"));
	printf ("--------------------\n\n");
	
}

void finalizarCoordinador(){
	free(puerto);
	log_destroy(log_Config);
	log_destroy(log_operacion);
	config_destroy(archivo);
}