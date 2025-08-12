/**
 * @file shell.c
 * @author Margarida Pinho
 * @brief Main entry point and core loop for the sword-shell application.
 * @date July 2025
 *
 * @details This file is responsible for initializing the shell, running the
 * main interactive loop that reads user input, and dispatching commands to the
 * appropriate handlers (either built-in functions or external programs).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "shell_utils.h"
#include "log.h"


#define MAX_ARGS 100

/**
 * @brief Parses a raw string into a command and its arguments.
 *
 * @details Takes a null-terminated string and tokenizes it based on spaces.
 * It modifies the input string in-place by replacing spaces with null terminators.
 * The resulting tokens are stored in the 'arguments' array.
 *
 * @param[in] input The raw input string read from the user. This string will be modified.
 * @param[out] arguments An output array of char pointers that will be populated with
 *                       pointers to the start of each token within the input string.
 *
 * @return int The number of arguments parsed (argcount).
 */
 int parse_input(char* input, char *arguments[]) {

    if (input[0] == '\0' || input[0] == '\n') {
        return 0;
    }

    // Remove the trailing newline character from getline, if present
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    int argcount = 0;
    // strtok modifies the input string by placing null terminators.
    // strtok does not create new strings or new copies of the data. 
    char *token = strtok(input, " "); // Split input at spaces

    while (token != NULL && argcount < MAX_ARGS - 1) {
        arguments[argcount++] = token;
        token = strtok(NULL, " ");
    }
    // The arguments array MUST be terminated by a NULL pointer for execvp.
    arguments[argcount] = NULL; 

    return argcount;
}

/**
 * @brief Executes an external command in a new child process.
 *
 * @details This function uses the fork-exec-wait pattern to run a command.
 * It forks the shell, and the child process attempts to replace its image
 * with the new command using execvp. The parent process waits for the child
s * to complete before continuing.
 *
 * @param arguments A null-terminated array of strings representing the command
 *                  and its arguments (e.g., {"ls", "-l", NULL}).
 *
 * @note This function does not return a value. Errors are printed to stderr.
 */
void execute_external_command(char *arguments[]) {
    pid_t pid = fork();
    DEBUG_PRINT("Forked process with PID %d", pid);

    if (pid < 0) {
        perror("Fork failed");
        return;
    }
    else if(pid == 0) {
        // Child process: execute the command

        DEBUG_PRINT("Executing external command: %s", arguments[0]);
        DEBUG_PRINT("Arguments:");
        for (int i = 0; arguments[i] != NULL; i++) {
            DEBUG_PRINT("  arguments[%d]: %s", i, arguments[i]);
        }

        // execvp replaces the current process image with a new program.
        if (execvp(arguments[0], arguments) == -1) {
            // If execvp returns, an error has occurred
            perror(arguments[0]);
            exit(EXIT_FAILURE); // Exit child process on error
        }
    
    }
    else {
        // Parent process: wait for the child to finish

        int status;
        /// wait() blocks the parent process until the child has terminated.
        pid_t result = wait(&status);

        if (result == -1) {
            perror("wait failed");
            return;
        }

        // Check the exit status of the child
        if (WIFEXITED(status)) {
            DEBUG_PRINT("Child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            DEBUG_PRINT("Child terminated by signal %d\n", WTERMSIG(status));
        }
    }
}


/**
 * @brief The main entry point and run loop for sword-shell.
 *
 * @details Initializes the shell and enters an infinite loop to:
 * 1. Display a prompt.
 * 2. Read a line of user input using getline.
 * 3. Parse the input into a command and arguments.
 * 4. Dispatch the command to the correct handler.
 * The loop terminates when the 'exit' command is entered or EOF is received.
 *
 * @return int Returns 0 on successful, clean exit.
 */
int main() {
    char *arguments[MAX_ARGS];  
    char *input = NULL;         // Buffer for user input, allocated by getline
    size_t len = 0;             // Size of the input buffer
    int argcount;

    while (1) {
        printf("sword-shell> ");
        fflush(stdout); // Ensure the prompt is displayed immediately

        // getline handles memory allocation, just need to free when the loop ends
        if (getline(&input, &len, stdin) == -1) {
            if (feof(stdin)) {
                // End of file (Ctrl+D) was received
                DEBUG_PRINT("\nExiting shell.\n");
                break;
            }
            perror("getline");
            continue; // Go to the next loop iteration on error
        }

        argcount = parse_input(input, arguments);

        if (argcount == 0) {
            // If the line was empty or just whitespace, show a new prompt.
            continue;  
        } else if (strcmp(arguments[0], "exit") == 0) {
            DEBUG_PRINT("Exiting shell");
            break;  // Exit the shell
        } else if (strcmp(arguments[0], "fib") == 0) {
            handle_fib(argcount, arguments);
        } else if (strcmp(arguments[0], "caesar") == 0) {
            handle_caesar(argcount, arguments);
        } else {
            execute_external_command(arguments);
        }
    }

    // Free the final buffer allocated by getline before exiting.
    free(input);
    input = NULL; // Good practice to nullify dangling pointers.
    
    DEBUG_PRINT("Shell shutting down.");
    return 0;
}