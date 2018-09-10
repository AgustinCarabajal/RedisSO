#include "claves.h"

void init_tabla(int sock, t_dictionary* tabla_entradas) {

	int header;
	char aux[2];
	char *buffer;

	// Inicializo la tabla de entradas
	tabla_entradas = dictionary_create();
	// Asigno un tamanio maximo a la tabla
	tabla_entradas -> table_max_size = 10000;

	printf("Esperando datos de configuracion..");

	// Recibo la cantidad de entradas
	if(recv(sock, aux, 1, 0) < 0) {
		perror("Error al recibir la configuracion [Header 1]");
	} else {
		// Realizo el casteo del entero que recibo como header
		header = aux[0] - 48;
		// printf("\nMensaje Recibido: %d\n", header);

		// Recibo el buffer con el tamaño del header
		buffer = malloc(header + 1);
		if(recv(sock, buffer, header, 0) < 0) {
			perror("Error al recibir la configuracion [buffer 1]");
		} else {
            buffer[header] = '\0';
			// Agrego la cantidad de entradas
			tabla_entradas -> elements_amount = atoi(buffer);
			printf("\nCantidad de entradas asignadas: %d\n", tabla_entradas -> elements_amount);
			free(buffer);
		}
	}

	// Recibo el tamanio de las entradas
	if(recv(sock, aux, 1, 0) < 0) {
		perror("Error al recibir la configuracion [Header 2]");
	} else {
		// Realizo el casteo del entero que recibo como header
		header = aux[0] - 48;
		// printf("\nMensaje Recibido: %d\n", header);

		// Recibo el buffer con el tamaño del header
		buffer = malloc(header + 1);
		if(recv(sock, buffer, header, 0) < 0) {
			perror("Error al recibir la configuracion [buffer 2]");
		} else {
            buffer[header] = '\0';
			// calculo el tamanio de la tabla con la cantidad de entradas * el tamanio de cada una
			tabla_entradas -> table_current_size = tabla_entradas -> elements_amount * atoi(buffer);
			printf("\nTamanio de cada entrada: %s\n", buffer);
			printf("\nTamanio de la tabla: %d\n\n", tabla_entradas -> table_current_size);
			free(buffer);
		}
	}
}