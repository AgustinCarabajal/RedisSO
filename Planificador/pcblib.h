#ifndef PCB_LIBRARY
#define PCB_LIBRARY

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/queue.h>
#include <commons/collections/list.h>
#include <commons/collections/node.h>
#include <pthread.h>

t_list *esi_node;
t_link_element *node;

pthread_mutex_t semaforo;
pthread_mutex_t semaforo_ready;
pthread_mutex_t semaforo_exe;

typedef struct t_pcb {
    int id;
    int estimation;

    struct t_pcb *next;
}pcb;

// Lista de claves bloqueadas
struct t_lock {
    int id;
    char *clave;
    
    struct t_lock *next;
};

void init_semaforos(pthread_mutex_t sem);

t_log* logger_procesos;

struct t_pcb *get_last_pcb(struct t_pcb *queue);

// listas
struct t_pcb *pcb_push(struct t_pcb *queue, int id, int estimation);
struct t_pcb *pcb_push_esi(struct t_pcb *queue);
struct t_pcb *pcb_pop_esi(struct t_pcb *queue);

// planificacion

// SJF ESTIMATIONS
// struct t_pcb *sort_pcb(struct t_pcb *queue);

#endif
