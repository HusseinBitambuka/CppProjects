# C++ Systems Projects

This repository is a collection of **standalone C++ systems projects**, each exploring a fundamental layer of computer systems — from language parsing and compilation to operating systems, databases, and deep learning frameworks.

Every project is built **from scratch**, in modern C++, emphasizing explicit data control, low-level design, and conceptual clarity.  
Some use **manual memory management** (for realism and learning), while others use **smart pointers or memory pools** (for safety and maintainability).  
No project mixes both approaches internally — each is internally consistent and designed to highlight one style of memory model.

---

## Overview of Projects

| Directory     | Description                                                              | Focus                                       | Memory Strategy                                        |
| ------------- | ------------------------------------------------------------------------ | ------------------------------------------- | ------------------------------------------------------ |
| `grep_clone/` | Custom regex engine using Thompson’s NFA and the Shunting Yard algorithm | Parsing, automata theory, text search       | Manual (raw pointers)                                  |
| `MuyagaBJ/`   | **Active project:** Compiler and runtime interface targeting MuyagaOS    | Parsing, code generation, runtime interface | Manual (explicit AST + heap allocation)                |
| `MuyagaOS/`   | Educational virtual machine and operating system replacing `mini_os`     | VM, kernel, memory, filesystem, processes   | Mixed by module (manual for kernel, smart for devices) |
| `mini_db/`    | Lightweight database engine with on-disk persistence                     | Storage, indexing, buffer management        | Smart pointers                                         |
| `cpp_server/` | Multi-threaded TCP/HTTP server prototype                                 | Networking, concurrency, socket I/O         | Smart pointers                                         |
| `tiny_dl/`    | Minimal deep learning framework inspired by TinyGrad                     | Tensor algebra, autodiff, graph computation | Smart pointers                                         |
| `shared/`     | Common utilities reused across multiple modules                          | Memory pools, logging, error handling       | Mixed (configurable)                                   |

---

## Design Philosophy

This repository reflects a **bottom-up exploration of computer systems** — starting from compilers and interpreters, progressing through virtual machines and operating systems, and culminating in persistent storage and computation frameworks.

Guiding principles:

- **Transparency** — implement all core systems from first principles
- **Isolation** — each project is self-contained and independently buildable
- **Consistency** — one memory model per project
- **Reproducibility** — all builds use CMake and standard C++17
- **Educational focus** — each module demonstrates classical system design tradeoffs

---

## Suggested Learning Path

| Stage | Project      | Core Concepts                                    |
| ----- | ------------ | ------------------------------------------------ |
| 1     | `grep_clone` | Regex parsing, postfix conversion, NFA/DFA       |
| 2     | `MuyagaBJ`   | Compiler backend targeting the MuyagaOS VM       |
| 3     | `MuyagaOS`   | CPU emulation, kernel, memory, filesystem        |
| 4     | `mini_db`    | Storage layout, page caching, indexing           |
| 5     | `cpp_server` | Concurrency and socket communication             |
| 6     | `tiny_dl`    | Tensor operations, gradients, computation graphs |

**MuyagaBJ** is the **current active project**, focused on designing and implementing a compiler for **MuyagaLang** —  
a small, C-like language that compiles directly to the 6502-inspired instruction set executed by **MuyagaOS**.

The compiler handles lexical analysis, parsing, type checking, and code generation into MuyagaBJ machine code.  
**MuyagaOS** serves as the runtime platform that will execute these compiled binaries.

---

## Repository Structure

```

C++-Systems/
├── MuyagaBJ/ # Compiler backend targeting MuyagaOS (active project)
├── MuyagaOS/ # Virtual machine and educational operating system
├── grep_clone/ # Regex engine (NFA/DFA)
├── mini_db/ # Minimal database engine
├── cpp_server/ # Network and concurrency prototype
├── tiny_dl/ # Lightweight deep learning engine
├── shared/ # Common utilities (logging, memory pools)
└── docs/ # Architecture notes and design documentation

```

---

## Build Instructions

All projects use **CMake ≥ 3.16** and a C++17-compatible compiler.

To build an individual project:

```bash
cd <project_name>
mkdir build && cd build
cmake ..
make -j$(nproc)
```

To rebuild all projects:

```bash
find . -type d -name build -exec rm -rf {} +
```

---

## Memory Management Policy

Each project has a **consistent memory management model**:

- **Manual management (raw pointers)**
  Used where understanding allocation/deallocation is part of the learning goal — e.g., regex engines, compiler ASTs, and OS kernels.

- **Smart pointers / RAII**
  Used where safety and lifecycle abstraction improve clarity — e.g., file systems, servers, and databases.

The two styles are **never mixed** within the same project.
This ensures conceptual clarity and pedagogical precision.

---

## Roadmap

| Phase | Focus Area    | Description                                 | Status          |
| ----- | ------------- | ------------------------------------------- | --------------- |
| 1     | MuyagaBJ Core | Lexer, parser, and AST design               | **In progress** |
| 2     | Codegen Layer | Generate MuyagaBJ instructions for MuyagaOS | Planned         |
| 3     | MuyagaOS Core | CPU, memory, and devices                    | In progress     |
| 4     | Kernel Layer  | Syscalls, processes, and file system        | Planned         |
| 5     | Integration   | Run MuyagaBJ-compiled programs in MuyagaOS  | Future          |
| 6     | BJFS Tools    | Disk formatter, file loader, and shell      | Future          |

---

## References

- **Ken Thompson**, _“Regular Expression Search Algorithm”_, CACM (1968)
- **Russ Cox**, _“Regular Expression Matching Can Be Simple and Fast”_, 2007
- **Niklaus Wirth**, _“Compiler Construction”_ (Addison-Wesley, 1996)
- **Fisher & LeBlanc**, _“Crafting a Compiler”_
- **Andrew Tanenbaum**, _“Modern Operating Systems”_
- **Patterson & Hennessy**, _“Computer Organization and Design”_
- **Alex Petrov**, _“Database Internals”_ (O’Reilly, 2019)
- **MIT 6.S081**, _“Operating System Engineering”_
- **CMU 15-213**, _“Introduction to Computer Systems”_
- **CMU 15-445/645**, _“Database Systems”_

---

## Author’s Note

This repository represents an **integrated systems laboratory** —
a unified environment for exploring how compilers, virtual machines, operating systems, and data systems connect.

Each subproject is both an **independent learning artifact** and a **building block** in a cohesive systems stack:

- **MuyagaBJ** compiles high-level code into MuyagaOS instructions.
- **MuyagaOS** executes those instructions in a 6502-inspired virtual machine.
- **BJFS**, **mini_db**, and **tiny_dl** extend the environment toward persistence and computation.

**MuyagaBJ** is under **active development**, serving as both a compiler and a bridge between language design and system execution.
It unites a prior **TypeScript-based MuyagaBJ** prototype
([github.com/HusseinBitambuka/muyagaBJ](https://github.com/HusseinBitambuka/muyagaBJ))
with a low-level C++ backend that directly emits executable bytecode for **MuyagaOS**.
