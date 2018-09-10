#include "consola_planificador.h"


void consola() {

  char *buffer;

  sleep(1);
  printf("\nIniciando Consola..\n");
  sleep(2);
  printf("\nIngrese un comando (:h para ayuda)\n\n");

  while(1) {
    printf("$ ");
    buffer = malloc(40);
    fgets(buffer, 40, stdin);

    if (!strcmp(buffer, "\n")) {} else

    if (!strcmp(buffer, ":help\n") || !strcmp(buffer, ":h\n")) {
      show_help();
    } else

    if (!strcmp(buffer, "pausar\n")) {
      pausar();
    } else

    if (!strcmp(buffer, "listar\n")) {
      listar_esi();
    } else

    if (!strcmp(buffer, "continuar\n")) {
      continuar();
    } else

    // if (!strcmp(buffer, ":help\n")) {
    //   show_help();
    // } else

    // if (!strcmp(buffer, ":help\n")) {
    //   show_help();
    // } else

      printf("$ command not found: %s", buffer);

    free(buffer);
  }
 }

void show_help() {
  fprintf (stdout, "\n----------------------- Ayuda -----------------------\n\n");
  
  fprintf (stdout, "Comandos de utilidad:\n\n");
  fprintf (stdout, "pausar: \t\tPausar ejecucion\n");
  fprintf (stdout, "continuar: \t\tContinuar ejecucion\n");
  fprintf (stdout, "bloquear [Clave] [ID]: \tBloquear clave\n");
  fprintf (stdout, "desbloquear [Clave]: \tDesbloquear clave\n");
  fprintf (stdout, "listar [Recurso]: \tListar procesos\n");
  fprintf (stdout, "kill [ID]: \t\tFinalizar proceso\n");
  fprintf (stdout, "status [Clave]: \tMostrar estado\n");
  fprintf (stdout, "deadlock: \t\tAnalizar deadlock existente\n\n");

  fprintf (stdout, "Informacion adicional\n\n");
  fprintf (stdout, "Version: 1.0.0\n");
  fprintf (stdout, "[Copyright] Derechos reservados Los Chantas 2018\n\n");

  fprintf (stdout, "-----------------------------------------------------\n\n");
}

void pausar() {
  printf("\nSe pauso la ejecucion..\n");
  pthread_mutex_lock(&semaforo_exe);
}

void continuar() {
  printf("\nContinua la ejecucion..\n");
  pthread_mutex_unlock(&semaforo_exe);
}

void listar_esi() {
  printf("\n\n------------ INFORMACION DE PROCESOS ------------\n\n");
  // INCOMING
  pcb *aux_incoming = incoming;
  printf("Listado de procesos nuevos:\n\n");
  while(aux_incoming) {
    
    printf("ESI:\t\t\t%d\n", aux_incoming -> id);
    aux_incoming = aux_incoming -> next;

  }

  // READY
  pcb *aux_ready = ready;
  printf("Listado de procesos listos:\n\n");
  while(aux_ready) {
    
    printf("ESI:\t\t\t%d\n", aux_ready -> id);
    aux_ready = aux_ready -> next;

  }

  // RUNNING
  pcb *aux_running = running;
  printf("Listado de procesos ejecutando:\n\n");
  while(aux_running) {
    
    printf("ESI:\t\t\t%d\n", aux_running -> id);
    aux_running = aux_running -> next;

  }
}
