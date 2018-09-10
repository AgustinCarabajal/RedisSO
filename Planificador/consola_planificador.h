#ifndef CONSOLA_PLANIFICADOR
#define CONSOLA_PLANIFICADOR

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "pcblib.h"
	#include <unistd.h>
	#include <pthread.h>
	#include "planificacion.h"

	void consola();
	void show_help();
	void pausar();
	void listar_esi();
	void continuar();

#endif
