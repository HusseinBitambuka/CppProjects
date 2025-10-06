# C++ Systems Projects

This repository is a collection of **standalone C++ systems projects**, each exploring a fundamental layer of computing — from text processing and compiler design to databases, operating systems, and deep learning frameworks.

The goal is to build each component **from scratch**, with each project adopting a _single, consistent memory management model_:

- Some projects use **manual memory management** in a **C-style design**, emphasizing pointers, lifetimes, and explicit deallocation.
- Other projects use **modern C++ smart pointers (RAII)** and standard containers for resource safety and ownership tracking.

No project mixes these paradigms — each serves as a controlled exploration of one design philosophy, allowing clean comparisons between low-level and modern C++ systems approaches.

Each subproject is **self-contained**, independently compilable, testable, and executable.

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

No external dependencies are required beyond a **C++17** (or newer) toolchain.

---

## Design Philosophy

This repository explores **how complex systems are built from first principles**, emphasizing the real-world tradeoffs between manual control, abstraction, and safety.

### Core Principles

- **One memory model per project** — no mixing of manual and automatic management within the same codebase.

  - Projects like `grep_clone` and `mini_os` use **manual control** (`new`, `delete`, custom allocators).
  - Projects like `compiler_6502` and `tiny_dl` use **RAII and smart pointers** (`std::unique_ptr`, `std::shared_ptr`).
    This makes each system a clean “laboratory” for studying its own resource model.

- **Isolation** — all projects compile and execute independently.

- **Incremental complexity** — each project builds upon the ideas introduced in earlier ones, moving from parsing and automata to runtime execution, persistence, and computation.

- **Educational intent** — to reimplement classical systems by hand and understand their underlying algorithms, architectures, and tradeoffs.

---

## Suggested Learning Path

A recommended order to study or build these projects:

1. **`grep_clone`** — Parsing, postfix notation, NFA/DFA-based regex engine
2. **`compiler_6502`** — Lexing, parsing, and 6502 code generation
3. **`mini_os`** — Memory management, processes, scheduling, IPC
4. **`mini_db`** — File systems, B-trees, storage, and query execution
5. **`cpp_server`** — I/O multiplexing, sockets, and concurrency models
6. **`tiny_dl`** — Tensors, computation graphs, backpropagation

Each project can be studied, modified, and extended independently.

---

## Memory Models Across Projects

| Project         | Memory Model                                   | Core Tools                            | Purpose                                             |
| --------------- | ---------------------------------------------- | ------------------------------------- | --------------------------------------------------- |
| `grep_clone`    | Manual (raw pointers, explicit free functions) | `new`, `delete`, `freeNFA`, `freeDFA` | Study lifetime management and automata construction |
| `compiler_6502` | RAII / smart pointers                          | `std::unique_ptr`, `std::shared_ptr`  | Safe AST and symbol table management                |
| `mini_os`       | Manual / custom allocators                     | Simulated paging and heap             | Learn OS-level resource handling                    |
| `mini_db`       | Configurable: in-memory vs on-disk             | Buffer pool + block cache             | Study durability and I/O control                    |
| `cpp_server`    | RAII + thread-safe containers                  | Scoped resources, locks               | Demonstrate concurrent system design                |
| `tiny_dl`       | Shared ownership graphs                        | `std::shared_ptr`, `weak_ptr`         | Manage interdependent computation graphs            |

This design encourages learning through **contrast** — how systems differ when ownership and lifetimes are managed explicitly versus implicitly.

---

## Future Work

- Shared runtime library for logging, allocators, and diagnostics
- Unified build system across all projects
- Cross-project integration (compiler → VM → OS → DB)
- Visualization utilities for automata, ASTs, and scheduling graphs
- Memory pool benchmarking framework (manual vs RAII)

---

## References

- Ken Thompson, _“Regular Expression Search Algorithm”_, **Communications of the ACM**, 1968. [PDF](https://dl.acm.org/doi/pdf/10.1145/363347.363387)
- Russ Cox, _“Regular Expression Matching Can Be Simple and Fast”_, 2007. [Article](https://swtch.com/~rsc/regexp/regexp1.html)
- **Charles N. Fischer, Ron K. Cytron, and Richard J. LeBlanc, Jr.**, _“Crafting a Compiler”_ (Pearson, 2010)
- **CMU Database Systems Course (15-445/645)** – Carnegie Mellon University. [Course Site](https://15445.courses.cs.cmu.edu/)
- **Alex Petrov**, _“Database Internals”_ (O’Reilly, 2019)
- **Niklaus Wirth**, _“Compiler Construction”_ (Addison-Wesley, 1996)
- **Andrew S. Tanenbaum**, _“Modern Operating Systems”_
- **Patterson & Hennessy**, _“Computer Organization and Design”_
- **Aho, Sethi, Ullman**, _“Compilers: Principles, Techniques, and Tools”_ (“The Dragon Book”)
