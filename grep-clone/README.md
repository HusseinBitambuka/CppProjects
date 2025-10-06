# Custom GREP Clone (C++)

This project implements a **from-scratch regular expression engine** in modern C++ that mimics the core behavior of UNIX `grep`.
It uses a **C-style procedural design** (raw pointers, manual memory management) to study the inner workings of regex engines at the automata level — without relying on the STL `<regex>` library or abstraction-heavy frameworks.

---

## Pipeline Overview

Each phase corresponds to one classical stage of regex evaluation:

1. **Parsing** — Converts infix regex to postfix (via Shunting Yard)
2. **Thompson’s Construction** — Builds an **NFA** (Non-Deterministic Finite Automaton)
3. **Subset Construction** — Converts the NFA into a **DFA**
4. **Matching Engine** — Simulates the DFA against file lines, printing matches with **highlighted substrings**

---

## Directory Structure

```
grep-clone/
├─ CMakeLists.txt
├─ include/
│   └─ regex/
│       ├─ parser.hpp      # Regex parser and shunting-yard logic
│       ├─ nfa.hpp         # Thompson construction (State, NFA)
│       ├─ dfa.hpp         # Subset construction (DFA builder)
│       ├─ matcher.hpp     # DFA simulation and matching interface
│       ├─ utils.hpp       # Shared utilities: Transition, extractSymbols, etc.
│       └─ ...
├─ src/
│   ├─ parser.cpp
│   ├─ nfa.cpp
│   ├─ dfa.cpp
│   ├─ matcher.cpp
│   ├─ utils.cpp
│   └─ main.cpp
└─ data/
    └─ sample.txt
```

---

## Build Instructions

### Requirements

- CMake ≥ 3.10
- C++17 or later (required for structured bindings and modern syntax)
- Tested on:

  - GCC 12.3 (Ubuntu)
  - Clang 16 (macOS)

### Build

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Run

```bash
./grep_clone "<pattern>" <file_path>
```

Example:

```bash
./grep_clone "ab*c" ./data/sample.txt
```

---

## Matching Behavior

- Reads a file line by line.
- For each line, the DFA is simulated across the entire text to find **partial matches**.
- Matching substrings are highlighted in color using ANSI escape codes for visual clarity.

Example output:

```
3: The pattern abbbc was found here → The pattern [1;33mabbbc[0m was found here
7: No match
9: Found [1;33mabc[0m again here
```

---

## Design Principles

This project follows a **manual memory model** inspired by C.

| Component | Allocations                  | Ownership    | Freed By    |
| --------- | ---------------------------- | ------------ | ----------- |
| `NFA`     | `State*` objects (via `new`) | `NFA.pool`   | `freeNFA()` |
| `DFA`     | `DFAState*` objects          | `DFA.states` | `freeDFA()` |
| Matcher   | Non-owning references        | —            | —           |

After conversion, `freeNFA(nfa)` is called to release NFA memory, leaving the DFA as the working automaton.

---

## Core Algorithms

### 1. Parsing (Shunting Yard)

Converts infix regex into postfix form for easy stack-based evaluation.

Example:

```
Input:  (ab|c)*dc
Output: ab.c|*d.c.
```

---

### 2. Thompson’s Construction (NFA)

Implements Thompson’s 1968 rules:

| Operator | Construction Logic                                                |
| -------- | ----------------------------------------------------------------- |
| `a`      | start →a→ accept                                                  |
| `AB`     | link A.accept →ε→ B.start                                         |
| `A\|B`   | new start →ε→ A,B; A.accept,B.accept →ε→ new accept               |
| `A*`     | new start →ε→ A.start,new accept; A.accept →ε→ A.start,new accept |

Each NFA keeps track of allocated `State*` objects in its internal `pool`.

---

### 3. Subset Construction (DFA)

Computes ε-closures and builds unique DFA states for each set of NFA states.

```cpp
std::set<State*> epsilonClosure(const std::set<State*>& states);
std::set<State*> move(const std::set<State*>& states, char symbol);
```

The resulting DFA is deterministic and suitable for fast matching.

---

### 4. Matching & File Scanning

- The matcher simulates the DFA per line of text.
- Partial matches are detected by running the DFA across all substrings.
- Matching regions are highlighted using ANSI colors (e.g., yellow or underline).

Example:

```cpp
bool simulateDFA(const DFA& dfa, const std::string& input);
void matchRegex(const DFA& compiledDFA, const std::string& line);
```

---

## Example Run

Given `sample.txt`:

```
abc
abbbc
zzz
cabca
```

Command:

```bash
./grep_clone "ab*c" data/sample.txt
```

Output:

```
1: [1;33mabc[0m
2: [1;33mabbbc[0m
4: c[1;33mabc[0ma
```

---

## Memory Management and Debugging

Because the system uses **manual allocation** for both NFAs and DFAs, memory control is explicit and part of the design learning goal.

### Freeing Memory

```cpp
void freeNFA(NFA &nfa);
void freeDFA(DFA &dfa);
```

Both functions recursively free all dynamically allocated `State*` and `DFAState*` objects and clear their internal containers.

Example:

```cpp
DFA dfa = compileDFA("ab*c");
simulateDFA(dfa, "abbbc");
freeDFA(dfa); // releases all allocated DFA states
```

You should call `freeNFA()` immediately after converting to DFA:

```cpp
NFA nfa = buildNFA(postfix);
DFA dfa = convertNFAtoDFA(nfa, alphabet);
freeNFA(nfa);
```

---

### State ID Tracking

All `State` objects are assigned an incremental integer ID at creation via a global counter:

```cpp
static int GLOBAL_STATE_ID = 0;
```

This allows deterministic debugging and easy visualization of transitions.

---

### Visualizing NFAs and DFAs

For debugging purposes, a helper function prints all transitions, including ε-transitions:

```cpp
void printNFA(const NFA &nfa);
```

Example output:

```
Printing the NFA output:
===========================================
S0 -> S1 (symbol: a)
S1 -> S2 (symbol: ε)
S2 -> S3 (symbol: b)
S3 -> S4 (symbol: ε)
```

A similar function for DFAs can be added to inspect deterministic transitions:

```cpp
void printDFA(const DFA &dfa);
```

This is useful for tracing subset construction correctness or visualizing the minimized transition graph.

---

## Future Work

- Add support for:

  - `+` (one or more)
  - `?` (optional)
  - Character classes (`[a-z]`)
  - Escaped operators (`\*`, `\|`, etc.)

- DFA minimization
- Add line number and byte offset tracking
- Multi-threaded file scanning
- Benchmark performance against `grep` and Python’s `re`

---

## References

- Ken Thompson, _Regular Expression Search Algorithm_, **Communications of the ACM**, 1968.
  [PDF](https://dl.acm.org/doi/pdf/10.1145/363347.363387)
- Russ Cox, _Regular Expression Matching Can Be Simple and Fast_, 2007.
  [Article](https://swtch.com/~rsc/regexp/regexp1.html)
- Aho, Sethi, Ullman. _Compilers: Principles, Techniques, and Tools_ (The Dragon Book).
