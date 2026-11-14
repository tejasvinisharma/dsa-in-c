#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

#include "todo.h"

LinkedList *ll_create(void) {
    TODO("Step 1", "ll_create");
}

bool ll_push_front(LinkedList *list, int value) {
    TODO("Step 1", "ll_push_front");
}

bool ll_push_back(LinkedList *list, int value) {
    TODO("Step 1", "ll_push_back");
}

bool ll_pop_front(LinkedList *list, int *out) {
    TODO("Step 1", "ll_pop_front");
}

bool ll_insert_at(LinkedList *list, size_t index, int value) {
    TODO("Step 1", "ll_insert_at");
}

long ll_find(const LinkedList *list, int value) {
    TODO("Step 1", "ll_find");
}

bool ll_remove(LinkedList *list, int value) {
    TODO("Step 1", "ll_remove");
}

void ll_reverse(LinkedList *list) {
    TODO("Step 1", "ll_reverse");
}

void ll_free(LinkedList *list) {
    TODO("Step 1", "ll_free");
}

/* Already written for you. */
void ll_print(const LinkedList *list) {
    printf("[");
    for (const Node *node = list->head; node != NULL; node = node->next) {
        printf("%d%s", node->value, node->next != NULL ? " -> " : "");
    }
    printf("]\n");
}
