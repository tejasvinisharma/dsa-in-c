#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Step 1: a singly linked list of ints.
 *
 *   head -> [ 7 | next ] -> [ 3 | next ] -> [ 9 | NULL ]
 *
 * `size` must always equal the number of nodes. Every function that adds
 * or removes a node has to keep it up to date.
 */

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
} LinkedList;

/* Make a new, empty list (head = NULL, size = 0).
 * Return NULL if malloc fails. */
LinkedList *ll_create(void);

/* Add `value` at the front. Return false if malloc fails. */
bool ll_push_front(LinkedList *list, int value);

/* Add `value` at the back. Return false if malloc fails. */
bool ll_push_back(LinkedList *list, int value);

/* Remove the first node and store its value in *out.
 * Return false (and leave *out alone) if the list is empty. */
bool ll_pop_front(LinkedList *list, int *out);

/* Insert `value` so that it ends up at position `index`
 * (0 = front, list->size = back).
 * Return false if index > list->size, or if malloc fails. */
bool ll_insert_at(LinkedList *list, size_t index, int value);

/* Return the position of the first node holding `value`, or -1. */
long ll_find(const LinkedList *list, int value);

/* Remove the first node holding `value`.
 * Return false if no node holds it. */
bool ll_remove(LinkedList *list, int value);

/* Reverse the list in place: re-link the nodes you already have.
 * Don't allocate new nodes and don't copy values. */
void ll_reverse(LinkedList *list);

/* Free every node, then the list itself. Passing NULL does nothing. */
void ll_free(LinkedList *list);

/* Already written for you: prints the list, e.g. [7 -> 3 -> 9] */
void ll_print(const LinkedList *list);

#endif
