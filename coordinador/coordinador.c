#include "coordinador.h"
#include "servidor.h"
#include "cliente.h"
#include <commons/collections/list.h>

void iniciarLogs(){
	log_Config =log_create(ARCHIVO_LOG,"Archivo_De_Configuracion",1,LOG_LEVEL_INFO);
	log_operacion = log_create(ARCHIVO_LOG,"Operaciones",1,LOG_LEVEL_INFO);
}

void iniciarArchivoConfig(){

	archivo = config_create(ARCHIVO_CONFIG);
	seAbrioBien();
	puerto = malloc(5);
	strcpy(puerto, config_get_string_value(archivo,"PUERTO"));
	algoritmo = malloc(4);
	strcpy(algoritmo,config_get_string_value(archivo,"ALGORITMO_DE_DISTRIBUCION"));

}

void seAbrioBien(){

	if(!(config_has_property(archivo,"PUERTO"))||
	!(config_has_property(archivo,"ALGORITMO_DE_DISTRIBUCION"))||
	!(config_has_property(archivo,"CANTIDAD_DE_ENTRADAS"))||
	!(config_has_property(archivo,"TAMANIO_DE_ENTRADAS"))||
	!(config_has_property(archivo,"RETARDO"))){

		log_error(log_Config,"Error al crear el archivo de configuracion");
		exit(1);
	}else{
		log_info(log_Config,"El archivo de configuracion se ha iniciado correctamente");

	}
}

void logueandoConexion(int tipoMensaje, char* mensaje){

	//Si el tipoMensaje es 0 significa que hay que loguear un error, si es uno se loguea una info
	if(tipoMensaje ==1){
		log_info(log_Config,mensaje);
	}else{
		log_error(log_Config,mensaje);
	}
}

void iniciarSemaforo(pthread_mutex_t sem) {
	if (pthread_mutex_init(&sem, NULL) != 0)
    {
        printf("\nError: Mutex Failed\n");
        exit(1);
    }
}

void iniciarListaInstancias(){
	instancias = list_create();
}