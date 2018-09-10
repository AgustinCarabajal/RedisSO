// #include "coordinador.h"
#include "algoritmos.h"

int algoritmo_distribucion(){

	int algoritmoElegido = elegirAlgoritmo();

	switch(algoritmoElegido){
		case 1:
			return equitative_load();
		case 2:
			// return least_space_used();
		case 3:
			// return key_explicit();
		default:
			printf("error: no existe algoritmo");
			exit(1);
	}
}

int equitative_load(){



}


int elegirAlgoritmo(){

	char* algoritmo = "EL";

	if(!strcmp(algoritmo,"EL"))
		return 1;
	else if(!strcmp(algoritmo,"LSU"))
		return 2;
	else
		return 3;
	
}