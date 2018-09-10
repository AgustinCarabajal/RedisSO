#include "servidor.h"
#include "coordinador.h"
#include "cliente.h"
#include <string.h>
#include <commons/config.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


void iniciarConexionConClientes(){

	struct addrinfo hints;
	struct addrinfo *serverInfo;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(NULL,puerto,&hints,&serverInfo);

	int listeningSocket;
	listeningSocket = socket(serverInfo->ai_family,serverInfo->ai_socktype,serverInfo->ai_protocol);

	if(listeningSocket <0){
		logueandoConexion(0,"No se pudo crear el socket");

	}
	else{
		
	int activador =1;
 	
 	//Esta funcion hace funcionar el bind por si algun chanta pone CTRL + C.
	setsockopt(listeningSocket,SOL_SOCKET,SO_REUSEADDR,&activador,sizeof(activador)); 

	if(bind(listeningSocket,serverInfo->ai_addr,serverInfo->ai_addrlen)!=0){
		logueandoConexion(0,"Fallo en la funcion bind");
		exit(1);
	}

	freeaddrinfo(serverInfo);
	logueandoConexion(1,"Esperando Conexiones..\n");
	
	
	listen(listeningSocket,MAX_CONEXIONES);
	int cliente;
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	
	while (cliente = accept(listeningSocket, (struct sockaddr *) &addr, &addrlen)) {

		datos = malloc(sizeof(proceso));
		datos -> cliente = cliente;
		datos -> servidor = listeningSocket;
		pthread_create(&conexion, NULL, (void *)operaciones, (void*)datos);
		
	}

	pthread_join(conexion, NULL);

	if (cliente < 0) {
      	logueandoConexion(0,"Fallo en la funcion accept, el cliente no se pudo conectar");
		exit(1);
    }

	close(listeningSocket);
	}
}


