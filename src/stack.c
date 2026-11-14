#include "stack.h"

#include <stdlib.h>

#include "todo.h"

/* ---- 2a. Stack on an array ------------------------------------------ */

bool as_init(ArrayStack *stack, size_t capacity) {
    TODO("Step 2a", "as_init");
}

bool as_push(ArrayStack *stack, int value) {
    TODO("Step 2a", "as_push");
}

bool as_pop(ArrayStack *stack, int *out) {
    TODO("Step 2a", "as_pop");
}

bool as_peek(const ArrayStack *stack, int *out) {
    TODO("Step 2a", "as_peek");
}

bool as_is_empty(const ArrayStack *stack) {
    TODO("Step 2a", "as_is_empty");
}

bool as_is_full(const ArrayStack *stack) {
    TODO("Step 2a", "as_is_full");
}

void as_free(ArrayStack *stack) {
    TODO("Step 2a", "as_free");
}

/* ---- 2b. Stack on a linked list -------------------------------------- */

void ls_init(LinkedStack *stack) {
    TODO("Step 2b", "ls_init");
}

bool ls_push(LinkedStack *stack, int value) {
    TODO("Step 2b", "ls_push");
}

bool ls_pop(LinkedStack *stack, int *out) {
    TODO("Step 2b", "ls_pop");
}

bool ls_peek(const LinkedStack *stack, int *out) {
    TODO("Step 2b", "ls_peek");
}

bool ls_is_empty(const LinkedStack *stack) {
    TODO("Step 2b", "ls_is_empty");
}

void ls_free(LinkedStack *stack) {
    TODO("Step 2b", "ls_free");
}
