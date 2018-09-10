#ifndef ESI
#define ESI

	#include <stdio.h>
	#include <stdlib.h>
	#include <commons/config.h>
	#include <commons/log.h>
	#include <arpa/inet.h>
	#include <parsi/parser.h>

	#define CONFIG "esi.config"
	#define LOGGER "esi.log"

	t_config* config;
	t_log* logger;

	int socketCoord,socketPlani;

	void inicializarESI();
	void crearLogger();
	void configurar_esi();
	void validar_config(t_config* config);
	void finalizarESI();

#endif
