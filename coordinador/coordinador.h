#ifndef COORDINADOR
#define COORDINADOR

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <commons/log.h>
	#include <commons/config.h>
	#include <pthread.h>
	#include "servidor.h"
	
	#define ARCHIVO_LOG  "coordinador.log"
	#define ARCHIVO_CONFIG "archivoCoordinador.config"

	t_log *log_Config;
	t_log *log_operacion;
	t_config *archivo;

	char* puerto;
	static char* algoritmo;

	void iniciarLogs();
	void iniciarArchivoConfig();
	void seAbrioBien();
	char* RetornarPuerto();
	int retornarAlgoritmo();
	void logueandoConexion(int tipoMensaje,char* mensaje);
	void iniciarSemaforo(pthread_mutex_t sem);
	void iniciarListaInstancias();


#endif

