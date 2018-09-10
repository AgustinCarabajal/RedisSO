#include "pcblib.h"

void init_semaforos(pthread_mutex_t sem) {
    if (pthread_mutex_init(&sem, NULL) != 0)
    {
        printf("\nError: Mutex Failed\n");
        exit(1);
    }
}

struct t_pcb *get_last_pcb(struct t_pcb *queue) {

    while(queue && queue -> next) {
        queue = queue -> next;
    }

    return queue;
}

struct t_pcb *pcb_push(struct t_pcb *queue, int id, int estimation) {

    // printf("\n\nestimacion %d - id: %d\n\n", estimation, id);

    struct t_pcb *aux;

    if (queue != NULL) {
        aux = get_last_pcb(queue);
        aux -> next = malloc(sizeof(struct t_pcb));
        aux = aux -> next;
        aux -> id = id;
        aux -> estimation = estimation;
        aux -> next = NULL;

    } else {
        queue = malloc(sizeof(struct t_pcb));
        queue -> id = id;
        queue -> estimation = estimation;
        queue -> next = NULL;
    }

    return queue;
}

struct t_pcb *pcb_push_esi(struct t_pcb *queue) {

    struct t_pcb *aux = queue;
    queue = pcb_pop_esi(queue);

    return aux;
}

struct t_pcb *pcb_pop_esi(struct t_pcb *queue) {
    struct t_pcb *aux = queue;
    
    queue = queue -> next;

    // if (aux -> resources != NULL) {
        // free(aux -> resources);
    // }
    free(aux);

    return queue;
}

// struct t_pcb *sort_pcb(struct t_pcb *queue) {

//     int amount = get_elements(queue);
//     struct t_pcb *aux;

//     for (int i = 1; i < amount; i++) {
//         for (int j = 0; j > amount - 1; j++) {
//             if (queue -> estimation < (queue -> next) -> estimation)
//                 aux = queue;
//                 aux -> next = (queue -> next) -> next;
//                 queue = queue -> next;
//                 queue -> next = aux;
//         }
//     }
// }




