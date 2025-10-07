# MuyagaBJ – 6502 Instruction Set Reference (Extended Subset)

> This document defines the **instruction subset** used by the **MuyagaBJ compiler backend**, inspired by the original **MOS 6502 architecture** but tailored for educational compilation and runtime simulation.
>
> Opcodes are shown in hexadecimal and follow the standard 6502 format.
> For simplicity, only **immediate (`#`), absolute (`$`),** and **implied** addressing modes are included.

---

## 1. Load and Store Operations

| Mnemonic | Opcode | Addressing | Description                          | Example     | Encoding   |
| -------- | ------ | ---------- | ------------------------------------ | ----------- | ---------- |
| `LDA`    | `A9`   | Immediate  | Load the accumulator with a constant | `LDA #$07`  | `A9 07`    |
| `LDA`    | `AD`   | Absolute   | Load the accumulator from memory     | `LDA $0010` | `AD 10 00` |
| `STA`    | `8D`   | Absolute   | Store the accumulator into memory    | `STA $0010` | `8D 10 00` |
| `LDX`    | `A2`   | Immediate  | Load X register with a constant      | `LDX #$01`  | `A2 01`    |
| `LDX`    | `AE`   | Absolute   | Load X register from memory          | `LDX $0010` | `AE 10 00` |
| `LDY`    | `A0`   | Immediate  | Load Y register with a constant      | `LDY #$04`  | `A0 04`    |
| `LDY`    | `AC`   | Absolute   | Load Y register from memory          | `LDY $0010` | `AC 10 00` |
| `STX`    | `8E`   | Absolute   | Store X register into memory         | `STX $0010` | `8E 10 00` |
| `STY`    | `8C`   | Absolute   | Store Y register into memory         | `STY $0010` | `8C 10 00` |

---

## 2. Arithmetic and Logic

| Mnemonic | Opcode | Description                                    | Example     | Encoding   |
| -------- | ------ | ---------------------------------------------- | ----------- | ---------- |
| `ADC`    | `6D`   | Add memory to accumulator (with carry)         | `ADC $0010` | `6D 10 00` |
| `SBC`    | `ED`   | Subtract memory from accumulator (with borrow) | `SBC $0010` | `ED 10 00` |
| `INC`    | `EE`   | Increment memory value by one                  | `INC $0021` | `EE 21 00` |
| `DEC`    | `CE`   | Decrement memory value by one                  | `DEC $0021` | `CE 21 00` |
| `CMP`    | `CD`   | Compare accumulator with memory                | `CMP $0010` | `CD 10 00` |
| `CPX`    | `EC`   | Compare X register with memory                 | `CPX $0010` | `EC 10 00` |
| `CPY`    | `CC`   | Compare Y register with memory                 | `CPY $0010` | `CC 10 00` |
| `AND`    | `2D`   | Logical AND accumulator with memory            | `AND $0010` | `2D 10 00` |
| `ORA`    | `0D`   | Logical OR accumulator with memory             | `ORA $0010` | `0D 10 00` |
| `EOR`    | `4D`   | Logical XOR accumulator with memory            | `EOR $0010` | `4D 10 00` |

---

## 3. Branching and Control Flow

| Mnemonic | Opcode | Condition     | Description                              | Example     | Encoding   |
| -------- | ------ | ------------- | ---------------------------------------- | ----------- | ---------- |
| `BNE`    | `D0`   | Z=0           | Branch if not equal (zero flag clear)    | `BNE $EF`   | `D0 EF`    |
| `BEQ`    | `F0`   | Z=1           | Branch if equal (zero flag set)          | `BEQ $F2`   | `F0 F2`    |
| `BCC`    | `90`   | C=0           | Branch if carry clear                    | `BCC $F3`   | `90 F3`    |
| `BCS`    | `B0`   | C=1           | Branch if carry set                      | `BCS $F4`   | `B0 F4`    |
| `BMI`    | `30`   | N=1           | Branch if negative                       | `BMI $F5`   | `30 F5`    |
| `BPL`    | `10`   | N=0           | Branch if positive                       | `BPL $F6`   | `10 F6`    |
| `JMP`    | `4C`   | Unconditional | Jump to absolute address                 | `JMP $00F0` | `4C F0 00` |
| `JSR`    | `20`   | Subroutine    | Jump to subroutine (push return address) | `JSR $00F0` | `20 F0 00` |
| `RTS`    | `60`   | Return        | Return from subroutine                   | `RTS`       | `60`       |

