#ifndef CONFIG_I
#define CONFIG_I

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <sys/socket.h>
	#include <commons/log.h>
	#include <commons/config.h>
	#include <unistd.h>
  #include "conexion.h"
  #include "analyser.h"

#define PATH_CONFIG "instancia.config"
#define PATH_LOGGER "instancia.log"
#define CODIGO "INS"

t_config* conf;
t_log* logger;

char* algoritmo_reemplazo;
char* punto_montaje;
char* nombre_instancia;
int intervalo_dump;
int cantEntradas;
int tamanioEntrada;

void iniciarInstancia(t_log *logger_connection);
void configurarInstancia(t_config* conf);
void validarConfigInstancia(t_config* conf);
void finalizarConfig(int sock);
void show_info(conexion instancia);
void liberar_memoria();

#endif
