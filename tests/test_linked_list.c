#include <stdlib.h>

#include "linked_list.h"
#include "test_util.h"

/* True if the list holds exactly expected[0..n-1], in order, and
 * list->size is n. */
static bool list_equals(const LinkedList *list, const int *expected, size_t n) {
    if (list->size != n) {
        return false;
    }
    const Node *node = list->head;
    for (size_t i = 0; i < n; i++) {
        if (node == NULL || node->value != expected[i]) {
            return false;
        }
        node = node->next;
    }
    return node == NULL;
}

static void test_create_gives_an_empty_list(void) {
    LinkedList *list = ll_create();
    CHECK(list != NULL);
    CHECK(list->head == NULL);
    CHECK(list->size == 0);
    ll_free(list);
}

static void test_push_front_adds_at_the_start(void) {
    LinkedList *list = ll_create();
    CHECK(ll_push_front(list, 1));
    CHECK(ll_push_front(list, 2));
    CHECK(ll_push_front(list, 3));
    int expected[] = {3, 2, 1};
    CHECK(list_equals(list, expected, 3));
    ll_free(list);
}

static void test_push_back_adds_at_the_end(void) {
    LinkedList *list = ll_create();
    CHECK(ll_push_back(list, 1));
    CHECK(ll_push_back(list, 2));
    CHECK(ll_push_back(list, 3));
    int expected[] = {1, 2, 3};
    CHECK(list_equals(list, expected, 3));
    ll_free(list);
}

static void test_push_front_and_back_together(void) {
    LinkedList *list = ll_create();
    ll_push_back(list, 2);
    ll_push_front(list, 1);
    ll_push_back(list, 3);
    int expected[] = {1, 2, 3};
    CHECK(list_equals(list, expected, 3));
    ll_free(list);
}

static void test_pop_front_removes_the_first_value(void) {
    LinkedList *list = ll_create();
    ll_push_back(list, 10);
    ll_push_back(list, 20);

    int out = 0;
    CHECK(ll_pop_front(list, &out));
    CHECK(out == 10);
    CHECK(list->size == 1);

    CHECK(ll_pop_front(list, &out));
    CHECK(out == 20);
    CHECK(list->size == 0);
    CHECK(list->head == NULL);

    out = 99;
    CHECK(!ll_pop_front(list, &out));   /* empty: nothing to pop */
    CHECK(out == 99);                   /* ...and *out is left alone */
    ll_free(list);
}

static void test_insert_at_each_position(void) {
    LinkedList *list = ll_create();
    CHECK(ll_insert_at(list, 0, 5));    /* into an empty list */
    CHECK(ll_insert_at(list, 1, 7));    /* index == size: the back */
    CHECK(ll_insert_at(list, 0, 1));    /* the front */
    CHECK(ll_insert_at(list, 2, 6));    /* the middle */
    int expected[] = {1, 5, 6, 7};
    CHECK(list_equals(list, expected, 4));

    CHECK(!ll_insert_at(list, 5, 9));   /* past the end: refused */
    CHECK(list_equals(list, expected, 4));
    ll_free(list);
}

static void test_find_returns_the_first_position(void) {
    LinkedList *list = ll_create();
    CHECK(ll_find(list, 4) == -1);      /* empty list */
    int values[] = {4, 8, 4, 2};
    for (size_t i = 0; i < 4; i++) {
        ll_push_back(list, values[i]);
    }
    CHECK(ll_find(list, 4) == 0);
    CHECK(ll_find(list, 8) == 1);
    CHECK(ll_find(list, 2) == 3);
    CHECK(ll_find(list, 99) == -1);
    ll_free(list);
}

static void test_remove_from_head_middle_and_tail(void) {
    LinkedList *list = ll_create();
    int values[] = {1, 2, 3, 2};
    for (size_t i = 0; i < 4; i++) {
        ll_push_back(list, values[i]);
    }

    CHECK(ll_remove(list, 2));          /* first 2 only */
    int after_middle[] = {1, 3, 2};
    CHECK(list_equals(list, after_middle, 3));

    CHECK(ll_remove(list, 1));          /* the head */
    int after_head[] = {3, 2};
    CHECK(list_equals(list, after_head, 2));

    CHECK(ll_remove(list, 2));          /* the tail */
    int after_tail[] = {3};
    CHECK(list_equals(list, after_tail, 1));

    CHECK(!ll_remove(list, 42));        /* not in the list */
    CHECK(list_equals(list, after_tail, 1));

    CHECK(ll_remove(list, 3));          /* the last node */
    CHECK(list->head == NULL);
    CHECK(list->size == 0);
    CHECK(!ll_remove(list, 3));         /* empty list */
    ll_free(list);
}

static void test_reverse_relinks_the_same_nodes(void) {
    LinkedList *list = ll_create();
    ll_reverse(list);                   /* empty: nothing happens */
    CHECK(list->head == NULL);

    ll_push_back(list, 5);
    ll_reverse(list);                   /* one node */
    int one[] = {5};
    CHECK(list_equals(list, one, 1));
    ll_free(list);

    list = ll_create();
    for (int v = 1; v <= 4; v++) {
        ll_push_back(list, v);
    }
    Node *first = list->head;
    Node *last = list->head->next->next->next;
    ll_reverse(list);
    int expected[] = {4, 3, 2, 1};
    CHECK(list_equals(list, expected, 4));
    CHECK(list->head == last);          /* same nodes, not copies */
    CHECK(last->next->next->next == first);
    CHECK(first->next == NULL);

    CHECK(ll_push_back(list, 0));       /* still works after reversing */
    int after_push[] = {4, 3, 2, 1, 0};
    CHECK(list_equals(list, after_push, 5));
    ll_free(list);
}

static void test_a_thousand_values(void) {
    LinkedList *list = ll_create();
    bool all_pushed = true;
    for (int v = 0; v < 1000; v++) {
        all_pushed = all_pushed && ll_push_back(list, v);
    }
    CHECK(all_pushed);
    CHECK(list->size == 1000);
    CHECK(ll_find(list, 999) == 999);

    ll_reverse(list);
    CHECK(list->head->value == 999);

    long sum = 0;
    int out;
    while (ll_pop_front(list, &out)) {
        sum += out;
    }
    CHECK(sum == 999L * 1000 / 2);
    CHECK(list->size == 0);
    ll_free(list);
}

static void test_free_accepts_null(void) {
    ll_free(NULL);                      /* must not crash */
    CHECK(true);
}

int main(void) {
    RUN(test_create_gives_an_empty_list);
    RUN(test_push_front_adds_at_the_start);
    RUN(test_push_back_adds_at_the_end);
    RUN(test_push_front_and_back_together);
    RUN(test_pop_front_removes_the_first_value);
    RUN(test_insert_at_each_position);
    RUN(test_find_returns_the_first_position);
    RUN(test_remove_from_head_middle_and_tail);
    RUN(test_reverse_relinks_the_same_nodes);
    RUN(test_a_thousand_values);
    RUN(test_free_accepts_null);
    FINISH("Step 1: linked list");
}
