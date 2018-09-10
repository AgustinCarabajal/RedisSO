#include "conexion.h"


int conectar_server(conexion instancia){ //same as esi

	struct addrinfo hints;
	struct addrinfo* serverInfo;

	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(instancia.ip,instancia.puerto,&hints,&serverInfo);

	int socketServer = socket(serverInfo->ai_family,serverInfo->ai_socktype,serverInfo->ai_protocol);

	if(socketServer < 0){
		perror("error socket");
		exit(1);
	}

	int conexion = connect(socketServer,serverInfo->ai_addr,serverInfo->ai_addrlen);

	if(conexion < 0){
		perror("error conexion");
		exit(1);
	}

	freeaddrinfo(serverInfo);

	return socketServer;
}


void configuracion_definitiva(int socketServer){

	char* identificador = "instancia";
	char buffer[50];
	int tamanioBuffer;

	send(socketServer,identificador,strlen(identificador)+1,0);

	int status = recv(socketServer,(void *)buffer,strlen(buffer)+1,0);

	tamanioBuffer = strlen(buffer)+1;


	if(status < 0){
		log_error(logger_connection,"Error al recibir configuracion");
	}else{

		//finalizarConfig(buffer);
	}

}

void freeInstancia(conexion instancia){

	free(instancia.ip);
	free(instancia.puerto);
}
