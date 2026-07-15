# CalcYouLater — an RPN Calculator & Mini Language

A command-line **Reverse Polish Notation (RPN) calculator** written in C++ that
grows into a small stack-based programming language. Beyond arithmetic, it
supports booleans, comparisons, and **rstrings** — quoted blocks of code that
can be stored on the stack and later executed with `exec`, branched on with
`if`, or loaded from disk with `file`. This makes the calculator *self-hosting*:
programs are just data pushed onto the same stack the calculator computes with.

The calculator is implemented on top of a hand-written stack data
structure, which was designed and unit-tested first.

## Tech stack

- **Language:** C++ (C++11-era standard library)
- **Core data structure:** custom `DatumStack` backed by `std::list<Datum>`
- **Value type:** `Datum`, a tagged union of `int` / `bool` / `rstring`
- **Build:** `make` (Makefile) / `g++` / `clang++`
- **Tests:** assert-based unit tests for the stack (`unit_tests.h`)

## Build & run

The project ships with a Makefile (which uses `clang++`):

```bash
make CalcYouLater
./CalcYouLater
```

Or compile directly with any C++ compiler:

```bash
g++ -std=c++11 -Wall -Wextra -o CalcYouLater \
    RPNCalc.cpp DatumStack.cpp Datum.cpp main.cpp
./CalcYouLater
```

The calculator reads whitespace-separated tokens from standard input until it
receives `quit`. You can type interactively or pipe a program in:

```bash
echo "3 4 + print quit" | ./CalcYouLater
```

## Usage examples

Values are pushed onto a stack; operators consume the top values and push the
result. `print` displays the top of the stack.

```
> 3 4 + print
7

> 17 5 mod print
2

> 5 3 > print
#t
```

Booleans are `#t` / `#f`, and `not` negates the top boolean.

**rstrings** are code quoted in `{ ... }`. They sit on the stack untouched until
`exec` runs them:

```
> { 10 2 * } exec print
20
```

`if` pops a boolean and two rstrings (the true-case and false-case blocks) and
executes the branch matching the condition:

```
> #t { 1 } { 0 } if print
1
```

Other stack operators: `dup`, `drop`, `swap`, `clear`. `file` pops an rstring
naming a file and runs its contents as a program, so larger routines can live in
their own `.cyl` files and be loaded at runtime.

### Command reference

| Category    | Commands |
|-------------|----------|
| Arithmetic  | `+` `-` `*` `/` `mod` |
| Comparison  | `<` `>` `<=` `>=` `==` |
| Booleans    | `#t` `#f` `not` |
| Stack       | `dup` `drop` `swap` `clear` `print` |
| Language    | `{ ... }` (rstring) · `exec` · `if` · `file` |
| Control     | `quit` |

## How it works

**`Datum` — a tagged value.** Every value on the stack is a `Datum`, which holds
exactly one of an `int`, a `bool`, or an `rstring`, tracked by an internal type
tag. Type queries (`isInt`, `isBool`, `isRString`) let the interpreter branch on
what it's looking at, and the accessors (`getInt`, etc.) throw
`std::runtime_error` on a type mismatch so a value can never be read as the wrong
type by accident.

**`DatumStack` — the calculator's memory.** A thin stack built on `std::list`,
exposing `push`, `pop`, `top`, `size`, `isEmpty`, and `clear`. `top`/`pop` throw
on an empty stack. RPN evaluation is a natural fit: operands are pushed as they
appear, and each operator pops its arguments off the top — every push and pop is
O(1).

**`RPNCalc` — the interpreter.** A read-eval loop (`run_helper`) tokenizes input
and dispatches each token: literals get pushed, operators pop and compute, and
language constructs manipulate the stack. Two details make it more than a
calculator:

- **rstring quoting.** When the lexer sees `{`, it scans forward keeping a brace
  counter so that *nested* `{ ... }` blocks are captured whole, and pushes the
  entire block as a single rstring value rather than evaluating it.
- **Self-hosting execution.** `exec` strips a rstring's outer braces and feeds
  its body back through the *same* evaluation loop via a `std::stringstream`.
  `if` builds on this by choosing one of two rstrings to `exec`, and `file`
  reads a program from disk into the same loop. Errors (empty stack, type
  mismatches) are surfaced as exceptions and caught at the top level so the
  calculator keeps running.

## Testing

`unit_tests.h` contains a suite of assert-based unit tests for the `DatumStack`
class — covering both constructors and every member function (`isEmpty`,
`clear`, `size`, `top`, `pop`, `push`) across empty, single-element,
three-element, and 1000-element stacks, plus the expected `runtime_error` on
`top`/`pop` of an empty stack. These are the test *functions*; a driver `main`
that calls them is not included in the repository. The calculator itself was
validated by running programs through it and diff-testing the output.

## Files

| File | Role |
|------|------|
| `main.cpp` | Entry point — constructs an `RPNCalc` and calls `run()` |
| `RPNCalc.h` / `.cpp` | The interpreter: lexing, dispatch, and all commands |
| `DatumStack.h` / `.cpp` | Stack data structure over `std::list<Datum>` |
| `Datum.h` / `.cpp` | Tagged value type (int / bool / rstring) |
| `unit_tests.h` | Unit tests for `DatumStack` |
| `Makefile` | Build rules |
