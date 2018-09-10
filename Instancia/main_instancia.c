#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <commons/config.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "main_instancia.h"

int main(int argc, char* argv[]){

	iniciarInstancia(logger_connection);
	log_info(logger, "Iniciando Instancia..\n\n");
	show_info(instancia);

	int socketCoordinador = conectar_server(instancia);

	if (socketCoordinador < 0) {
		log_error(logger, "Error de conexion..\n");
		exit(1);
	} else {

		log_info(logger, "Conexion exitosa!\n\n");

		// Me identifico con el coordinador
		send(socketCoordinador, CODIGO, 3, 0);

		// TODO: Recibo la config desde el coordinador
		finalizarConfig(socketCoordinador);

		// Espero por sentencias
		// if(get_operations(socketCoordinador, logger) == 0)
		// 	log_info(logger, "Server Disconnected");
		// else
		// 	log_error(logger, "RECV failed");

		close(socketCoordinador);

		// Libero la memoria
		liberar_memoria();
	}
	return 0;
}
