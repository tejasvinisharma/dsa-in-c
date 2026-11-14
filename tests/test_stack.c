#include "stack.h"
#include "test_util.h"

/* ---- 2a. Array stack ------------------------------------------------- */

static void test_array_stack_refuses_zero_capacity(void) {
    ArrayStack stack;
    CHECK(!as_init(&stack, 0));
}

static void test_array_stack_is_last_in_first_out(void) {
    ArrayStack stack;
    CHECK(as_init(&stack, 3));
    CHECK(as_is_empty(&stack));
    CHECK(!as_is_full(&stack));

    CHECK(as_push(&stack, 10));
    CHECK(as_push(&stack, 20));
    CHECK(as_push(&stack, 30));
    CHECK(as_is_full(&stack));
    CHECK(!as_push(&stack, 40));        /* overflow */
    CHECK(stack.count == 3);

    int out = 0;
    CHECK(as_peek(&stack, &out));
    CHECK(out == 30);
    CHECK(stack.count == 3);            /* peek doesn't remove */

    CHECK(as_pop(&stack, &out) && out == 30);
    CHECK(as_pop(&stack, &out) && out == 20);
    CHECK(as_pop(&stack, &out) && out == 10);
    CHECK(as_is_empty(&stack));

    out = 99;
    CHECK(!as_pop(&stack, &out));       /* underflow */
    CHECK(!as_peek(&stack, &out));
    CHECK(out == 99);                   /* *out left alone */

    CHECK(as_push(&stack, 7));          /* usable again after emptying */
    CHECK(as_pop(&stack, &out) && out == 7);

    as_free(&stack);
    CHECK(stack.items == NULL);
    CHECK(stack.count == 0 && stack.capacity == 0);
}

/* ---- 2b. Linked stack ------------------------------------------------ */

static void test_linked_stack_starts_empty(void) {
    LinkedStack stack;
    ls_init(&stack);
    CHECK(ls_is_empty(&stack));
    CHECK(stack.top == NULL && stack.size == 0);

    int out = 99;
    CHECK(!ls_pop(&stack, &out));
    CHECK(!ls_peek(&stack, &out));
    CHECK(out == 99);
    ls_free(&stack);
}

static void test_linked_stack_is_last_in_first_out(void) {
    LinkedStack stack;
    ls_init(&stack);
    bool all_pushed = true;
    for (int v = 1; v <= 1000; v++) {
        all_pushed = all_pushed && ls_push(&stack, v);
    }
    CHECK(all_pushed);
    CHECK(stack.size == 1000);

    int out = 0;
    CHECK(ls_peek(&stack, &out) && out == 1000);
    CHECK(stack.size == 1000);

    bool in_order = true;
    for (int expected = 1000; expected >= 1; expected--) {
        in_order = in_order && ls_pop(&stack, &out) && out == expected;
    }
    CHECK(in_order);
    CHECK(ls_is_empty(&stack));
    ls_free(&stack);
}

static void test_linked_stack_free_leaves_it_empty(void) {
    LinkedStack stack;
    ls_init(&stack);
    ls_push(&stack, 1);
    ls_push(&stack, 2);
    ls_free(&stack);                    /* frees nodes still on it */
    CHECK(stack.top == NULL && stack.size == 0);

    int out = 0;
    CHECK(ls_push(&stack, 3));          /* usable again */
    CHECK(ls_pop(&stack, &out) && out == 3);
    ls_free(&stack);
}

int main(void) {
    RUN(test_array_stack_refuses_zero_capacity);
    RUN(test_array_stack_is_last_in_first_out);
    RUN(test_linked_stack_starts_empty);
    RUN(test_linked_stack_is_last_in_first_out);
    RUN(test_linked_stack_free_leaves_it_empty);
    FINISH("Step 2: stack");
}
