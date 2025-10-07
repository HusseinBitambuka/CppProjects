# C++ Systems Projects

This repository is a collection of **standalone C++ systems projects**, each exploring a fundamental layer of computer systems — from language parsing and compilation to operating systems, databases, and deep learning frameworks.

Every project is built **from scratch**, in modern C++, emphasizing explicit data control, low-level design, and conceptual clarity.  
Some use **manual memory management** (for realism and learning), while others use **smart pointers or pools** (for safety and maintainability).  
No project mixes both approaches internally — each is internally consistent and designed to highlight one style of memory model.

---

## Overview of Projects

| Directory        | Description                                                              | Focus                                       | Memory Strategy                                        |
| ---------------- | ------------------------------------------------------------------------ | ------------------------------------------- | ------------------------------------------------------ |
| `grep_clone/`    | Custom regex engine using Thompson’s NFA and the Shunting Yard algorithm | Parsing, automata theory, text search       | Manual (raw pointers)                                  |
| `MuyagaOS/`      | Educational virtual machine and operating system replacing `mini_os`     | VM, kernel, memory, filesystem, processes   | Mixed by module (manual for kernel, smart for devices) |
| `MuyagaBJ/`      | Educational compiler targeting the MuyagaOS VM                           | Parsing, code generation, runtime interface | Manual (explicit AST + heap allocation)                |
| `compiler_6502/` | Minimal compiler and assembler targeting the 6502 instruction set        | Lexing, parsing, assembly output            | Manual                                                 |
| `mini_db/`       | Lightweight database engine with on-disk persistence                     | Storage, indexing, buffer management        | Smart pointers                                         |
| `cpp_server/`    | Multi-threaded TCP/HTTP server prototype                                 | Networking, concurrency, socket I/O         | Smart pointers                                         |
| `tiny_dl/`       | Minimal deep learning framework inspired by TinyGrad                     | Tensor algebra, autodiff, graph computation | Smart pointers                                         |
| `shared/`        | Common utilities reused across some modules                              | Memory pools, logging, error handling       | Mixed (configurable)                                   |

> **Note:**  
> `mini_os/` has been **merged into MuyagaOS**.  
> All kernel, scheduler, and memory-management code will continue development under `MuyagaOS/`.

---

## Design Philosophy

This repository reflects a **bottom-up exploration of computer systems** — starting from compilers and interpreters, progressing through virtual machines and operating systems, and culminating in storage and distributed computation.

Guiding principles:

- **Transparency** — implement all core systems from first principles
- **Isolation** — each project is self-contained and independently buildable
- **Consistency** — only one memory model per project
- **Reproducibility** — all builds use CMake and standard C++17
- **Educational focus** — each module demonstrates classical system design tradeoffs

---

## Suggested Learning Path

| Stage | Project         | Core Concepts                                    |
| ----- | --------------- | ------------------------------------------------ |
| 1     | `grep_clone`    | Regex parsing, postfix conversion, NFA/DFA       |
| 2     | `compiler_6502` | Lexing, parsing, assembly generation             |
| 3     | `MuyagaOS`      | CPU emulation, memory, kernel, filesystem        |
| 4     | `MuyagaBJ`      | Compiler backend targeting MuyagaOS VM           |
| 5     | `mini_db`       | Storage layout, page caching, indexing           |
| 6     | `cpp_server`    | Concurrency and socket communication             |
| 7     | `tiny_dl`       | Tensor operations, gradients, computation graphs |

`MuyagaOS` is now the **central foundation** — it will host the compiler output from **MuyagaBJ**, load binaries from its file system (BJFS), and run them inside its VM environment.

---

## Repository Structure

```

C++-Systems/
├── MuyagaOS/        # Virtual machine and educational OS
├── MuyagaBJ/        # Compiler targeting MuyagaOS
├── grep_clone/      # Regex engine (NFA/DFA)
├── compiler_6502/   # 6502 compiler and assembler
├── mini_db/         # Minimal database engine
├── cpp_server/      # Network and concurrency prototype
├── tiny_dl/         # Lightweight deep learning engine
├── shared/          # Common utilities
└── docs/            # System architecture and notes

```

---

## Build Instructions

All projects use **CMake ≥ 3.16** and a C++17-compatible compiler.

To build a project:

```bash
cd <project_name>
mkdir build && cd build
cmake ..
make -j$(nproc)
```

To rebuild all:

```bash
find . -type d -name build -exec rm -rf {} +
```

---

## Memory Management Policy

Each project has an **explicit, consistent memory management model**:

- **Manual management (raw pointers)**
  Used where understanding allocation/deallocation is part of the learning goal (e.g., regex engines, kernel internals, compiler ASTs).

- **Smart pointers / RAII**
  Used where complexity or resource lifetime management benefits from abstraction (e.g., file systems, servers, databases).

The two styles are **never mixed** within the same project.

---

## Roadmap

| Phase | Focus Area    | Description                                | Status      |
| ----- | ------------- | ------------------------------------------ | ----------- |
| 1     | MuyagaOS Core | CPU, memory, and devices                   | In progress |
| 2     | Kernel Layer  | Syscalls, processes, and file system       | Planned     |
| 3     | MuyagaBJ      | Compiler backend for MuyagaOS              | Planned     |
| 4     | BJFS Tools    | Disk formatter, file loader, and shell     | Planned     |
| 5     | mini_db       | Persistent page manager                    | Planned     |
| 6     | Integration   | Run MuyagaBJ-compiled binaries in MuyagaOS | Future      |

---

## References

- **Ken Thompson**, _“Regular Expression Search Algorithm”_, CACM (1968)
- **Russ Cox**, _“Regular Expression Matching Can Be Simple and Fast”_, 2007
- **Niklaus Wirth**, _“Compiler Construction”_ (Addison-Wesley, 1996)
- **Andrew Tanenbaum**, _“Modern Operating Systems”_
- **Patterson & Hennessy**, _“Computer Organization and Design”_
- **Fisher & LeBlanc**, _“Crafting a Compiler”_
- **Alex Petrov**, _“Database Internals”_ (O’Reilly, 2019)
- **CMU Database Systems Course (15-445/645)**
- **MIT 6.S081**, _“Operating System Engineering”_
- **CMU 15-213**, _“Introduction to Computer Systems”_

---

## Author’s Note

This repository represents an **integrated systems laboratory** — where virtual machines, compilers, file systems, and databases evolve together.
Each project is both an independent experiment and a step toward a unified software ecosystem centered around **MuyagaOS**.
