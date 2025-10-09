# MuyagaLang Grammar

This document defines the syntax of **MuyagaLang**, a small, statically typed C-like language that compiles to **MuyagaBJ machine instructions**. Execution begins in the function named **`main`**. All variables are local to functions (no globals).

---

## Lexical Elements

- **Keywords:** **`func`**, **`return`**, **`while`**, **`if`**, **`else`**, **`print`**, **`int`**, **`char`**, **`string`**, **`alloc`**, **`free`**
- **Symbols:** **`=`**, **`+`**, **`-`**, **`*`**, **`/`**, **`(`**, **`)`**, **`{`**, **`}`**, **`;`**, **`,`**, **`<`**, **`>`**, **`<=`**, **`>=`**, **`==`**, **`!=`**, **`&`**
- **Identifiers:** `IDENT` → matches `[A-Za-z_][A-Za-z0-9_]*`
- **Literals:**

  - `NUMBER` → decimal only: `[0-9]+`
  - `CHAR` → a single printable char: `'A'` (escape sequences optional/future)
  - `STRING` → `"..."` (null-terminated at runtime; escapes optional/future)

- **Whitespace/Comments:** ignored. Line comments start with `//` and run to end of line.

---

## Program Structure (functions only)

- **Program** ::= `{` **FuncDecl** `}`
- **FuncDecl** ::= **`func`** **Type** **IDENT** **`(`** [ **ParamList** ] **`)`** **Block**
- **ParamList** ::= **Param** { **`,`** **Param** }
- **Param** ::= **Type** **IDENT**

> The program is a sequence of function definitions. Execution starts by calling **`main`** (conventionally `func void main()` or `func int main()`).

---

## Blocks and Statements (function bodies contain statements)

- **Block** ::= **`{`** { **Statement** } **`}`**

- **Statement** ::=

  - **VarDecl**
  - **Assignment**
  - **ReturnStmt**
  - **WhileStmt**
  - **IfStmt**
  - **PrintStmt**
  - **AllocStmt**
  - **FreeStmt**
  - **ExprStmt**
  - **Block** _(nested scopes allowed)_

- **VarDecl** ::= **Type** **IDENT** **`=`** **Expression** **`;`**

- **Assignment** ::= **IDENT** **`=`** **Expression** **`;`**

- **ReturnStmt** ::= **`return`** [ **Expression** ] **`;`**

- **WhileStmt** ::= **`while`** **`(`** **Expression** **`)`** **Block**

- **IfStmt** ::= **`if`** **`(`** **Expression** **`)`** **Block** [ **`else`** **Block** ]

- **PrintStmt** ::= **`print`** **`(`** **Expression** **`)`** **`;`**

- **AllocStmt** ::= **IDENT** **`=`** **`alloc`** **`(`** **Expression** **`)`** **`;`**

- **FreeStmt** ::= **`free`** **`(`** **IDENT** **`)`** **`;`**

- **ExprStmt** ::= **Expression** **`;`**

---

## Expressions (precedence and associativity)

From lowest to highest precedence:

- **Expression** ::= **EqualityExpr**
- **EqualityExpr** ::= **RelationalExpr** { ( **`==`** | **`!=`** ) **RelationalExpr** }
- **RelationalExpr** ::= **AdditiveExpr** { ( **`<`** | **`<=`** | **`>`** | **`>=`** ) **AdditiveExpr** }
- **AdditiveExpr** ::= **MultiplicativeExpr** { ( **`+`** | **`-`** ) **MultiplicativeExpr** }
- **MultiplicativeExpr** ::= **UnaryExpr** { ( **`*`** | **`/`** ) **UnaryExpr** }
- **UnaryExpr** ::= [ **`-`** | **`&`** ] **PrimaryExpr**
- **PrimaryExpr** ::= **NUMBER** | **CHAR** | **STRING** | **IDENT** | **FuncCall** | **`(`** **Expression** **`)`**

**Function call:**

- **FuncCall** ::= **IDENT** **`(`** [ **ArgList** ] **`)`**
- **ArgList** ::= **Expression** { **`,`** **Expression** }

---

## Types

- **Type** ::= **`int`** | **`char`** | **`string`**

Notes:

- **`string`** values are pointers to heap-allocated, null-terminated byte arrays.
- Use **`alloc(n)`** to allocate and **`free(p)`** to deallocate.

---

## Example

```c
func int add(int a, int b) {
    int r = a + b;
    return r;
}

func void main() {
    int x = 10;
    int y = 20;
    int z = add(x, y);
    print(z);
}
```
