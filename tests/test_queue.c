#include "queue.h"
#include "test_util.h"

static void test_refuses_zero_capacity(void) {
    CircularQueue queue;
    CHECK(!cq_init(&queue, 0));
}

static void test_first_in_first_out(void) {
    CircularQueue queue;
    CHECK(cq_init(&queue, 3));
    CHECK(cq_is_empty(&queue));
    CHECK(!cq_is_full(&queue));

    CHECK(cq_enqueue(&queue, 1));
    CHECK(cq_enqueue(&queue, 2));
    CHECK(cq_enqueue(&queue, 3));
    CHECK(cq_is_full(&queue));
    CHECK(!cq_enqueue(&queue, 4));      /* full */

    int out = 0;
    CHECK(cq_peek(&queue, &out) && out == 1);
    CHECK(queue.count == 3);            /* peek doesn't remove */

    CHECK(cq_dequeue(&queue, &out) && out == 1);
    CHECK(cq_dequeue(&queue, &out) && out == 2);
    CHECK(cq_dequeue(&queue, &out) && out == 3);
    CHECK(cq_is_empty(&queue));

    out = 99;
    CHECK(!cq_dequeue(&queue, &out));   /* empty */
    CHECK(!cq_peek(&queue, &out));
    CHECK(out == 99);                   /* *out left alone */
    cq_free(&queue);
}

static void test_wraps_round_the_array(void) {
    CircularQueue queue;
    cq_init(&queue, 3);
    int out = 0;
    cq_enqueue(&queue, 1);
    cq_enqueue(&queue, 2);
    cq_enqueue(&queue, 3);
    cq_dequeue(&queue, &out);           /* frees slot 0 */

    CHECK(cq_enqueue(&queue, 4));       /* must reuse slot 0 */
    CHECK(cq_is_full(&queue));
    CHECK(queue.items[0] == 4);

    CHECK(cq_dequeue(&queue, &out) && out == 2);
    CHECK(cq_dequeue(&queue, &out) && out == 3);
    CHECK(cq_dequeue(&queue, &out) && out == 4);
    CHECK(cq_is_empty(&queue));
    cq_free(&queue);
}

static void test_many_rounds_stay_in_order(void) {
    CircularQueue queue;
    cq_init(&queue, 4);
    int next_in = 0, next_out = 0, out = 0;
    bool in_order = true, front_in_range = true;
    for (int round = 0; round < 100; round++) {
        in_order = in_order && cq_enqueue(&queue, next_in++);
        in_order = in_order && cq_enqueue(&queue, next_in++);
        in_order = in_order && cq_enqueue(&queue, next_in++);
        in_order = in_order && cq_dequeue(&queue, &out) && out == next_out++;
        in_order = in_order && cq_dequeue(&queue, &out) && out == next_out++;
        in_order = in_order && cq_dequeue(&queue, &out) && out == next_out++;
        front_in_range = front_in_range && queue.front < queue.capacity;
    }
    CHECK(in_order);
    CHECK(front_in_range);
    CHECK(cq_is_empty(&queue));
    cq_free(&queue);
}

static void test_free_resets_the_queue(void) {
    CircularQueue queue;
    cq_init(&queue, 2);
    cq_enqueue(&queue, 5);
    cq_free(&queue);
    CHECK(queue.items == NULL);
    CHECK(queue.count == 0 && queue.capacity == 0 && queue.front == 0);
}

int main(void) {
    RUN(test_refuses_zero_capacity);
    RUN(test_first_in_first_out);
    RUN(test_wraps_round_the_array);
    RUN(test_many_rounds_stay_in_order);
    RUN(test_free_resets_the_queue);
    FINISH("Step 3: circular queue");
}
