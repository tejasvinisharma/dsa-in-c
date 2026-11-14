# Data Structures in C: build guide

This kit gives you the project's skeleton: a header file for each structure that says exactly what every function must do, and tests that check it. **You write the code inside each function in `src/*.c`.** That is what makes this your project, and it's what interviewers will ask you about.

Work through the steps in order: roughly one a week, alongside CSE205. Check each step with its tests, then commit. Looking things up is normal. If a person or an AI helps you, ask them to explain the idea, then type the code yourself. You should be able to explain every line.

| Step | What you write | Main thing you learn | Rough time |
|---|---|---|---|
| 0 | Setup | gcc, make, Git | 1 hour |
| 1 | Singly linked list, `linked_list.c` | `malloc`, `free`, walking and re-linking nodes | 3–4 hours |
| 2 | Stack two ways, `stack.c` | Arrays vs linked nodes, overflow and underflow | 2 hours |
| 3 | Circular queue, `queue.c` | Wrapping round an array with `%` | 1–2 hours |
| 4 | Infix to postfix, `expression.c` | Using a stack to handle precedence | 2–3 hours |
| 5 | Sorting, `sorting.c` | Four algorithms and their complexity | 3 hours |
| 6 | Searching, `search.c` | Binary search and its edge cases | 1 hour |
| 7 | Finish | README, complexity table, pin the repo | 1 hour |

---

## Step 0: Setup

