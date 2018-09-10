#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "serializacion.h"

#define IP "127.0.0.1"
#define PUERTO "6667"
#define PACKAGESIZE 1024	// Define cual va a ser el size maximo del paquete a enviar

int main(){

	/*
	 *  ¿Quien soy? ¿Donde estoy? ¿Existo?
	 *
	 *  Estas y otras preguntas existenciales son resueltas getaddrinfo();
	 *
	 *  Obtiene los datos de la direccion de red y lo guarda en serverInfo.
	 *
	 */
	struct addrinfo hints;
	struct addrinfo *serverInfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		// Permite que la maquina se encargue de verificar si usamos IPv4 o IPv6
	hints.ai_socktype = SOCK_STREAM;	// Indica que usaremos el protocolo TCP

	getaddrinfo(IP, PUERTO, &hints, &serverInfo);	// Carga en serverInfo los datos de la conexion


	/*
	 * 	Ya se quien y a donde me tengo que conectar... ¿Y ahora?
	 *	Tengo que encontrar una forma por la que conectarme al server... Ya se! Un socket!
	 *
	 * 	Obtiene un socket (un file descriptor -todo en linux es un archivo-), utilizando la estructura serverInfo que generamos antes.
	 *
	 */
	int serverSocket;
	serverSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
  
  operacion_esi *paquete;
  
  freeaddrinfo(serverInfo);	

	if (connect(serverSocket, serverInfo->ai_addr, serverInfo->ai_addrlen) > -1) {
    printf("Conectado al servidor. Bienvenido al sistema, ya puede enviar mensajes. Escriba 'exit' para salir\n");
    
    paquete = malloc (sizeof(operacion_esi));
    paquete -> clave = malloc(7);

    strcpy(paquete -> clave, "EJEMPLO");
    printf("%s", paquete -> clave);

    send (serverSocket, serializarOperacion(paquete), 4 + sizeof(paquete -> clave), 0);

    printf("Envio exitoso");
  }
	
	close(serverSocket);
	return 0;

	/* ADIO'! */
}