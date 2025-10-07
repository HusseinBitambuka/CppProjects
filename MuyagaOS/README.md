# MuyagaOS

**MuyagaOS** is an educational operating system and virtual machine written entirely in modern **C++**, inspired by classic 8-bit architectures like the **MOS 6502**.  
It’s designed as a sandbox for exploring **systems programming**, **memory management**, and **file systems** at a low level — combining a simple virtual CPU, kernel, and disk-backed filesystem.

The goal is to build a **fully bootable software system** that runs user programs, simulates hardware devices, and provides a foundation for experimentation with compilers and runtime environments later on.

---

## Project Overview

**MuyagaOS** consists of three main components:

| Component                      | Description                                                                                                                                              |
| ------------------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **VM (Virtual Machine)**       | Implements a 6502-inspired CPU, memory bus, and I/O devices. Executes machine instructions, manages RAM, and performs I/O through memory-mapped devices. |
| **OS (Kernel + System Calls)** | Provides a simple kernel interface with basic syscalls (`print`, `read`, `exit`, etc.), memory allocation routines, and device abstractions.             |
| **BJFS (Muyaga File System)**  | A minimal block-based file system that supports formatted disk images, directory listings, and file loading into memory.                                 |

This design makes MuyagaOS both **educational and extensible** — ideal for experimenting with:

- Custom kernels and schedulers
- User-mode applications and system calls
- Memory paging and heap management
- Simple shell interpreters and I/O devices
- File systems and virtual disks

---

## Architecture Overview

```

+----------------------------------------------------------+
| MuyagaOS |
+----------------------------------------------------------+
| User Programs / Shell |
+----------------------------------------------------------+
| System Calls |
+----------------------------------------------------------+
| Kernel (Scheduler + Memory + FS) |
+----------------------------------------------------------+
| BJFS (Disk I/O, Directory, File Blocks) |
+----------------------------------------------------------+
| Virtual Machine (CPU, Memory, Devices, Bus) |
+----------------------------------------------------------+
| Host Environment |
+----------------------------------------------------------+

```

- **CPU**: Emulates a reduced 6502 instruction set (LDA, STA, ADC, JMP, etc.)
- **Memory**: 64KB RAM with stack and memory-mapped I/O regions
- **Devices**: Virtual console and disk device interfaces
- **BJFS**: Simple block-based file system with bootable image support
- **Kernel**: Boots from disk, mounts BJFS, and runs init processes

---

## Directory Structure

```

MuyagaOS/
├── vm/ # Virtual machine layer
│ ├── include/ # CPU, memory, and device headers
│ ├── src/ # Implementation of CPU, memory, loader
│ ├── devices/ # Virtual console and disk I/O
│ └── tests/ # Unit tests for VM modules
│
├── os/ # Operating system layer
│ ├── include/ # Kernel, syscalls, FS headers
│ ├── src/ # Kernel and syscall implementation
│ ├── fs/ # BJFS filesystem implementation
│ └── tests/ # OS and FS tests
│
├── disk/ # Virtual disk images (.img)
├── tools/ # Host utilities (bjfs-ls, bjfs-cp, etc.)
├── docs/ # Architecture, syscall table, file system spec
└── scripts/ # Build, run, and setup scripts

```

---

## Build and Run

### Requirements

- CMake ≥ 3.16
- C++17-compatible compiler (GCC ≥ 9, Clang ≥ 10)

### Build

```bash
chmod +x scripts/build_all.sh
./scripts/build_all.sh
```

### Run VM

```bash
./scripts/run_vm.sh
```

### Create a new disk image

```bash
./scripts/make_disk.sh
```

This creates a blank `disk/disk.img` file for BJFS.

---

## Components Overview

### Virtual Machine (VM)

Implements:

- 6502-style CPU registers (`A`, `X`, `Y`, `SP`, `PC`, `STATUS`)
- 64KB memory model (`0x0000–0xFFFF`)
- Memory-mapped I/O regions for console and disk
- Instruction decoder and stepping loop

### Operating System

Provides:

- Kernel initialization and boot sequence
- Syscall interface (print, exit, read/write)
- Memory allocation (`kmalloc`, `kfree`)
- Device abstraction for disk and console

### BJFS File System

A minimal block-based file system for `disk.img`, including:

- Superblock and inode layout
- Basic directory structure
- File read/write operations
- Simple tools to list and copy files (`bjfs-ls`, `bjfs-cp`)

---

## Testing and Debugging

Unit tests are planned under:

```
vm/tests/   # CPU and memory tests
os/tests/   # Filesystem and syscall tests
```

To run tests manually:

```bash
cd build && ctest
```

---

## Roadmap

| Phase | Goal                           | Status      |
| ----- | ------------------------------ | ----------- |
| 1     | VM Core: CPU, Memory, Devices  | In Progress |
| 2     | Kernel Boot + Basic Syscalls   | Planned     |
| 3     | BJFS File System (Disk I/O)    | Planned     |
| 4     | Shell and Process Loader       | Planned     |
| 5     | Multitasking and Memory Paging | Future      |
| 6     | Networking Layer / Drivers     | Future      |

---

## Memory Map (Draft)

| Region          | Address Range     | Purpose                |
| --------------- | ----------------- | ---------------------- |
| `0x0000–0x00FF` | Zero Page         | Fast access registers  |
| `0x0100–0x01FF` | Stack             | System stack           |
| `0x0200–0x7FFF` | Program / Heap    | Kernel and user memory |
| `0x8000–0xFEFF` | Reserved          | File buffers / drivers |
| `0xFF00–0xFF0F` | Console I/O       | Memory-mapped output   |
| `0xFF10–0xFF1F` | Disk I/O          | Disk controller        |
| `0xFFFE–0xFFFF` | Interrupt vectors | BRK / SYS entry        |

---

## Design Philosophy

MuyagaOS aims to teach **systems internals by construction** — writing everything from scratch:

- Manual memory management in C++
- Virtual device emulation and mapping
- File system design from bytes to blocks
- OS boot process and syscall design
- Incremental layering toward a full environment

Memory management strategy:

- Each project (VM, OS, FS) uses **one consistent approach**
- Some use **manual memory control (raw pointers)**
- Others will use **smart pointers or memory pools**
- The two approaches are never mixed within the same module

---

## References

- **Ken Thompson**, _“Regular Expression Search Algorithm”_, CACM (1968)
- **Russ Cox**, _“Regular Expression Matching Can Be Simple and Fast”_, 2007
- **Niklaus Wirth**, _“Compiler Construction”_ (Addison-Wesley, 1996)
- **Richard C. Holt**, _“Operating Systems: Principles and Practice”_
- **Andrew Tanenbaum**, _“Modern Operating Systems”_
- **Patterson & Hennessy**, _“Computer Organization and Design”_
- **Fisher & LeBlanc**, _“Crafting a Compiler”_
- **CMU Database Systems Course (15-445/645)**
- **Alex Petrov**, _“Database Internals”_ (O’Reilly, 2019)

---

## Author’s Note

MuyagaOS is an evolving educational environment — part VM, part OS, and part creative experiment in systems design.
Each component (CPU, FS, Kernel) can be run, tested, and extended independently.

```

---

Would you like me to now generate a companion `docs/architecture.md` file that visualizes and explains how the **CPU**, **memory**, **BJFS**, and **kernel** communicate internally (with ASCII diagrams and initialization flow)?
```