---

## 4. Stack Operations

| Mnemonic | Opcode | Description                 | Example | Encoding |
| -------- | ------ | --------------------------- | ------- | -------- |
| `PHA`    | `48`   | Push accumulator onto stack | `PHA`   | `48`     |
| `PLA`    | `68`   | Pull accumulator from stack | `PLA`   | `68`     |
| `PHP`    | `08`   | Push processor status       | `PHP`   | `08`     |
| `PLP`    | `28`   | Pull processor status       | `PLP`   | `28`     |
| `TXS`    | `9A`   | Transfer X to stack pointer | `TXS`   | `9A`     |
| `TSX`    | `BA`   | Transfer stack pointer to X | `TSX`   | `BA`     |

---

## 5. Flag and Processor Control

| Mnemonic | Opcode | Description                            | Example | Encoding |
| -------- | ------ | -------------------------------------- | ------- | -------- |
| `CLC`    | `18`   | Clear carry flag                       | `CLC`   | `18`     |
| `SEC`    | `38`   | Set carry flag                         | `SEC`   | `38`     |
| `CLI`    | `58`   | Clear interrupt disable                | `CLI`   | `58`     |
| `SEI`    | `78`   | Set interrupt disable                  | `SEI`   | `78`     |
| `CLV`    | `B8`   | Clear overflow flag                    | `CLV`   | `B8`     |
| `CLD`    | `D8`   | Clear decimal mode                     | `CLD`   | `D8`     |
| `SED`    | `F8`   | Set decimal mode                       | `SED`   | `F8`     |
| `NOP`    | `EA`   | No operation                           | `NOP`   | `EA`     |
| `BRK`    | `00`   | Software interrupt (break/system call) | `BRK`   | `00`     |

---

## 6. System and Extended Instructions

These are **MuyagaBJ-specific extensions** used to simulate system calls, I/O, and runtime services in the VM or 6502 emulator.

| Mnemonic | Opcode | Description                                                 | Example | Notes                      |
| -------- | ------ | ----------------------------------------------------------- | ------- | -------------------------- |
| `SYS`    | `FF`   | Perform a system call based on X register                   | `SYS`   | Custom instruction for I/O |
|          |        | **X = 0x01** → print integer in Y register                  |         |                            |
|          |        | **X = 0x02** → print null-terminated string at address in Y |         |                            |
|          |        | **X = 0x03** → allocate string buffer on heap               |         |                            |
|          |        | **X = 0x04** → free string buffer                           |         |                            |

---

## 7. Example Instruction Sequence

Example of compiling a simple print statement:

```asm
; string s = "Hi"
A9 00       LDA #$00         ; clear accumulator
A2 02       LDX #$02         ; SYS print-string
A0 20       LDY #$20         ; address of string in memory
FF          SYS              ; system call → print string
00          BRK              ; program end
```

---

## 8. Supported Addressing Modes

| Mode          | Syntax  | Description                            |
| ------------- | ------- | -------------------------------------- |
| **Immediate** | `#$07`  | Constant literal                       |
| **Absolute**  | `$0010` | Full memory address                    |
| **Implied**   | —       | No operand (uses accumulator or flags) |

---

## 9. Implementation Notes

- All numeric literals are **hexadecimal** unless otherwise specified.
- The system call (`SYS`) instruction is **not part of the real 6502 ISA** — it’s an intentional extension for controlled I/O during emulation.
- The compiler backend may generate instruction macros (e.g., `MOV` → `LDA`/`STA` pairs).
- Emulation layer (or codegen) will implement a **memory-mapped I/O region** for strings and integers.

---