1. **Check for a compiler.** Open Git Bash (it came with Git) and run `gcc --version` and `make --version`.
2. **If either is missing on Windows**, install MSYS2 from [msys2.org](https://www.msys2.org). Open the **MSYS2 UCRT64** terminal from the Start menu and run:
   ```bash
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc make
   ```
   Then use the MSYS2 UCRT64 terminal for this project.
3. **Get the code.** Go to the folder where you keep projects and run:
   ```bash
   git clone https://github.com/tejasvinisharma/dsa-in-c.git
   cd dsa-in-c
   ```
   Open the `dsa-in-c` folder in VS Code.
4. **Run Step 1's tests:** `make step1`. You should see `Not written yet: ll_create() (Step 1)`. That's correct: nothing is written yet.
5. **Without make**, the same test builds with one command:
   ```bash
   mkdir -p build
   gcc -std=c11 -Wall -Isrc -o build/test_linked_list tests/test_linked_list.c src/linked_list.c
   ./build/test_linked_list
   ```
6. **Save your work to GitHub** after every step:
   ```bash
   git add .
   git commit -m "Describe what you did"
   git push
   ```

### Reading the test output

- `FAIL  tests/test_linked_list.c line 40:  list_equals(list, expected, 3)` tells you which check failed. Open the test file at that line to see what it expected.
- `Not written yet: ll_push_back()` means a test reached a function you haven't written. Delete its `TODO(...)` line when you write it.
- `Segmentation fault` means the program followed a `NULL` or freed pointer. The last test name printed above it is the one that crashed.
- If a test seems to hang, press `Ctrl+C`: a loop never ends. In binary search this is a classic.
- To see your list while debugging, call `ll_print(list);` inside a test.

---

## Step 1: Singly linked list

**Goal:** every function in `linked_list.h`, with `size` always equal to the number of nodes.

**Read first:** the linked lists chapter of your CSE205 book (Schaum's Outline, Lipschutz), [malloc](https://en.cppreference.com/w/c/memory/malloc), [free](https://en.cppreference.com/w/c/memory/free)

**Hints**
- Write `ll_create` and `ll_free` first: every test uses them. Then go down the header in order, because the tests stop at the first function that still says `TODO`. The same goes for `as_free`, `ls_free` and `cq_free` in Steps 2 and 3.
- Draw three boxes and arrows on paper before you write `ll_insert_at`, `ll_remove` and `ll_reverse`. Every pointer change becomes one line of code.
- A small helper saves repeating yourself: `static Node *new_node(int value, Node *next)` that mallocs a node and fills it in. Return `NULL` if `malloc` fails.
- `ll_push_back`: an empty list is a special case. Otherwise walk until `node->next == NULL`, then link the new node there.
- `ll_pop_front`: read the head's value and remember the head, move `list->head` on, *then* free the old head.
- `ll_insert_at`: index 0 is the same as `ll_push_front`. Otherwise walk to the node at `index - 1` and link the new node after it.
- `ll_remove`: walk with two pointers, `prev` and `current`. Removing the head is a special case.
- `ll_reverse`: three pointers, `prev`, `current` and `next`. Each loop: save `current->next`, point `current->next` back at `prev`, then move both forward. Finally, `list->head = prev`.
- `ll_free`: save `node->next` *before* you free `node`.

**Check:** `make step1` → `Step 1: linked list: 60 of 60 checks passed`
**Commit:** `git commit -am "Add singly linked list"` then `git push`
**README:** fill in row 1's time complexity (for example `push front O(1), push back O(n), find O(n), reverse O(n)`) and change its status to Done.

---

## Step 2: Stack, two ways

**Goal:** the same stack on an array (2a) and on linked nodes (2b).

**Read first:** the stacks chapter of your CSE205 book

**Hints**
- 2a. `as_init`: `malloc(capacity * sizeof(int))`. `count` is both the number of values and the index of the next free slot.
- 2a. Push is `items[count] = value; count++;` and pop is the reverse. Check full or empty first: that's overflow and underflow.
- 2b. Pushing onto a linked stack is the same as `ll_push_front`, and popping is `ll_pop_front`. You've done this already.
- 2b. `ls_free` can just pop until the stack is empty.

**Check:** `make step2` → `Step 2: stack: 38 of 38 checks passed`
**Commit:** `"Add array and linked stacks"`

---

## Step 3: Circular queue

**Goal:** a queue on a fixed array that reuses the slots freed by dequeue.

**Read first:** the queues section of your CSE205 book

**Hints**
- The next free slot is `(front + count) % capacity`.
- After a dequeue, `front = (front + 1) % capacity`.
- Storing `count` means full is `count == capacity` and empty is `count == 0`. No wasted slot is needed.
- Walk through `test_wraps_round_the_array` on paper with a 3-slot array before you code it.

**Check:** `make step3` → `Step 3: circular queue: 30 of 30 checks passed`
**Commit:** `"Add circular queue"`

---

## Step 4: Infix to postfix, and evaluating postfix

**Goal:** `"A+B*C"` → `"ABC*+"`, and `"234*+"` → 14.

**Read first:** the Polish notation section of your CSE205 book, [isalnum](https://en.cppreference.com/w/c/string/byte/isalnum), [isdigit](https://en.cppreference.com/w/c/string/byte/isdigit)

**Hints for `infix_to_postfix`**
- Use a `char` array as the operator stack. A fixed size such as 256 is fine for this project.
- Read the input left to right and skip spaces:
  - letter or digit → straight to the output
  - `(` → push it
  - `)` → pop operators to the output until you reach `(`, then throw the `(` away. If there's no `(`, return -1.
  - operator → while the top of the stack is an operator with *higher* precedence, or *equal* precedence and the new operator isn't `^`, pop it to the output. Then push the new operator.
  - anything else → return -1
- At the end, pop everything left to the output. A `(` still on the stack means a bracket was never closed: return -1.
- Before writing each output character, check that `length + 1 < out_size` (keep room for the `'\0'`).
- Pass `(unsigned char)c` to `isalnum` and `isdigit`.

**Hints for `evaluate_postfix`**
- Use an array of `long` as the stack. A digit `c` becomes the number `c - '0'`.
- For an operator, pop **b first, then a**, and push `a op b`. The order matters for `-`, `/` and `^`.
- At the end, exactly one value must be left. Only then write it to `*result`.

**Check:** `make step4` → `Step 4: infix to postfix: 45 of 45 checks passed`
**Commit:** `"Add infix to postfix conversion and evaluation"`

---

## Step 5: Sorting

**Goal:** four sorts that all give the same result as the C library's `qsort`.

**Read first:** the sorting chapter of your CSE205 book

**Hints**
- **Watch out for `size_t`:** it can't go below 0. When `n` is 0, `n - 1` is a huge number, not -1. Write loop conditions as `i + 1 < n` instead of `i < n - 1`.
- Bubble: after each pass the biggest remaining value has reached the end, so each pass can stop one place earlier. Keep a `swapped` flag and stop when a pass makes no swaps.
- Selection: remember the *index* of the smallest value, and swap once per pass.
- Insertion: save `a[i]` in `key`, shift bigger values right with `while (j > 0 && a[j - 1] > key)`, then put `key` in the gap.
- Merge: write a helper that sorts `a[lo]` to `a[hi - 1]`. Malloc one temporary array in `merge_sort`, pass it to the helper, and free it at the end.

**Check:** `make step5` → `Step 5: sorting: 37 of 37 checks passed`
**Commit:** `"Add bubble, selection, insertion and merge sort"`

---

## Step 6: Searching

**Goal:** linear search on any array, binary search on a sorted one.

**Hints**
- Binary search over `lo` to `hi`, where `hi` is one past the end: start with `lo = 0`, `hi = n`, and loop `while (lo < hi)`.
- `mid = lo + (hi - lo) / 2`. If `a[mid] < key`, search right with `lo = mid + 1`. Otherwise, if it's not a match, search left with `hi = mid`.
- If it hangs, you probably wrote `lo = mid`.

**Check:** `make step6` → `Step 6: searching: 18 of 18 checks passed`, and `make test` now passes every step.
**Commit:** `"Add linear and binary search"`

---

## Step 7: Finish

1. **README:** every row Done with its time complexity, and 3–5 honest points under "What I learned".
2. **Screenshot:** run `make test` and add a screenshot of the passing scores to the README.
3. **Pin the repository** on your GitHub profile, and change its row in your profile README to Done.

## Stretch goals (pick any)

- **Tail pointer:** add `Node *tail` to `LinkedList` so `ll_push_back` is O(1). Update every function that changes the last node.
- **Binary search for the first match:** in `{1, 2, 2, 2, 3}`, return 1 for key 2, still in O(log n).
- **Quick sort**, and a timing comparison of all five sorts on 100,000 values.
- **Doubly linked list** with `prev` pointers.
- **Multi-digit numbers** in `evaluate_postfix`, separated by spaces.

## Be ready to explain

Once you've finished, you should be able to answer these without looking:

1. Why is `ll_push_back` O(n) here, and what one extra field would make it O(1)?
2. What goes wrong if you free a node before reading its `next`?
3. When would you choose an array stack over a linked stack, and the other way round?
4. How does your circular queue tell full from empty?
5. Walk through `A+B*C` with your operator stack, one character at a time.
6. Why is `^` treated differently from `-` when two operators have equal precedence?
7. Best and worst case for each sort. Which would you use for 10 values, and which for a million?
8. Why `lo + (hi - lo) / 2` rather than `(lo + hi) / 2`?
