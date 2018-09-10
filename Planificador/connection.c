#include "connection.h"

int create_listenner(char* port) {

  memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		// No importa si uso IPv4 o IPv6
  hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

  if(getaddrinfo(NULL, port, &hints, &serverInfo) < 0) {
    // log_error();
    exit(EXIT_FAILURE);
  }

  int list_sock = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

  bind(list_sock, serverInfo->ai_addr, serverInfo->ai_addrlen);
  freeaddrinfo(serverInfo);

  return list_sock;
}

int read_from_client (int filedes)
{
  char *buffer;
  int nbytes;

  buffer = malloc(40);
  nbytes = read (filedes, buffer, 40);
  if (nbytes < 0)
    {
      /* Read error. */
      log_info (logger_connection, "%d se desconecto..", filedes);
      // printf("%d se desconecto..", filedes);
      // exit (EXIT_FAILURE);
    }
  else if (nbytes == 0)
    /* End-of-file. */
    return -1;
  else
    {
      /* Data read. */
      printf("Message from %d: %s", filedes, buffer);
      free(buffer);
      return 0;
    }
}

int conectar_servidor(char *ip, char *port){

	struct addrinfo hints;
	struct addrinfo *serverInfo;

	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(ip, port, &hints, &serverInfo);

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


void init_connections(int sock) {
  int i;

  if (listen (sock, BACKLOG) < 0)
  {
    log_error(logger, "Error en el Listen..");
    exit (EXIT_FAILURE);
  }

  log_info(logger, "Esperando conexiones..");
  /* Initialize the set of active sockets. */
  FD_ZERO (&active_fd_set);
  FD_SET (sock, &active_fd_set);

  while (1) {
    /* Block until input arrives on one or more active sockets. */
    read_fd_set = active_fd_set;
    if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
      {
        log_error(logger, "Error en Select");
        exit (EXIT_FAILURE);
      }

    /* Service all the sockets with input pending. */
    for (i = 0; i < FD_SETSIZE; ++i)
      if (FD_ISSET (i, &read_fd_set))
        {
          if (i == sock)
            {
              /* Connection request on original socket. */
              int new;
              addrlen = sizeof(clientname);
              
              new = accept (sock,(struct sockaddr *) &clientname, &addrlen);
              printf("\n");
              log_info(logger, "Conexion entrante..");
              if (new < 0)
                {
                  log_error (logger, "Error al aceptar un cliente");
                  exit (EXIT_FAILURE);
                }
              log_info (logger, "ESI conectado: %d", new);
              FD_SET (new, &active_fd_set);

              // TODO: agregar un nuevo ESI a la cola [VER: struct de datos de ESI (Estimacion)]
              pthread_mutex_lock(&semaforo);
              // ARREGLAR ESTIMACION
              incoming = pcb_push(incoming, new, 3);

              pthread_mutex_unlock(&semaforo);
              // MOSTRAR LISTA DE ESIS PLANIFICADOS PARA EJECUTAR
              // show_list(incoming);
            }
          else
            {
              /* Data arriving on an already-connected socket. */
              if (read_from_client (i) < 0)
                {
                  close (i);
                  FD_CLR (i, &active_fd_set);
                }

            }
        }
  }
  
  FD_ZERO (&active_fd_set);
  FD_ZERO (&read_fd_set);
    
}
