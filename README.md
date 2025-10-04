# C++ Systems Projects

This repository is a collection of **standalone C++ systems projects**, each exploring a fundamental layer of computing — from text processing and compiler design to databases, operating systems, and deep learning frameworks.

The goal is to build each component **from scratch**, using primarily **C-style design** (manual memory control, explicit data structures, minimal abstractions), to understand the internal mechanics of real systems.

Each subproject is designed to be **self-contained**: independently compilable, testable, and executable.

---

## Overview of Projects

| Directory        | Description                                                                              | Focus                                        |
| ---------------- | ---------------------------------------------------------------------------------------- | -------------------------------------------- |
| `grep_clone/`    | Custom regex engine based on Thompson’s NFA construction and the Shunting Yard algorithm | Formal languages, parsing, automata          |
| `compiler_6502/` | Minimal compiler and assembler targeting the 6502 instruction set                        | Lexing, parsing, code generation             |
| `mini_os/`       | Basic operating system simulation with processes, scheduling, and memory management      | OS fundamentals, memory, IPC                 |
| `mini_db/`       | Lightweight database engine (in-memory or on-disk) with simple query execution           | Data layout, persistence, indexing           |
| `cpp_server/`    | Single-threaded and multi-threaded HTTP/TCP server prototype                             | Networking, concurrency                      |
| `tiny_dl/`       | Minimal deep learning framework similar in spirit to TinyGrad                            | Tensor algebra, autodiff, computation graphs |
| `shared/`        | Common utilities reused across some modules                                              | Memory pools, error handling, logging        |

Each subdirectory includes its own `CMakeLists.txt` and `README.md`.

---

## Build Instructions

Each project builds independently using **CMake**.

Example:

```bash
cd grep_clone
mkdir build && cd build
cmake ..
make
./grep_clone
```

No external dependencies are required beyond a C++14 (or newer) toolchain.

---

## Design Philosophy

This repository emphasizes:

- **C-style design** – direct structs, pointers, and manual control.
- **Isolation** – no cross-dependencies between subprojects.
- **Incremental complexity** – each project builds intuitively on concepts from the previous one.
- **Educational focus** – reimplement classic algorithms to understand design tradeoffs.

This approach encourages a bottom-up exploration of computer systems:
start from text parsing, move into compilation and runtime behavior, then progress toward persistent storage and computation frameworks.

---

## Suggested Learning Path

If you want to follow the same progression of ideas, this order is recommended:

1. `grep_clone` — Parsing, postfix notation, and state machines
2. `compiler_6502` — Lexing, syntax trees, and code generation
3. `mini_os` — Memory, processes, and scheduling
4. `mini_db` — Persistent storage, B-trees, and indexing
5. `cpp_server` — Concurrency and networking
6. `tiny_dl` — Tensors, gradients, and matrix computation

Each project can be studied, built, and modified independently.

---

## Future Work

- Unified build system across all projects
- Shared runtime utilities for logging and memory allocation
- Consistent test suite format for unit and integration testing
- Potential interoperability between components (e.g., compiler → VM → OS simulation)

---

## References

- Ken Thompson, _“Regular Expression Search Algorithm”_, Communications of the ACM, 1968. [PDF](https://dl.acm.org/doi/pdf/10.1145/363347.363387)
- Russ Cox, _“Regular Expression Matching Can Be Simple and Fast”_, 2007. [Article](https://swtch.com/~rsc/regexp/regexp1.html)
- Niklaus Wirth, _“Compiler Construction”_ (Addison-Wesley, 1996)
- Tanenbaum, _“Modern Operating Systems”_
- Patterson & Hennessy, _“Computer Organization and Design”_
- Aho, Sethi, Ullman, _“Compilers: Principles, Techniques, and Tools”_ (“The Dragon Book”)
