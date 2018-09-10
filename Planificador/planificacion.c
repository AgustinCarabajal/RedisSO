#include "planificacion.h"


void planificacion() {

    while (1) {
        sleep(10);
        // log_info(logger_procesos, "Planificando procesos..");
        pthread_mutex_lock(&semaforo);
        // printf("INCOMING: %d", incoming -> id);
        if (incoming) {
            printf("\n[PLANIFICACION] Hay procesos para ejecutar..\n");
            planificar_esi();
        } else {
            printf("\n[PLANIFICACION] ESIs para planificar: 0\n");
        }
        pthread_mutex_unlock(&semaforo);
    }
}

void planificar_esi() {
    printf("\n[PLANIFICACION] Replanificando..\n");
    pthread_mutex_lock(&semaforo_ready);

    pcb *aux = incoming;
    while(aux) {
      ready = pcb_push(ready, aux -> id, 5);
      aux = aux -> next;
    }
    pthread_mutex_unlock(&semaforo_ready);
    // FREE INCOMING
    free_incoming();

}

void free_incoming() {
  while(incoming && incoming -> next) {
    free(incoming);
    incoming = incoming -> next;
  }
  if (incoming) {
    free(incoming);
    incoming = NULL;
  }
  
}

int replanificar_esi() {

    pthread_mutex_lock(&semaforo_ready);
    if(ready) {
      running = pcb_push(running, ready -> id, ready -> estimation);
      ready = ready -> next;
      pthread_mutex_unlock(&semaforo_ready);
      return 1;
    }
    pthread_mutex_unlock(&semaforo_ready);
    return 0;
    

}

void ejecucion() {

  char* buffer;
  int confirm = 1;
  int end;

  while(1) {
    if(replanificar_esi()) {
  
      printf("\nPUEDO EJECUTAR UN ESI..\n");
    
      while(running -> estimation > 0) {

        printf("\nENVIO EL OKIS..\n");
        pthread_mutex_lock(&semaforo_exe);
        printf("\n[EJECUTANDO SIN PAUSA]\n");
        
        send(running -> id, &confirm, sizeof(int), 0);
        
        running -> estimation -= 1;
        
        printf("\nESPERANDO RESPUESTAS.. %d\n", socketCoord);
        // ESPERO RESPUESTA DEL COORD. -> no se porqe garcha no se bloqea el thread con el receive
        if (recv(socketCoord, buffer, 3, 0) > -1) {
          printf("\nAca.\n");
          buffer[3] = '\0';
          if (!strcmp(buffer, "110")) {
            char *clave = get_key(socketCoord);

            if(dictionary_has_key(tabla_entradas, clave)){
              // Agrego la clave con el esi al final, como bloqueado
              locked = pcb_push(locked, running -> id, running -> estimation);
              dictionary_put(tabla_entradas, clave, (void *) running -> id);
        
              break;
            }

            dictionary_put(tabla_entradas, clave, (void *) running -> id);
          }
        } 

        if (recv(running -> id, &end, 4, 0) > -1) {
          if (end == 15) {
            running -> estimation = 0;
          }
        }
        
        pthread_mutex_unlock(&semaforo_exe);
        sleep(5);
      }
      
      pthread_mutex_lock(&semaforo_exe);
      if(running)
        free(running);
      running = NULL;
      pthread_mutex_unlock(&semaforo_exe);
      
    }
  }

}

char *get_key(int sock) {

	char *key;
	int keyLength;

	recv(sock, &keyLength, 4, 0);
	key = malloc(keyLength);
	recv(sock, key, keyLength, 0);
	
	key[keyLength] = '\0';

	return key;
}