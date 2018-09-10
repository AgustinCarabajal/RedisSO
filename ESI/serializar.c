#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

char* serializar(char *codigoOperacion, char *clave){

	int longitudCodigo = strlen(codigoOperacion);
	int messageLength = strlen(clave);

	char *buffer = malloc(longitudCodigo + 4 + messageLength);

	memcpy(buffer, codigoOperacion, longitudCodigo);
	memcpy(buffer + longitudCodigo, &messageLength, 4);
	memcpy(buffer + longitudCodigo + 4, clave, messageLength);

	return buffer;
}

char* serializar_set(char *codigoOperacion, char *clave, char *valor){

	int longitudCodigo = strlen(codigoOperacion);
	int messageLength = strlen(clave);
	int valueLength = strlen(valor);

	char *buffer = malloc (longitudCodigo + 4 + 4 + messageLength);

	memcpy(buffer, codigoOperacion, longitudCodigo);
	memcpy(buffer + longitudCodigo, &messageLength, 4);
	memcpy(buffer + longitudCodigo + 4, clave, messageLength);
	memcpy(buffer + longitudCodigo + 4 + messageLength, &valueLength, 4);
	memcpy(buffer + longitudCodigo + 4 + messageLength + 4, valor, valueLength);

	return buffer;
}

void eliminarPaquete(char** buffer){
	free(*buffer);
}