#include "conexiones.h"

int crearSocketListener(datos_conexion serverData, t_log* serverLogger) {

  struct addrinfo hints;
  struct addrinfo* serverInfo;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;        // No importa si uso IPv4 o IPv6
  hints.ai_socktype = SOCK_STREAM;


  if(getaddrinfo(serverData.ip, serverData.puerto, &hints, &serverInfo) < 0) {
    log_error(serverLogger, "Error al cargar la informacion del servidor");
    exit(EXIT_FAILURE);
  }

  int socketListener = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

  if(socketListener < 0){
    log_error(serverLogger, "No se pudo crear el socket servidor");
    exit(EXIT_FAILURE);
  }

  	else
  {
		int activador = 1;
 		//Esta funcion hace funcionar el bind por si alguien pone CTRL + C.
		//El socket queda colgando y el bind no funciona al querer levantar la conexion
		//(Funcion descubierta en el canal de youtube de SO)

		setsockopt(socketListener, SOL_SOCKET, SO_REUSEADDR, &activador, sizeof(activador));

		if(bind(socketListener, serverInfo->ai_addr, serverInfo->ai_addrlen) < 0)
    {
			log_error(serverLogger, "Error al asignar la IP al cliente");
			exit(EXIT_FAILURE);
		}
	}

  freeaddrinfo(serverInfo);
  return socketListener;
}

int conectarseAServer(datos_conexion clientData, t_log* clientLogger){

  struct addrinfo hints;
  struct addrinfo *serverInfo;

  memset(&hints,0,sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if(getaddrinfo(clientData.ip, clientData.puerto, &hints, &serverInfo) <0){
    log_error(clientLogger, "Error al cargar los datos del cliente");
    exit(EXIT_FAILURE);
  }

  int socketServer=socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

  if(socketServer < 0){
    log_error(clientLogger, "Error al crear el socket cliente");
    exit(EXIT_FAILURE);
  }

  int conexion = connect(socketServer, serverInfo->ai_addr, serverInfo->ai_addrlen);

  if(conexion < 0){
    log_error(clientLogger,"Error en la conexion");
    exit(EXIT_FAILURE);
  }
  freeaddrinfo(serverInfo);

  return socketServer;
}
