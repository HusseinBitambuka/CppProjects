# MuyagaLang Grammar Specification

This document defines the syntax of **MuyagaLang**, a small statically typed C-like language that compiles to **MuyagaBJ machine instructions**.  
Execution begins at the **`main`** function, and all variables are local to functions.

---

## Lexical Structure

```ebnf
KEYWORDS =
    **"func"** | **"return"** | **"while"** | **"if"** | **"else"** | **"print"** |
    **"int"** | **"char"** | **"string"** | **"alloc"** | **"free"** ;

SYMBOLS =
    **"="** | **"+"** | **"-"** | **"*"** | **"/"** |
    **"("** | **")"** | **"{"** | **"}"** |
    **";"** | **","** |
    **"<"** | **">"** | **"<="** | **">="** | **"=="** | **"!="** | **"&"** ;

IDENTIFIER  = [a-zA-Z_], { [a-zA-Z0-9_] } ;
NUMBER      = [0-9], { [0-9] } ;
CHAR        = "'", [ -~ ], "'" ;
STRING      = '"', { [^"\\] | "\\" , any }, '"' ;

WHITESPACE  = { " " | "\t" | "\r" | "\n" } ;
COMMENT     = "//" , { any }, "\n" ;
```

````

Whitespace and comments are ignored by the parser.

---

## Program Structure

```ebnf
Program        = { **FuncDecl** } ;

FuncDecl       = **"func"** , **Type** , **IDENTIFIER** ,
                  **"("** , [ **ParamList** ] , **")"** , **Block** ;

ParamList      = **Param** , { **","** , **Param** } ;
Param          = **Type** , **IDENTIFIER** ;
```

Each program consists of one or more **function definitions**.
Execution starts in the function named **`main`**.

---

## Statements

```ebnf
Statement      = **VarDecl**
               | **Assignment**
               | **PrintStmt**
               | **ReturnStmt**
               | **WhileStmt**
               | **IfStmt**
               | **AllocStmt**
               | **FreeStmt**
               | **Block**
               | **ExprStmt** ;

VarDecl        = **Type** , **IDENTIFIER** , **"="** , **Expression** , **";"** ;
Assignment     = **IDENTIFIER** , **"="** , **Expression** , **";"** ;
ReturnStmt     = **"return"** , [ **Expression** ] , **";"** ;
PrintStmt      = **"print"** , **"("** , **Expression** , **")"** , **";"** ;
WhileStmt      = **"while"** , **"("** , **Expression** , **")"** , **Block** ;
IfStmt         = **"if"** , **"("** , **Expression** , **")"** , **Block** ,
                 [ **"else"** , **Block** ] ;
AllocStmt      = **IDENTIFIER** , **"="** , **"alloc"** , **"("** , **Expression** , **")"** , **";"** ;
FreeStmt       = **"free"** , **"("** , **IDENTIFIER** , **")"** , **";"** ;
ExprStmt       = **Expression** , **";"** ;
Block          = **"{"** , { **Statement** } , **"}"** ;
```

---

## Expressions

```ebnf
Expression     = **EqualityExpr** ;

EqualityExpr   = **RelationalExpr** ,
                 { ( **"=="** | **"!="** ) , **RelationalExpr** } ;

RelationalExpr = **AdditiveExpr** ,
                 { ( **"<"** | **"<="** | **">"** | **">="** ) , **AdditiveExpr** } ;

AdditiveExpr   = **MultiplicativeExpr** ,
                 { ( **"+"** | **"-"** ) , **MultiplicativeExpr** } ;

MultiplicativeExpr = **UnaryExpr** ,
                     { ( **"*"** | **"/"** ) , **UnaryExpr** } ;

UnaryExpr      = [ **"-"** | **"&"** ] , **PrimaryExpr** ;

PrimaryExpr    = **NUMBER**
               | **CHAR**
               | **STRING**
               | **IDENTIFIER**
               | **FuncCall**
               | **"("** , **Expression** , **")"** ;

FuncCall       = **IDENTIFIER** , **"("** , [ **ArgList** ] , **")"** ;
ArgList        = **Expression** , { **","** , **Expression** } ;
```

---

## Types

```ebnf
Type           = **"int"** | **"char"** | **"string"** ;
```

---

## Example Program

```c
func int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

func void main() {
    int x = 5;
    int result = factorial(x);
    print(result);
}
```

---

## Notes

- Only **functions** appear at the top level.
- The compiler entry point is **`main()`**, which must have type `void` and no parameters.
- All variables are **function-local** (stack-allocated).
- The built-in functions **`alloc(size)`** and **`free(ptr)`** provide heap memory management for strings or buffers.

---

**End of MuyagaLang Grammar**

````
