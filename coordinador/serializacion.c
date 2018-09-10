#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <commons/log.h>
#include "cliente.h"



char* serializarEntradas(char* entradas, char* size){

	int aux_entradas=strlen(entradas);
	int aux_size=strlen(size);
	char* buffer= malloc(sizeof(entradas)+sizeof(size));
	char* aux_buffer = malloc(header_size);

	
	//Si quieren verificar algo dejo los printf, si no les gusta son libres de sacarlos.
	sprintf(buffer, "%d",aux_entradas);
	//printf("cuando hacer el header entradas_ %s \n", buffer);

	buffer=strcat(buffer,entradas);
	//printf("cuaando concatena2: %s \n", buffer);		

	//Aqui utilizo el aux_buffer porque sprintf borra lo concatenado anteriormente.
	sprintf(aux_buffer,"%d",aux_size);
//	printf("cuando hace el header size: %s \n", aux_buffer);

	buffer=strcat(buffer,aux_buffer);
//	printf("cuaando concatena2: %s \n", buffer);	

	buffer=strcat(buffer,size);	
//	printf("El mensaje total: %s \n", buffer);

	
	free(aux_buffer);


	return buffer;
}
