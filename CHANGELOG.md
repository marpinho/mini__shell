## 1. Executive Summary

The initial version of the `sword-shell` was a functional prototype with a good modular structure. The new version enhances this foundation by focusing on three critical areas: **memory safety**, **robustness and stability**, and **code clarity and documentation**.

The most impactful change was the overhaul of the input handling mechanism, replacing a fixed-size buffer with a dynamic one. Additional improvements were made to the command execution logic to increase stability, variable naming conventions and the inline documentation was expanded to demonstrate a deeper understanding.

## 2. Detailed Change Log

### Improvement 1: Enhanced Memory Safety with Dynamic Input Handling

This is directly addressing a potential vulnerability and limitation in the old version.

*   **Change:** Replaced a fixed-size `static` buffer and `fgets()` with dynamic memory allocation via `getline()` in the main loop.
*   **Reasoning & Benefit:**
    *   **Elimination of Buffer Overflow Risk:** The old fixed-size buffer was unsafe. Any user input exceeding `MAX_LINE` would cause a buffer overflow. `getline()` completely solves this by dynamically allocating exactly as much memory as needed.
    *   **Memory Ownership:** The new `main` function now "owns" the input buffer, calling `getline()` to allocate it and `free(input)` a single time when the program exits. This is a cleaner and safer memory management.

### Improvement 2: Simplified and Stabilized Command Execution

The logic for running external commands was re-thinked to align with standard shell design principles.

*   **Change:** The custom, non-standard timeout feature (implemented with a complex polling loop) was removed. It was replaced with a single, standard, blocking call to `wait(&status)`.

*   **Reasoning & Benefit:**
    *   **Adherence to the Unix Philosophy:** This change establishes the shell's role as an *executor*, not a *manager*. The shell should run the user's commands and wait for them to complete. It is the user's responsibility, not the shell's, to terminate a misbehaving process.
    *   **Increased Reliability and Efficiency:** A single, blocking `wait()` call is an efficient way for a simple shell to manage a child process. It consumes zero CPU resources while waiting for the operating system's signal.
    *   **Predictable and Standard Behavior:** The shell now behaves like standard shells such as `bash`, meeting user expectations and removing surprising behavior.


### Improvement 3: Improved Code Clarity and Maintainability

Made the code more readable, less ambiguous, and easier to maintain.

*   **Change 1: Contextual Variable Naming:** Parameters in command-handling and utility functions were renamed from the generic `argc`/`argv` to the more descriptive `argcount`/`arguments`.

*   **Reasoning & Benefit:** The names `argc` and `argv` are a ingrained convention for `main`'s arguments. Reusing them created ambiguity. The new names make the code's intent immediately obvious, preventing potential bugs.

*   **Change 2: Comprehensive Code Documentation:** Imrpoved full Doxygen-style documentation for all functions and files.

*   **Reasoning & Benefit:** The documentation now describis *what* the code does and explains *why*. This includes file-level summaries, detailed function contracts with `@param` and `@return` tags, and inline comments explaining design choices.

### Improvement 4: Overhauled Project Documentation (README.md)

The project's primary documentation file, `README.md`, was rewritten to be more comprehensive, and accessible to a wider audience.

*   **Change:** The new version introduces a high-level "Project Overview" and restructures for better readability.

*   **Reasoning & Benefit:**
    *   **Added "Project Overview":** A new section was created to explain the project's purpose and design in simple, non-technical terms. This makes the project's goals understandable to any reader.

