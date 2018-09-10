#ifndef CONEXION_CLIENTES
#define CONEXION_CLIENTES


	#include <stdio.h>
	#include <stdlib.h>	
	#include <string.h>
	#include <commons/collections/list.h>


	typedef struct {
		int servidor;
		int cliente;
	}proceso;

	#define MAX_CONEXIONES 5	
	#define PACKAGESIZE 1024

	proceso* datos;
	t_list* instancias;

	typedef struct{
		int identificador;
		int cantVecesElegida;
	}datos_instancia;

	int socketPlani;

	char* entradas;
	int header_entradas;
	char* size;
	int header_size;
  	char* mensaje;

	pthread_t conexion;
	pthread_mutex_t sem_config,sem_lista;

	// void aplicarConexion(int listeningSocket);
	void operaciones(proceso* datos);
	void send_config(proceso* datos);
	void send_plani(proceso* datos);
	void agregarALista(int identificador);
	// void recv_serializado(int sock);
	char *get_value(int sock);
	char *get_key(int sock);
	char* serializar(char *code, char *clave);

#endif	
