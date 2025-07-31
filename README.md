# Sword's Mini Shell
A minimal custom shell written in C as part of the Sword Health technical challenge.  
Handles built-in commands (`fib`, `caesar`, `exit`) and external Linux commands.

## Features
- `exit`: Quits the shell
- `fib <n>`: Computes the nth Fibonacci number (0-indexed)
- `caesar <shift> <text>`: Encodes <text> using Caesar cipher with positive/negative <shift>
- anything else: Run as an external command (`ls`, `pwd`, etc.) using `fork()`, `execvp()`, and `wait()`

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

  
## Author
Margarida Pinho - July 2025
