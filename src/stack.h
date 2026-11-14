#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Step 2: the same stack, built two ways.
 * Both are LIFO: the last value pushed is the first one popped.
 */

/* ---- 2a. Stack on an array ------------------------------------------ */

typedef struct {
    int *items;      /* array of `capacity` ints, from malloc   */
    size_t count;    /* how many values are on the stack now    */
    size_t capacity; /* the most values it can hold             */
} ArrayStack;

/* Set up an empty stack that can hold `capacity` values.
 * Return false if capacity is 0 or malloc fails. */
bool as_init(ArrayStack *stack, size_t capacity);

/* Push `value`. Return false if the stack is full (overflow). */
bool as_push(ArrayStack *stack, int value);

/* Pop the top value into *out. Return false if empty (underflow). */
bool as_pop(ArrayStack *stack, int *out);

/* Copy the top value into *out without removing it.
 * Return false if empty. */
bool as_peek(const ArrayStack *stack, int *out);

bool as_is_empty(const ArrayStack *stack);
bool as_is_full(const ArrayStack *stack);

/* Free the array and reset the fields to 0 / NULL. */
void as_free(ArrayStack *stack);

/* ---- 2b. Stack on a linked list -------------------------------------- */

typedef struct StackNode {
    int value;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;  /* NULL when empty */
    size_t size;
} LinkedStack;

/* Set up an empty stack. */
void ls_init(LinkedStack *stack);

/* Push `value`. It never gets full; return false only if malloc fails. */
bool ls_push(LinkedStack *stack, int value);

/* Pop the top value into *out. Return false if empty. */
bool ls_pop(LinkedStack *stack, int *out);

/* Copy the top value into *out without removing it.
 * Return false if empty. */
bool ls_peek(const LinkedStack *stack, int *out);

bool ls_is_empty(const LinkedStack *stack);

/* Free every node and leave an empty stack (top = NULL, size = 0). */
void ls_free(LinkedStack *stack);

#endif
