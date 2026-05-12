*This project has been created as part of the 42 curriculum by faharila, ainarako.*

---

# push_swap

## Description

`push_swap` is a sorting algorithm project from the 42 school curriculum. The goal is to sort a stack of integers using a limited set of operations on two stacks (`a` and `b`), while minimizing the total number of operations performed.

The program reads a list of integers as arguments, outputs the sequence of operations needed to sort them in ascending order on stack `a`, and includes a `checker` program that validates whether a given sequence of operations correctly sorts the input.

### Available Operations

| Operation | Effect |
|-----------|--------|
| `sa` | Swap the top two elements of stack a |
| `sb` | Swap the top two elements of stack b |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | Push the top element of stack b onto stack a |
| `pb` | Push the top element of stack a onto stack b |
| `ra` | Rotate stack a upward (top becomes bottom) |
| `rb` | Rotate stack b upward |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | Reverse rotate stack a (bottom becomes top) |
| `rrb` | Reverse rotate stack b |
| `rrr` | `rra` and `rrb` simultaneously |

### Benchmark Mode

The project includes a built-in benchmark system (`--bench` flag) that measures the number of each operation performed and reports the total operation count along with the strategy used.

---

## Algorithms

Three sorting strategies are implemented, selected based on the size and disorder of the input. An adaptive mode (`--adaptive`) automatically picks the best strategy.

### Simple Sort (`--simple`) — for small inputs (≤ 5 elements)

A hardcoded, case-by-case sorting approach tailored for very small stacks. Because the number of permutations is tiny, it is possible to write optimal decision trees directly without any general-purpose algorithm. This gives the lowest possible operation count for inputs of 2 to 5 elements.

**Justification:** Any general algorithm has overhead (index computation, chunk management, etc.) that becomes wasteful for tiny inputs. Hardcoded decision trees for ≤ 5 elements are provably optimal and extremely fast.

### Medium Sort (`--medium`) — for moderately disordered inputs

A chunk-based insertion sort. The stack is divided into chunks of size `√n`. Elements belonging to each chunk are pushed to stack `b` in order, then pulled back to stack `a` one by one in sorted order.

- Chunk size is computed as `(int)sqrt(size)`, giving a good trade-off between the number of rotations needed to find each target element and the number of push/pull cycles.
- Within each chunk, elements are located by rotating stack `b` until the target index is at the top, then pushed back to `a`.

**Justification:** Chunk-based approaches reduce the number of rotations compared to naive insertion sort (O(n²)) while being simpler and more cache-friendly than a full radix sort for medium-sized inputs. The `√n` chunk size minimises the worst-case rotation cost per element.

### Radix Sort (`--complex`) — for large or highly disordered inputs

A bitwise radix sort (LSD — Least Significant Bit first). Elements are first mapped to contiguous indices (0, 1, 2, …, n−1) to allow bit-level comparisons. For each bit position, elements whose current bit is `0` are pushed to stack `b`; elements whose bit is `1` stay in (or are rotated through) stack `a`. After processing all bits, the stacks are merged.

**Justification:** Radix sort runs in O(n × k) where k is the number of bits needed to represent n (≈ log₂ n). For large inputs (100–500 elements), this dramatically outperforms comparison-based strategies. It requires no comparisons between elements — only bit reads — making it well suited to the limited push_swap operation set.

### Adaptive Mode (`--adaptive`)

Computes a *disorder score* for the input (a normalized measure of how far the stack is from sorted order) and automatically selects:

- `simple_sort` if disorder < 0.2 (nearly sorted)
- `medium_sort` if disorder < 0.5 (moderately shuffled)
- `radix_sort` otherwise (heavily shuffled / large input)

**Justification:** No single algorithm is optimal across all input sizes and disorder levels. The adaptive mode avoids over-engineering small inputs with a heavy radix pass and avoids under-serving large inputs with an O(n²) approach.

---

## Contributions

| Login | Contributions |
|-------|--------------|
| `faharila` | Core sorting algorithms (`simple_sort`, `medium_sort`, `radix_sort`), adaptive algorithm (`adaptive.c`), stack operations (push, swap, rotate, reverse-rotate), argument checking and stack initialization, main entry point |
| `ainarako` | Benchmark system (`bench.h`, `bench.c`, `bench_utils.c`, `bench_p_utils.c`, `bench_r_utils.c`, `bench_s_utils.c`), checker program, Makefile, `get_next_line` integration |

---

## Instructions

### Requirements

- A C compiler (`cc`) with support for C99 or later
- The `math` library (`-lm`), available on standard POSIX systems
- GNU Make

### Compilation

```bash
# Build both push_swap and checker
make

# Build only push_swap
make push_swap

# Build only checker
make checker

# Clean object files
make clean

# Remove all build artefacts
make fclean

# Rebuild from scratch
make re
```

### Usage

```bash
# Sort a list of integers
./push_swap 5 3 1 4 2

# Use a specific algorithm
./push_swap --simple 3 1 2
./push_swap --medium 42 7 13 99 1 55 23
./push_swap --complex $(shuf -i 1-500 -n 500 | tr '\n' ' ')
./push_swap --adaptive 8 3 6 1 7 2

# Validate output with checker
./push_swap 5 3 1 4 2 | ./checker 5 3 1 4 2

# Run benchmark (reports operation counts)
./push_swap --bench 5 3 1 4 2
./push_swap --bench --adaptive $(shuf -i 1-100 -n 100 | tr '\n' ' ')
```

The `checker` program reads operation instructions from standard input and prints `OK` if the stack ends up sorted, or `KO` otherwise.

### Input Constraints

- All arguments must be valid integers within the `int` range.
- Duplicate values are not allowed.
- The program exits with an error message on invalid input.

---

## Resources

### Official / Academic References

- [Wikipedia — Radix sort](https://en.wikipedia.org/wiki/Radix_sort) — Theory and complexity analysis of LSD/MSD radix sort.
- [Wikipedia — Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort) — Background for the chunk-based medium sort strategy.
- [Sorting Algorithm Visualizer](https://visualgo.net/en/sorting) — Interactive visualizations for common sorting algorithms.
- [42 push_swap subject (PDF)](https://cdn.intra.42.fr/pdf/pdf/81152/en.subject.pdf) — Official project specification.

### Community Guides

- [push_swap tutorial by Ayoub](https://medium.com/@ayoub.a/push-swap-tutorial-e6ff19f73c4) — A step-by-step walkthrough of common push_swap strategies.
- [The Turk algorithm explained](https://medium.com/@jamierobertdawson/push-swap-the-least-number-of-moves-with-two-stacks-d1e76a71789a) — One of the most referenced community algorithms for 100/500 element inputs.

### AI Usage

Claude (Anthropic) was used as an assistant during this project for the following tasks:

- **Debugging:** Identifying off-by-one errors in chunk boundary calculations inside `medium.c` and rotation logic in the radix sort.
- **Code review:** Reviewing the `bench` infrastructure for correctness and suggesting the separation of benchmark counters into dedicated files (`bench_p_utils.c`, `bench_r_utils.c`, `bench_s_utils.c`) for clarity.
- **Documentation:** Generating this README based on source files and project requirements.

All algorithmic design decisions, implementation, and testing were done by the project authors.
