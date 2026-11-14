#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Step 3: a circular queue (FIFO: first in, first out) on an array.
 *
 * `front` is the index of the oldest value. When an index passes the end
 * of the array it wraps round to 0, so the space freed by dequeue is used
 * again. With `count` stored, full and empty are easy to tell apart.
 *
 *   capacity 5, front 3, count 3:   [ c | . | . | a | b ]
 *                                     2           0   1   <- order out
 */

typedef struct {
    int *items;      /* array of `capacity` ints, from malloc */
    size_t capacity;
    size_t front;    /* index of the oldest value             */
    size_t count;    /* how many values are in the queue now  */
} CircularQueue;

/* Set up an empty queue that can hold `capacity` values, with front = 0
 * and count = 0. Return false if capacity is 0 or malloc fails. */
bool cq_init(CircularQueue *queue, size_t capacity);

/* Add `value` at the back. Return false if the queue is full. */
bool cq_enqueue(CircularQueue *queue, int value);

/* Remove the oldest value into *out. Return false if empty. */
bool cq_dequeue(CircularQueue *queue, int *out);

/* Copy the oldest value into *out without removing it.
 * Return false if empty. */
bool cq_peek(const CircularQueue *queue, int *out);

bool cq_is_empty(const CircularQueue *queue);
bool cq_is_full(const CircularQueue *queue);

/* Free the array and reset the fields to 0 / NULL. */
void cq_free(CircularQueue *queue);

#endif
