# Build and run the tests.
#
#   make step1     Step 1 only (linked list)
#   make test      every step, in order; stops at the first one that fails
#   make clean     delete the build folder
#
# Run these in Git Bash or the MSYS2 terminal on Windows, or any terminal
# on Mac or Linux.

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wno-unused-parameter -g
BUILD = build

MODULES = linked_list stack queue expression sorting search

.PHONY: test clean step1 step2 step3 step4 step5 step6

test: step1 step2 step3 step4 step5 step6

step1: $(BUILD)/test_linked_list
	./$<
step2: $(BUILD)/test_stack
	./$<
step3: $(BUILD)/test_queue
	./$<
step4: $(BUILD)/test_expression
	./$<
step5: $(BUILD)/test_sorting
	./$<
step6: $(BUILD)/test_search
	./$<

$(BUILD)/test_%: tests/test_%.c src/%.c src/%.h src/todo.h tests/test_util.h | $(BUILD)
	$(CC) $(CFLAGS) -Isrc -o $@ tests/test_$*.c src/$*.c

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
