#include "analyser.h"

void get_key(char *key, int sock) {


	if(!dictionary_has_key(tabla_entradas,key)){	

		set_key(key," "); 	
	}
	
	send(sock,key, strlen(key)+1, 0);

	// bloquear_clave(key);
	
}

void store_key(char* key,int sock){

	char* var;	

	//desbloquear_clave(key);
	printf("hola");
	
	if(keys = txt_open_for_append(key)){
	
		var = strdup(dictionary_get(tabla_entradas,key)); //strdup: la misma funcion te hace el malloc 	
		txt_write_in_file(keys, var);
		txt_close_file(keys);
		send(sock,key, strlen(key)+1, 0);
	}else{
		
		log_error(logger,"Error al abrir/crear el archivo");
		exit(1);
	}


}

void set_key(char *key, char *val) {

	// Agrego la clave y el valor al diccionario si es que no existen
	// si hago esto en el caso de que ya exista la key, me la va a crear de nuevo en otro nodo
	if (!dictionary_has_key(tabla_entradas, key)) {

		dictionary_put(tabla_entradas, key, (void *) val);
		
		
	} else {

    // Aca busco la key existente y solamente le agrego el valor
		set_value(key, val);
	}
}

void set_value(char *key, char *val) {

  // Obtengo el Hash correspondiente a la key que quiero buscar
	unsigned int key_hash = get_hash(key, strlen(key));
  // Obtengo el indice de la key dentro de la tabla
	int index = key_hash % tabla_entradas->table_max_size;

  // Me paro sobre el elemento "Index"
	t_hash_element *element = tabla_entradas->elements[index];

	if (element == NULL) {
		// return NULL;
		perror("Error al asignar el valor..");
	}
	do {
    // Checkeo si el hash coincide con el de la key que quiero asignar
		if (element->hashcode == key_hash) {

			// Agrego el valor al elemento con la key designada
			element->data = val;
			
			
		}

	} while ((element = element->next) != NULL);

	// return NULL;
}

// Esta funcion me devuelve la que le pasas por parametro (Funcion de la catedra)
static unsigned int get_hash(char *key, int key_len) {
	unsigned int hash = 0;
	int index;

	for (index = 0; index < key_len; index++) {
		unsigned char c = key[index];
		hash += c;
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}

int get_operations(int sock, t_log* log) {

  char operator[3];
  int res;
  logger = log;
	
	printf("hola");
  while((res = recv(sock, operator, 3, 0)) > 0) {

    analizar(operator, sock);
  }

  return res;
}

void analizar(char *operator, int sock) {

  /*int header;
	char aux[2];
	char *buffer;
  char *clave;
*/
char* clave = malloc(6);
char* valor = malloc(6);

//operacion_esi_set* package_Set;
//operacion_esi* package_Get;
//operacion_esi* package_Store;

	int res = recv(sock, clave, 6, 0);
	int res2 = recv(sock,valor,6,0);

  if (strcmp(operator, "SET")) {
	
	seleccionarAlgortimo();
	//if(deserializar_Set(package_Set,sock)>0){
	printf("hola");
	set_key(clave,valor);

	/*}else{

	perror("Intruccion Incorrecta");
	exit(1);
	}
	*/
     }
	if (strcmp(operator, "GET")) {
		
		//if(deserializar(package_Get,sock)>0){

			get_key(clave,sock); //El sock hay que pasarlo para despues mandarle al coord

		
	}
	
	if(strcmp(operator,"STORE")){

		//if(deserializar(package_Store,sock)>0){
	
			store_key(clave,sock);
	
		
	}
	
  

}


void seleccionarAlgoritmo(){

	int algoritmoElegido = elegirAlgoritmo();
	

	switch(algoritmoElegido){
		case 1:
			return algoritmo_circular();
		case 2:
			// return least_space_used();
		case 3:
			// return key_explicit();
		default:
			printf("error: no existe algoritmo");
			exit(1);
	}
}

int algoritmo_circular(){

if(!first){
//first debe apuntar al primer espacio de memoria de la tabla
first = tabla_entradas->elements;

}

	//Apunto al espacio de memoria de tipo t_hash_elements
		algoritmo = tabla_entradas->elements;
	
	//guardo la key y el valor de la misma
		set_key(algoritmo->key, (char *)algoritmo->data); //Nose si hace falta el casteo TODO:Check
	
	//Me muevo al proximo espacio de memoria
		algoritmo->next = tabla_entradas->elements->next;
		
		if(algoritmo->next){
	
		algoritmo = algoritmo->next;
		tabla_entradas ->elements = tabla_entradas ->elements->next;
	
		}else{
			//Llegue al final de la tabla y vuelvo al principio
			algoritmo = first;
			tabla_entradas->elements = first;			
		}

}


int selectAlgoritmo(){

	char* algoritmo = "CIRC";

	if(!strcmp(algoritmo,"CIRC"))
		return 1;
	else if(!strcmp(algoritmo,"LRU"))
		return 2;
	else
		return 3;
	
}	
	


}
