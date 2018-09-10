#ifndef SERVIDOR
#define SERVIDOR

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <pthread.h>
	#include <commons/log.h>
	#include "coordinador.h"

	void iniciarConexionConClientes();

#endif
