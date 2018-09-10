#ifndef CONNECTION_LIB
#define CONNECTION_LIB

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <commons/log.h>
#include <commons/config.h>
#include "planificacion.h"

#define MAXMSG  512
#define BACKLOG 5

char* puerto_coord;
char* ip_coord;

t_log* logger_connection;

struct addrinfo hints;
struct addrinfo *serverInfo;
struct sockaddr_in clientname;
socklen_t addrlen;


int create_listenner(char* port);
int read_from_client (int filedes);
int conectar_servidor(char *ip, char *port);
void init_connections(int sock);



#endif