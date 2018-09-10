#include "conexionesESI.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>


int conectar_servidor(datos_conexion server){

	struct addrinfo hints;
	struct addrinfo *serverInfo;

	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(server.ip,server.puerto,&hints,&serverInfo);

	int socketServer = socket(serverInfo->ai_family,serverInfo->ai_socktype,serverInfo->ai_protocol);

	if(socketServer < 0){
		perror("error socket");
		exit(1);
	}

	int conexion = connect(socketServer,serverInfo->ai_addr,serverInfo->ai_addrlen);

	if(conexion < 0){
		perror("Error");
		exit(1);
	}
	freeaddrinfo(serverInfo);

	return socketServer;
}




