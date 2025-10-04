# Custom GREP Clone (C++)

This project implements a simplified **regular expression engine** in C++ using a **C-style procedural design**.
It reconstructs the core mechanics of tools like `grep` by manually building each stage of a regex engine:

1. **Parsing** using the Shunting Yard Algorithm
2. **Thompson’s Construction** for NFA generation
3. **Subset Construction** for DFA generation
4. **Pattern Matching** using DFA simulation

The purpose of this design is to explore how classical automata-based regex engines can be implemented in low-level C and C++ without heavy abstraction, and to contrast this with higher-level implementations (e.g., Python).

---

## Directory Structure

```
custom-grep/
├─ CMakeLists.txt
├─ include/
│   └─ regex/
│       ├─ parser.hpp      # Regex parser: adds concatenation, converts to postfix
│       ├─ nfa.hpp         # Thompson construction: NFA and State definitions
│       ├─ dfa.hpp         # Subset construction: builds DFA from NFA
│       └─ matcher.hpp     # Simulates NFA/DFA for matching
├─ src/
│   ├─ parser.cpp
│   ├─ nfa.cpp
│   ├─ dfa.cpp
│   ├─ matcher.cpp
│   └─ main.cpp
├─ tests/
│   ├─ test_parser.cpp
│   ├─ test_nfa.cpp
│   └─ test_matcher.cpp
└─ data/
    └─ sample.txt
```

---

## Build Instructions

### Requirements

- CMake ≥ 3.10
- C++14-compatible compiler (GCC ≥ 9, Clang ≥ 10, or MSVC ≥ 2019)

### Steps

```bash
mkdir build && cd build
cmake ..
make
```

The resulting executable `grep_clone` will be created inside the `build/` directory.

Run it with:

```bash
./grep_clone
```

---

## Design Overview

This project uses an explicitly **C-style architecture**—simple structs, raw pointers, and manual data control—to highlight how regex engines can be built close to the metal.

### 1. Parser

The parser performs two steps:

- Inserts explicit concatenation operators (`.`) where implied
- Converts infix regex to postfix (Reverse Polish Notation) using the **Shunting Yard Algorithm**

Example:

```
Input:  (ab|c)*dc
Output: ab.c|*d.c.
```

Files: `parser.hpp`, `parser.cpp`

---

### 2. NFA Construction (Thompson’s Construction)

Converts the postfix expression into an NFA by applying Thompson’s rules:

| Operator | Construction                                                        |
| -------- | ------------------------------------------------------------------- |
| `a`      | start → `a` → accept                                                |
| `AB`     | connect accept(A) →ε→ start(B)                                      |
| `A\|B`   | new start →ε→ A and B; both accept →ε→ new accept                   |
| `A*`     | new start →ε→ A and new accept; A.accept →ε→ A.start and new accept |

NFA representation:

```cpp
struct Transition {
    char symbol;
    State* target;
};

struct State {
    int id;
    std::vector<Transition> transitions;
    std::vector<State*> epsilonTransitions;
};

struct NFA {
    State* start;
    State* accept;
};
```

Files: `nfa.hpp`, `nfa.cpp`

---

### 3. DFA Construction (Subset Construction)

Builds a deterministic automaton by computing the ε-closure of NFA states and creating DFA states for each unique closure.
This eliminates non-determinism and allows linear-time matching against input strings.

Files: `dfa.hpp`, `dfa.cpp`

---

### 4. Matching Phase

Simulates the DFA on an input string:

- Begin at the DFA’s start state
- Follow transitions for each input character
- Accept if the final state is an accepting state

Files: `matcher.hpp`, `matcher.cpp`

---

## Example Run

### Input

```
(ab|c)*dc
```

### Steps

1. Add concatenations → `(a.b|c).*.d.c`
2. Convert to postfix → `ab.c|*d.c.`
3. Build NFA (via Thompson)
4. Convert to DFA (subset construction)
5. Match input strings

### Test Inputs

| Input   | Result   |
| ------- | -------- |
| `abdc`  | Match    |
| `ccdc`  | Match    |
| `cabc`  | No match |
| `abcdc` | Match    |

---

## Current Development Focus

- Implementing the NFA construction logic (`nfa.cpp`)
- Completing Thompson’s operators: concatenation, union, and Kleene star
- Using raw pointers and manual lifetime management to better understand memory handling compared to Python implementations

---

## Planned Extensions

- Add support for:

  - `+` (one or more)
  - `?` (zero or one)
  - Character classes (`[a-z]`)
  - Escaped operators (`\|`, `\*`, etc.)

- DFA minimization and table-driven transitions
- Streaming file input to implement real `grep`-like search behavior

---

## References

- Ken Thompson, _Regular Expression Search Algorithm_, Communications of the ACM, 1968. [PDF link](https://dl.acm.org/doi/pdf/10.1145/363347.363387)
- Russ Cox, _Regular Expression Matching Can Be Simple and Fast_, 2007. [Article link](https://swtch.com/~rsc/regexp/regexp1.html)
- Aho, Sethi, Ullman. _Compilers: Principles, Techniques, and Tools_ (“The Dragon Book”).
