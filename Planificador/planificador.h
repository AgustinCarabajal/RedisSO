#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <commons/log.h>
#include <commons/config.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include "connection.h"
#include "pcblib.h"
#include "claves.h"
#include "consola_planificador.h"
#include "planificador.h"


#define CONFIG "plani.config"
#define LOGGER "planificador.log"

char *puerto;

pthread_t thread_conexion;
pthread_t thread_consola;
pthread_t thread_procesos;
pthread_t thread_ejecucion;

void init();

void create_logger();
void create_config();
void validate_config();
void init_connections(int sock);



#endif