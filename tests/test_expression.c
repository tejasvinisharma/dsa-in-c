#include <string.h>

#include "expression.h"
#include "test_util.h"

/* True if infix_to_postfix succeeds and gives exactly `expected`. */
static bool converts_to(const char *infix, const char *expected) {
    char out[64];
    memset(out, 'x', sizeof out);
    return infix_to_postfix(infix, out, sizeof out) == 0 &&
           strcmp(out, expected) == 0;
}

static bool is_rejected(const char *infix) {
    char out[64];
    return infix_to_postfix(infix, out, sizeof out) == -1;
}

/* True if evaluate_postfix succeeds and gives `expected`. */
static bool evaluates_to(const char *postfix, long expected) {
    long result = -12345;
    return evaluate_postfix(postfix, &result) == 0 && result == expected;
}

static bool evaluation_fails(const char *postfix) {
    long result = -12345;
    return evaluate_postfix(postfix, &result) == -1 && result == -12345;
}

static void test_precedence(void) {
    CHECK(converts_to("A+B", "AB+"));
    CHECK(converts_to("A+B*C", "ABC*+"));
    CHECK(converts_to("A*B+C", "AB*C+"));
    CHECK(converts_to("A+B^C*D", "ABC^D*+"));
}

static void test_left_and_right_associativity(void) {
    CHECK(converts_to("A-B-C", "AB-C-"));       /* (A-B)-C */
    CHECK(converts_to("A/B*C", "AB/C*"));       /* (A/B)*C */
    CHECK(converts_to("A^B^C", "ABC^^"));       /* A^(B^C) */
}

static void test_brackets(void) {
    CHECK(converts_to("(A+B)*C", "AB+C*"));
    CHECK(converts_to("A*(B+C*D)+E", "ABCD*+*E+"));
    CHECK(converts_to("((A))", "A"));
    /* The worked example from the Schaum's Outline chapter on stacks: */
    CHECK(converts_to("A+(B*C-(D/E^F)*G)*H", "ABC*DEF^/G*-H*+"));
}

static void test_spaces_digits_and_lowercase(void) {
    CHECK(converts_to(" A + B ", "AB+"));
    CHECK(converts_to("2*(3+4)", "234+*"));
    CHECK(converts_to("a+b*c", "abc*+"));
}

static void test_bad_infix_is_rejected(void) {
    CHECK(is_rejected("(A+B"));                 /* bracket never closed */
    CHECK(is_rejected("A+B)"));                 /* closing with no opening */
    CHECK(is_rejected(")A("));
    CHECK(is_rejected("A&B"));                  /* unknown character */
    CHECK(is_rejected("AB12+="));
}

static void test_output_buffer_size(void) {
    char out[4];
    CHECK(infix_to_postfix("A+B", out, 4) == 0);  /* "AB+" plus '\0' fits */
    CHECK(strcmp(out, "AB+") == 0);
    char small[3];
    CHECK(infix_to_postfix("A+B", small, 3) == -1);  /* doesn't fit */
}

static void test_evaluate(void) {
    CHECK(evaluates_to("23+", 5));
    CHECK(evaluates_to("234*+", 14));
    CHECK(evaluates_to("52-", 3));
    CHECK(evaluates_to("08-", -8));
    CHECK(evaluates_to("72/", 3));              /* integer division */
    CHECK(evaluates_to("23^", 8));
    CHECK(evaluates_to("20^", 1));
    CHECK(evaluates_to("232^^", 512));          /* 2^(3^2) */
    CHECK(evaluates_to("5 6 2 + * 8 4 / -", 38));
    CHECK(evaluates_to("7", 7));
}

static void test_bad_postfix_fails(void) {
    CHECK(evaluation_fails(""));                /* nothing to evaluate */
    CHECK(evaluation_fails("+"));
    CHECK(evaluation_fails("2+"));              /* operator short of operands */
    CHECK(evaluation_fails("23"));              /* two values left over */
    CHECK(evaluation_fails("50/"));             /* division by zero */
    CHECK(evaluation_fails("201-^"));           /* 2^(0-1): negative exponent */
    CHECK(evaluation_fails("2a+"));             /* unknown character */
}

static void test_convert_then_evaluate(void) {
    char postfix[64];
    long result = 0;
    CHECK(infix_to_postfix("(1+2)*(3+4)", postfix, sizeof postfix) == 0);
    CHECK(evaluate_postfix(postfix, &result) == 0);
    CHECK(result == 21);
    CHECK(infix_to_postfix("9-2^3/4", postfix, sizeof postfix) == 0);
    CHECK(evaluate_postfix(postfix, &result) == 0);
    CHECK(result == 7);                         /* 9 - (8/4) */
}

int main(void) {
    RUN(test_precedence);
    RUN(test_left_and_right_associativity);
    RUN(test_brackets);
    RUN(test_spaces_digits_and_lowercase);
    RUN(test_bad_infix_is_rejected);
    RUN(test_output_buffer_size);
    RUN(test_evaluate);
    RUN(test_bad_postfix_fails);
    RUN(test_convert_then_evaluate);
    FINISH("Step 4: infix to postfix");
}
