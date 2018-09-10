#ifndef PROCESOS_LIB
#define PROCESOS_LIB

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/queue.h>
#include <commons/collections/list.h>
#include <commons/collections/node.h>
#include <commons/collections/dictionary.h>
#include <sys/socket.h>
#include <pthread.h>

t_dictionary* tabla_entradas;

void init_tabla(int sock, t_dictionary* tabla_entradas);

#endif