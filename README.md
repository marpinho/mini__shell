# Sword's Mini Shell
A minimal custom shell written in C as part of the Sword Health technical challenge.  
Handles built-in commands (`fib`, `caesar`, `exit`) and external Linux commands.

## Features
- Command Prompt: Interactive `sword-shell>` prompt for user input.
- External Commands: Executes standard command (`ls`, `pwd`, etc.) using `fork()`, `execvp()`, and `wait()`.
- Built-in Commands:
    - `fib <n>`: Calculates the nth Fibonacci number (0-indexed).
    - `caesar <shift> <text>`: Applies Caesar cipher to text with support for shifts and punctuation.
    - `exit`: Cleanly exits the shell.
- Input Parsing: Tokenization of user input with support for quoted strings and multiple arguments.
- Error Handling: Graceful recovery from malformed inputs and unrecognized commands.
- Logging: Debug mode enabled via `make DEBUG=1`, using custom `log.h` macros.
- Unit Tests: Key logic tested using assertions.



## Prerequisites:
- GCC compiler
- GNU Make
- Linux environment or WSL

## Compile:
- `make`           # builds the shell
- `make run`       # builds and runs the shell
- `make DEBUG=1`   # builds with debug logging enabled
- `make test`      # runs unit tests for core logic

## Cleanup
Removes 
```bash
make clean
```

## Debugging
Enable debug messages by compiling with DEBUG=1:
```bash
make DEBUG=1 run
```
Debug logs will show internal flow (e.g., command dispatch, parsing info, logic execution).
To suppress logs, use the default build: `make run`.

## Testing

Run:
```bash
make test
```

Unit tests verify:
- Correct Fibonacci outputs (e.g., `fib 0`, `fib 10`)
- Proper handling of invalid inputs (e.g., `fib abc`, `caesar x Hello`)
- Caesar encryption with both positive and negative shifts
- Basic edge cases for both logic and input validation

Tests are located in `test.c` and run using assertions (`assert()`).

## Usage Examples

```bash
sword-shell> fib 7 
13 

sword-shell> fib hello 
Invalid input. Usage: fib <n>

sword-shell> caesar -3 khoor 
hello

sword-shell> caesar wow 
Invalid input. Usage: caesar <shift> <text>

sword-shell> ls -l 
(total output from your system)

sword-shell> exit 

```

## File Structure
. <br />
 ├── shell.c              # Main shell entry and loop <br />
 ├── shell_utils.c        # Implementation of logic helpers (fib, caesar) <br />
 ├── shell_utils.h        # Function declarations <br />
 ├── log.h                # Debug log macros <br />
 ├── test.c               # Unit tests for core logic <br />
 ├── makefile             # Build automation <br />
 └── README.md            # Project documentation <br />



## Author
Margarida Pinho - July 2025
