#include "cliente.h"
#include "servidor.h"
#include "coordinador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "serializacion.h"

char *get_key(int sock) {

	char *key;
	int keyLength;

	recv(sock, &keyLength, 4, 0);
	key = malloc(keyLength);
	recv(sock, key, keyLength, 0);
	
	key[keyLength] = '\0';

	return key;
}

char *get_value(int sock) {

	char *value;
	int valueLength;

	recv(sock, &valueLength, 4, 0);
	value = malloc(valueLength);
	recv(sock, value, valueLength, 0);
	
	value[valueLength] = '\0';

	return value;
}

void operaciones(proceso* datos) {
  
  mensaje = malloc(4);
  int estado_Proceso = recv(datos -> cliente, mensaje, 3, 0);
  
  if(estado_Proceso >= 0){
			
		logueandoConexion(1,"Conexion entrante..\n");
		mensaje[3] = '\0';

		if(!strcmp(mensaje, "ESI")){ 
			free(mensaje);
			printf("---------------- ESI Conectado con ID: %d ----------------\n\n", datos -> cliente);

			char *code = malloc(4);
			recv(datos -> cliente, code, 3, 0);
			code[3] = '\0';

			char *clave = get_key(datos -> cliente);
			// printf("\n\nCODIGO: %s\n\n", code);
			printf("\nHERE\n");
			// SET -> Seguir con instancia
			if (!strcmp(code, "120")) {
				free(code);
				char *valor = get_value(datos -> cliente);

			} else
				
			// GET -> Seguir con plani
			if (!strcmp(code, "110")) {
				free(code);

				// Me conecto al plani y le mando la clave con la operacion GET
				printf("\n\nMANDANDO: %s - %d\n\n", clave, socketPlani);
				send(socketPlani, serializar("110", clave), strlen(clave) + 7, 0);

			}

			// free(clave);
			// checkeo_operacion();
			// instancia = algortimo_distribucion();

			// sends(instancia,algo)

			//cuando me mande clave 
			//me fijo si es get --> ida y vuelta con plani
			//tengo que llamar a algortimo y elegir instancia
			//envio clave a instancia
			//instancia retorna ok
			//envio a esi.
			
			//TODO: Q pasa si instancia retorna no ok.

		}else
		
		if (!strcmp(mensaje, "INS")) {
			free(mensaje);
			printf("---------------- Instancia Conectada con ID: %d ----------------\n\n", datos -> cliente);
			
			pthread_mutex_lock(&sem_config);
			send_config(datos);
			pthread_mutex_unlock(&sem_config);		

			pthread_mutex_lock(&sem_lista);
			agregarALista(datos->cliente);
			pthread_mutex_unlock(&sem_lista);
		
		} else 

		if (!strcmp(mensaje, "PLN")) {
			free(mensaje);
			printf("---------------- Planificador Conectado con ID: %d ----------------\n\n", datos -> cliente);
			socketPlani = datos -> cliente;
			send_config(datos);
		}
		free(datos);		
	}
}

void send_config(proceso* datos) {
	
	printf("[Instancia %d] Preparando los datos para enviar la configuracion..\n", datos -> cliente);

	archivo = config_create(ARCHIVO_CONFIG);

	if(!config_has_property(archivo,"CANTIDAD_DE_ENTRADAS")) {
		perror("Error en la config");
	}

	header_entradas = sizeof(config_get_string_value(archivo, "CANTIDAD_DE_ENTRADAS"));
	entradas = malloc(header_entradas);
	entradas = config_get_string_value(archivo, "CANTIDAD_DE_ENTRADAS");

	header_size = sizeof(config_get_string_value(archivo, "TAMANIO_DE_ENTRADAS"));
	size = malloc(header_entradas);
	size = config_get_string_value(archivo, "TAMANIO_DE_ENTRADAS");
	
	printf("[Instancia %d] Serializando..\n", datos -> cliente);
	
	char* buffer= malloc(header_entradas + header_size);
	
	strcpy(buffer,serializarEntradas(entradas,size));
	

	printf("[Instancia %d] Enviando datos de configuracion..\n", datos -> cliente);

	if (send(datos -> cliente, buffer, strlen(buffer)+1, 0) >= 0) {
		printf("[Instancia %d] Configuracion enviada correctamente!\n\n", datos -> cliente);
	}
	
	free (buffer);
	config_destroy(archivo);

}

void send_plani(proceso* datos) {
	
	printf("[Planificador %d] Preparando los datos para enviar la configuracion..\n", datos -> cliente);

	archivo = config_create(ARCHIVO_CONFIG);

	if(!config_has_property(archivo,"CANTIDAD_DE_ENTRADAS")) {
		perror("Error en la config");
	}

	header_entradas = sizeof(config_get_string_value(archivo, "CANTIDAD_DE_ENTRADAS"));
	entradas = malloc(header_entradas);
	entradas = config_get_string_value(archivo, "CANTIDAD_DE_ENTRADAS");

	header_size = sizeof(config_get_string_value(archivo, "TAMANIO_DE_ENTRADAS"));
	size = malloc(header_entradas);
	size = config_get_string_value(archivo, "TAMANIO_DE_ENTRADAS");
	
	printf("[Planificador %d] Serializando..\n", datos -> cliente);
	
	char* buffer= malloc(header_entradas + header_size);
	
	strcpy(buffer,serializarEntradas(entradas,size));
	

	printf("[Planificador %d] Enviando datos de configuracion..\n", datos -> cliente);

	if (send(datos -> cliente, buffer, strlen(buffer)+1, 0) >= 0) {
		printf("[Planificador %d] Configuracion enviada correctamente!\n\n", datos -> cliente);
	}
	
	free (buffer);
	config_destroy(archivo);

}


void agregarALista(int identificador){
	
	datos_instancia *nuevaInstancia = malloc(sizeof(datos_instancia));

	nuevaInstancia -> identificador = identificador;
	nuevaInstancia -> cantVecesElegida = 0;


	list_add(instancias,nuevaInstancia);

}

char* serializar(char *code, char *clave){

	int len = strlen(code);
	int messageLength = strlen(clave);

	char *buffer = malloc (len + 4 + messageLength);

	memcpy(buffer, code, len);
	memcpy(buffer + len, &messageLength, 4);
	memcpy(buffer + len + 4, clave, messageLength);

	return buffer;
}