#ifndef PLANIFICACION
#define PLANIFICACION

	#include <stdlib.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <pthread.h>
	#include "pcblib.h"
	#include "claves.h"


	static pcb *ready = NULL;
 	static pcb *locked= NULL;
 	static pcb *incoming = NULL;
 	static pcb *running = NULL;	

	
	static t_config* config;
	t_log* logger;

 	fd_set active_fd_set, read_fd_set;

	int socketCoord;

	void planificacion();
	void planificar_esi();
	void free_incoming();
	int replanificar_esi();
	void ejecucion();
	char *get_key(int sock);





#endif