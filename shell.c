
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/wait.h>
#include "shell_utils.h"
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "log.h"


#define MAX_LINE 1024
#define MAX_ARGS 100
#define MAX_WAIT 5  // seconds

/**
 * @brief        Reads user input and tokenizes it into arguments.
 *
 * @details      Displays the shell prompt, reads a line from stdin,
 *               and splits it into tokens stored in argv[].
 *
 * @param argv   Output array to store parsed command and arguments
 * @return       Number of arguments parsed (argc); 0 if empty or invalid
 */
int read_and_parse_input(char *argv[]) {
    static char input[MAX_LINE];  // static so argv points to it safely
    printf("sword-shell> ");
    fflush(stdout);

    if (fgets(input, MAX_LINE, stdin) == NULL) {
        // Handle EOF (e.g., Ctrl+D)
        printf("\n");
        exit(0);
    }

    // Remove newline
    input[strcspn(input, "\n")] = 0;
    DEBUG_PRINT("User entered: %s", input);


    // Check for empty input
    if (strlen(input) == 0 || strspn(input, " \t") == strlen(input)) {
        return 0;
    }

    // Tokenize input
    int argc = 0;
    char *token = strtok(input, " ");     // Split input at spaces

    while (token != NULL && argc < MAX_ARGS - 1) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL;  // Null-terminate array
    DEBUG_PRINT("Parsed %d arguments", argc);
    DEBUG_PRINT("Arguments:");
    for (int i = 0; i < argc; i++) {
        DEBUG_PRINT("  argv[%d]: %s", i, argv[i]);
    }   
  
    return argc;
}

/**
 * @brief        Executes an external command using fork and execvp.
 *
 * @details      Forks a new process to run the external command passed in argv.
 *               Waits for the child process with a timeout. If the command takes
 *               too long, it is terminated to avoid blocking the shell.
 *
 * @param argv   Null-terminated array of command arguments
 */
void execute_external_command(char *argv[]) {
    pid_t pid = fork();
    DEBUG_PRINT("Forked process with PID %d", pid);

    if (pid < 0) {
        perror("Fork failed");
        return;
    }
    else if(pid == 0) {
        // Child process: execute the command
        DEBUG_PRINT("Executing external command: %s", argv[0]);
        DEBUG_PRINT("Arguments:");
        for (int i = 0; argv[i] != NULL; i++) {
            DEBUG_PRINT("  argv[%d]: %s", i, argv[i]);
        }
        execvp(argv[0], argv);
        //when it ends sends signal SIGCHILD to the parent
        perror("execvp failed");
        exit(EXIT_FAILURE);
    
    }
    else if( pid > 0) {
        // Parent process: wait for the child to finish
        int status;
        time_t start = time(NULL);

        while (1) {
            pid_t result = waitpid(pid, &status, WNOHANG);

            if (result == -1) {
                perror("waitpid failed");
                return;
            }

            if (result > 0) {
                // Child has finished
                if (WIFEXITED(status)) {
                    DEBUG_PRINT("Child exited with status %d\n", WEXITSTATUS(status));
                } else if (WIFSIGNALED(status)) {
                    DEBUG_PRINT("Child terminated by signal %d\n", WTERMSIG(status));
                }
                break;
            }

            // Child still running, check for timeout
            if (time(NULL) - start >= MAX_WAIT) {
                printf("Command exceeded time limit (%d seconds), killing it.\n", MAX_WAIT);
                kill(pid, SIGKILL);
                waitpid(pid, &status, 0);  // Reap the child
                break;
            }

            usleep(100000);  // sleep 100ms
        }
    
    }
    
}

/**
 * @brief        Entry point of the mini shell application.
 *
 * @details      Continuously displays a shell prompt, reads user input,
 *               parses commands, and dispatches them to built-in or external
 *               handlers. Exits when the "exit" command is issued or EOF is received.
 *
 * @return       Exit code of the shell program (0 for normal exit)
 */
int main() {
    char *argv[MAX_ARGS];
    int argc;

    DEBUG_PRINT("Starting shell loop");

    while (1) {
        argc = read_and_parse_input(argv);
        if (argc == 0) continue;  // skip empty input

        if (strcmp(argv[0], "exit") == 0) {
            DEBUG_PRINT("Exiting shell");
            break;  // Exit the shell
        } else if (strcmp(argv[0], "fib") == 0) {
            handle_fib(argc, argv);
        } else if (strcmp(argv[0], "caesar") == 0) {
            handle_caesar(argc, argv);
        } else {
            execute_external_command(argv);
        }
    }

    return 0;
}