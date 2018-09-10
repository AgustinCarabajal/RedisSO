#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <parsi/parser.h>
#include <commons/config.h>
#include <commons/log.h>
#include "script.h"
#include "conexionesESI.h"
#include <string.h>
#include "serializar.h"
#include <unistd.h>

void envio_sentencias(char* path_script,int socketPlani, int socketCoord){

	FILE* script;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int operacion;
	int estadoOperacion;
	int estadoEnvio;

	script = fopen(path_script,"r");

	if(script){

		read = getline(&line,&len,script);		
		while(read != -1 && confirmacion(socketPlani)){ 
			t_esi_operacion parsed = parse(line);

				if(parsed.valido){
					switch(parsed.keyword){
						case GET:

					 		printf("La clave del GET es:\t%s\n",parsed.argumentos.GET.clave);
					 		envio_operaciones("110",parsed.argumentos.GET.clave,socketCoord);
					 		estadoOperacion = recv(socketCoord, &operacion,sizeof(int),0);

					 		if(estadoOperacion < 0){
					 			printf("Error al recibir confirmacion de ejecucion de sentencia de coordinador\n");
					 		}

					 		estadoEnvio = send(socketPlani, &operacion, sizeof(int), 0);

					 		if(estadoEnvio < 0){
					 			printf("Error al enviar confirmacion a planificador\n");
					 		}

							break;

						case SET:

							printf("La clave del SET es\t%s\t y el valor:\t%s\n",parsed.argumentos.SET.clave, parsed.argumentos.SET.valor);
							envio_operacion_set("120",parsed.argumentos.SET.clave, parsed.argumentos.SET.valor,socketCoord);

							estadoOperacion = recv(socketCoord, &operacion,sizeof(int),0);

					 		if(estadoOperacion < 0){
					 			printf("Error al recibir confirmacion de ejecucion de sentencia de coordinador\n");
					 		}

					 		estadoEnvio = send(socketPlani, &operacion, sizeof(int), 0);

					 		if(estadoEnvio < 0){
					 			printf("Error al enviar confirmacion a planificador\n");
					 		}
						
							break;

						case STORE:

							printf("La clave del STORE es\t%s\n",parsed.argumentos.STORE.clave);
							envio_operaciones("130",parsed.argumentos.STORE.clave,socketCoord);

							estadoOperacion = recv(socketCoord, &operacion,sizeof(int),0);

					 		if(estadoOperacion < 0){
					 			printf("Error al recibir confirmacion de ejecucion de sentencia de coordinador\n");
					 		}

					 		estadoEnvio = send(socketPlani, &operacion, sizeof(int), 0);

					 		if(estadoEnvio < 0){
					 			printf("Error al enviar confirmacion a planificador\n");
					 		}
							break;

						default:

							printf("Error al parsear\n");
							break;
					}

					destruir_operacion(parsed);
				}
			read = getline(&line,&len,script);
		}
	} else{
		printf("Error al abrir el archivo\n");
		exit(1);
	}

	fclose(script);
	if(line){
		free(line);
	}

}


int confirmacion(int socket){

	int confirmacion;

	int status = recv(socket,&confirmacion,sizeof(int),0);

	if(status < 0){
		printf("error\n");
	}

	if(confirmacion == 1){
		return 1;
	}else{
		return 0;
	}
}


void envio_operaciones(char* operacion,char* clave, int socket){

	int estado = send(socket, serializar(operacion, clave), 7 + strlen(clave), 0);

	if(estado > -1){
		printf("\nSuccess\n\n");
	} else {
		printf("\nNo Success\n\n");
	}
}

void envio_operacion_set(char* operacion,char* clave, char* valor, int socket){

	int estado = send(socket, serializar_set(operacion, clave, valor), 11 + strlen(clave) + strlen(valor), 0);

	if(estado> -1) {
		printf("\nSuccess\n\n");
	} else {
		printf("\nNo Success\n\n");
	}

}