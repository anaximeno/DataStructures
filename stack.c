#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define len(arr, type) (sizeof(arr) / sizeof(type))

typedef void* stack_Item;

typedef struct stack_Rep {
    stack_Item item;
    struct stack_Rep* next;
} stack_Rep;

typedef stack_Rep* stack_T;

stack_T stack_create(void) {
    return (stack_T) malloc(sizeof(stack_Rep));
}

bool stack_empty(stack_T ts) {
    return (ts == NULL) || (ts->item == NULL);
}

void stack_push(stack_T* s, stack_Item e) {
    stack_T new = stack_create();
    // This should work even when 
    // the parameter 's' is NULL.
    if (new != NULL) {
        new->item = e;
        new->next = *s;
        (*s) = new;
    }
}

stack_Item stack_pop(stack_T* s) {
    stack_Item item = NULL;
    stack_T top = NULL;

    if (!stack_empty(*s)) {
        item = (*s)->item;
        top = (*s);
        (*s) = (*s)->next;
        free(top);
    }

    return item;
}

void stack_free(stack_T s) {
    if (s != NULL) {
        // Recursivelly eliminates the nexts
        // nodes on the stack.
        stack_free(s->next);
    }
    // Deallocates the memory used on the
    // node.
    free(s);
}


int main(int argc, char** argv) {
    puts("\nData Structure: Stack\n");
    
    stack_T stack = NULL;

    long array[] = {2, 3, 1, 4, 9, 1, 7, 2}; 
    int size = len(array, long);

    for (int i = 0 ; i < size ; ++i) {
        stack_push(&stack, (stack_Item) array[i]);
        printf(" push: %ld\n", array[i]);
    }

    puts("\n ------- \n");

    stack_Item item = NULL;
    while((item = stack_pop(&stack)) != NULL){
        printf(" pop: %ld\n", (long) item);
    }

    putchar('\n');

    stack_free(stack);
    return 0;
}
