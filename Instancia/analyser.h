#ifndef ANALYSER_H
#define ANALYSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <commons/config.h>
#include <commons/log.h>
#include <commons/collections/dictionary.h>
#include <commons/collections/node.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <commons/txt.h>

#define MAX_SIZE 30

t_hash_element* first;
t_hash_element* algoritmo;
t_dictionary* tabla_entradas;
t_log* logger;
FILE* keys;



// Habria que mandarlo para el plani
void ser_key(char* key,char* valor);
void get_key(char *key,int sock);

// Setea un valor en la key, si la key no existe la crea
void set_key(char *key, char *val);

// Se encargar de setear el valor en el caso de que la key exista
void set_value(char *key, char *val);

// Busca el hash correspondiente a una key dada
static unsigned int get_hash(char *key, int key_len);

// Obtiene las sentencias enviadas por el coordinador
int get_operations(int sock, t_log* log);

// Analiza el tipo de operacion que llega desde el coordinador
void analizar(char *operador, int sock);

#endif
