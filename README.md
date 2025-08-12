# Sword's Mini Shell
A minimal custom shell written in C as part of the Sword Health technical challenge.  
It handles built-in commands (`fib`, `caesar`, `exit`) and external Linux commands.

## Project Overview

The core function of this shell is to process user commands. It does this by handling the command itself, or asking the operating system to run an external program.

1.  **Handling Built-in Commands:** For a set of commands, the shell performs the action internally, without creating a new process. The built-ins are:
    *   **`exit`**: Terminates the shell program itself.
    *   **`fib`**: Calculates a Fibonacci number directly within the shell.
    *   **`caesar`**: Encrypts text using a Caesar cipher. This is a substitution technique where each letter is shifted a certain number of places down the alphabet. For example, a shift of 3 would turn 'A' into 'D'. The cipher smartly "wraps around" from Z back to A and leaves numbers and punctuation unchanged.

2.  **Executing External Programs:** For standard system commands like `ls` or `pwd`, the shell acts as a process launcher. It uses the operating system's `fork()` and `execvp()` functions to create a new process and run the specified program. The shell then waits for that program to finish before prompting the user for the next command.

This project demonstrates the fundamental workflow of a command-line shell: reading input, parsing it into a command and its arguments, and then dispatching the command to the appropriate handler.

## Features
- Command Prompt: Interactive `sword-shell>` prompt for user input.
- External Commands: Executes standard commands (`ls`, `pwd`, etc.) using `fork()`, `execvp()`, and `wait()`.
- Built-in Commands:
    - `fib <n>`: Calculates the nth Fibonacci number (0-indexed).
    - `caesar <shift> <text>`: Applies Caesar cipher to the given text.
    - `exit`: Cleanly exits the shell.
- Input Parsing: Parses user input into a command and its separate arguments.
- Error Handling: Gracefully handles malformed inputs and unrecognized commands.
- Logging: Includes a debug mode enabled via `make DEBUG=1`, using custom `log.h` macros.
- Unit Testing: Key logic tested using through a dedicated test suite.



## Prerequisites:
- GCC compiler (or equivalent C compiler)
- GNU Make
- Linux environment or WSL on Windows

## How to Compile and Run

#### Build the Shell
```bash
make
```
#### Build and Run the Shell
```bash
make run
```
#### Build with Debug Logging Enabled
```bash
make DEBUG=1
```
Debug logs will show internal flow (e.g., command dispatch, parsing info, logic execution).
To suppress logs, use the default build: `make run`.

#### Run Unit Tests
```bash
make test
```
## Cleanup
To remove all compiled files and executables, run:
```bash
make clean
```
## Testing
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
- shell.c: Main entry point, contains the core shell loop that reads and dispatches commands.
- shell_utils.c: Implementation of built-in commands (fib, caesar) and other helper logic.
- shell_utils.h: Header file declaring the functions that utilities provide.
- log.h: A simple macro-based system for conditional debug logging.
- test.c: Unit tests for the built-in command logic to ensure correctness.
- makefile: Automates the build, test, and cleanup processes.
- CHANGELOG.md: Detailed documentation of the improvements made to the project.
- README.md: This file.

## Author
Margarida Pinho - July 2025
