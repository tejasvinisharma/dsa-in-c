#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stddef.h>

/*
 * Step 4: infix to postfix (Polish notation), and evaluating postfix.
 * Both are classic uses of a stack.
 *
 *   infix  "A+B*C"     ->  postfix "ABC*+"
 *   infix  "(A+B)*C"   ->  postfix "AB+C*"
 *
 * Operators, highest precedence first:
 *   ^       (right to left: A^B^C means A^(B^C))
 *   * /     (left to right)
 *   + -     (left to right)
 */

/* Convert `infix` to postfix and write it into `out` as a string
 * (no spaces), using at most `out_size` bytes including the '\0'.
 *
 * - Operands are single letters (A-Z, a-z) or single digits (0-9).
 * - Operators are + - * / ^ and brackets are ( ).
 * - Spaces in the input are ignored.
 *
 * Return 0 on success. Return -1 if the brackets don't match, if the
 * input holds any other character, or if `out` is too small.
 * (It doesn't have to check that every operator has two operands.) */
int infix_to_postfix(const char *infix, char *out, size_t out_size);

/* Evaluate a postfix expression whose operands are single digits 0-9,
 * and store the answer in *result.
 *
 * - Operators are + - * / ^. Spaces are ignored.
 * - / is C integer division (7/2 is 3).
 * - ^ is a power with a whole, non-negative exponent (2^3 is 8).
 *
 * Return 0 on success, or -1 (leaving *result alone) if:
 * an operator doesn't have two operands, more than one value is left at
 * the end, the input is empty, there's a division by zero, an exponent is
 * negative, or the input holds any other character. */
int evaluate_postfix(const char *postfix, long *result);

#endif
