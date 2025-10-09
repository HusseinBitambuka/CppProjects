# MuyagaLang Compiler (MuyagaBJ)

**MuyagaLang** is a small, statically typed, C-like programming language that compiles directly to **MuyagaBJ machine instructions** — a 6502-inspired instruction set executed inside **MuyagaOS**.

The compiler is written entirely in **modern C++17** and serves as a learning environment for compiler construction, systems programming, and low-level code generation.

---

## Background

The project builds on earlier work completed during college:  
a **browser-based implementation of MuyagaBJ**, written in **TypeScript**, which provided a virtual CPU and instruction visualizer.  
That project can be found here:

**Repository:** [HusseinBitambuka/muyagaBJ](https://github.com/HusseinBitambuka/muyagaBJ/tree/main)

The C++ version extends that foundation, focusing on code generation, instruction emission, and integration with **MuyagaOS**.

---

## Project Overview

| Component              | Description                                                               |
| ---------------------- | ------------------------------------------------------------------------- |
| **Lexer**              | Converts MuyagaLang source code into tokens                               |
| **Parser**             | Builds an Abstract Syntax Tree (AST) following the grammar                |
| **Semantic Pass**      | Validates types, scope, and declarations                                  |
| **Code Generator**     | Emits MuyagaBJ machine instructions                                       |
| **Runtime (MuyagaOS)** | Provides system calls for I/O, memory allocation, and program termination |

---

## Language Summary

**MuyagaLang** includes:

| Feature         | Example                                        |
| --------------- | ---------------------------------------------- |
| Primitive types | `int`, `char`, `string`                        |
| Variables       | `int a = 3;`                                   |
| Arithmetic      | `a = a + 1;`                                   |
| Functions       | `func int add(int x, int y) { return x + y; }` |
| Conditionals    | `if (a < b) { print(a); } else { print(b); }`  |
| Loops           | `while (i < 10) { i = i + 1; }`                |
| Heap memory     | `string s = alloc(32); free(s);`               |
| I/O             | `print("Hello!"); print(x);`                   |

---

## Directory Structure

```

MuyagaBJ/
├── include/
│ ├── token.hpp
│ ├── lexer.hpp
│ ├── parser.hpp
│ ├── ast.hpp
│ ├── codegen.hpp
│ ├── symbol_table.hpp
│ └── utils.hpp
│
├── src/
│ ├── lexer.cpp
│ ├── parser.cpp
│ ├── codegen.cpp
│ ├── symbol_table.cpp
│ └── main.cpp
│
├── grammar.mlg
│
├── tests/
│ ├── test_lexer.cpp
│ ├── test_parser.cpp
│ ├── test_codegen.cpp
│
└── examples/
├── factorial.mlg
└── hello.mlg

```

---

## Build and Run

### Requirements

- CMake ≥ 3.16
- C++17-compatible compiler (GCC ≥ 9, Clang ≥ 10)

### Build

```bash
mkdir -p build
cmake -S . -B build
cmake --build build -j
```

### Run the Compiler

```bash
./build/muyagac examples/hello.mlg -o hello.bin
```

### Example Input

```c
func void main() {
    int a = 5;
    while (a > 0) {
        print(a);
        a = a - 1;
    }
}
```

### Example Output (MuyagaBJ Instructions)

```
A9 05      ; LDA #$05
8D 10 00   ; STA $0010
loop_start:
AD 10 00   ; LDA $0010
C9 00      ; CMP #$00
F0 10      ; BEQ loop_end
A2 01      ; LDX #$01
AC 10 00   ; LDY $0010
FF         ; SYS print integer
CE 10 00   ; DEC $0010
4C 00 00   ; JMP loop_start
loop_end:
00         ; BRK
```

---

## System Calls in MuyagaOS

| Syscall     | X Register | Description                                           |
| ----------- | ---------- | ----------------------------------------------------- |
| `print_int` | `0x01`     | Print integer in Y                                    |
| `print_str` | `0x02`     | Print null-terminated string                          |
| `alloc`     | `0x03`     | Allocate N bytes on heap (size in Y, returns pointer) |
| `free`      | `0x04`     | Free string buffer (pointer in Y)                     |

---

## Development Phases

| Phase | Goal                          | Status      |
| ----- | ----------------------------- | ----------- |
| 1     | Lexer and Tokenizer           | In progress |
| 2     | Parser and AST                | Planned     |
| 3     | Type Checker and Symbol Table | Planned     |
| 4     | Code Generator (machine code) | Planned     |
| 5     | Integration with MuyagaOS VM  | Future      |

---

## References

- “Crafting Compilers” — Charles N. Fischer, Ron K. Cytron, and Richard J. LeBlanc
- “Writing a C Compiler” — Nora Sandler
- “Let's Build a Compiler” — Jack Crenshaw
- 6502 Instruction Set Reference — MOS Technology (1975)

---

## Author’s Note

MuyagaLang is part of a broader educational system that includes:

- **MuyagaBJ** — compiler backend
- **MuyagaOS** — educational operating system and runtime
- **MuyagaVM** — virtual machine executing MuyagaBJ binaries
- **BJFS** — block-based file system
