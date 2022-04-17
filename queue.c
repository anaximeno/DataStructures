#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define len(arr, type) (sizeof(arr) / sizeof(type))


typedef void* queue_Item;


typedef struct queue_Rep {
    queue_Item item;
    struct queue_Rep* next;
} queue_Rep;


typedef queue_Rep* queue_T;


/* Queue Holder: 
 *   Holds the head and tail of the queue
 */
typedef struct qholder_Rep {
    queue_T head;
    // The tail will point to the 
    // last element on the queue
    // so that the insertion will be
    // faster.
    queue_T tail;
} qholder_Rep;


typedef qholder_Rep* qholder_T;


qholder_T qholder_create(void) {
    qholder_T qholder = (qholder_T) malloc(sizeof(qholder_Rep));

    if (qholder != NULL) {
        qholder->head = NULL;
        qholder->tail = NULL;
    }

    return qholder;
}


bool qholder_empty(qholder_T qholder) {
    return (qholder == NULL) || ((qholder->head == NULL) && (qholder->tail == NULL));
}


queue_T queue_create(void) {
    return (queue_T) malloc(sizeof(queue_Rep));
}


bool queue_empty(queue_T ts) {
    return (ts == NULL) || (ts->item == NULL);
}


void enqueue(qholder_T* qholder, queue_Item item) {
    if (*qholder == NULL) {
        (*qholder) = qholder_create();
        enqueue(qholder, item);
    } else if ((*qholder)->head == NULL) {
        (*qholder)->head = queue_create();
        (*qholder)->tail = (*qholder)->head;
        (*qholder)->head->item = item;
        (*qholder)->head->next = NULL;
    } else {
        queue_T new = queue_create();
        new->item = item;
        new->next = NULL;
        (*qholder)->tail->next = new;
        (*qholder)->tail = (*qholder)->tail->next;
    }
}


queue_Item dequeue(qholder_T* qholder) {
    queue_Item item = NULL;

    if (!qholder_empty(*qholder)) {
        queue_T top = (*qholder)->head;
        item = top->item;
        (*qholder)->head = top->next;
        free(top);
    }

    return item;
}


queue_Item peek(qholder_T qholder) {
    queue_Item item = NULL;

    if (!qholder_empty(qholder)) {
        item = qholder->head->item;
    }

    return item;
}


void queue_free(queue_T s) {
    if (s != NULL) {
        // Recursivelly eliminates the nexts
        // nodes on the queue.
        queue_free(s->next);
    }
    // Deallocates the memory used on the
    // node.
    free(s);
}


int main(int argc, char** argv) {
    puts("\nData Structure: Queue\n");

    qholder_T qholder = NULL;
    
    long array[] = {2, 3, 1, 4, 9, 1, 7, 2}; 
    int size = len(array, long);

    for (int i = 0 ; i < size ; ++i) {
        enqueue(&qholder, (queue_Item) array[i]);
        printf(" enqueue: %ld\n", array[i]);
    }

    puts("\n ------- \n");

    queue_Item item = NULL;
    while((item = dequeue(&qholder)) != NULL){
        printf(" dequeue: %ld\n", (long) item);
    }

    putchar('\n');

    queue_free(qholder->head);
    return 0;
}
