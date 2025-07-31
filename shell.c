
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

#define MAX_LINE 1024
#define MAX_ARGS 100
#define MAX_WAIT 5  // seconds


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
    
    return argc;
}


void execute_external_command(char *argv[]) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return;
    }
    else if(pid == 0) {
        // Child process: execute the command
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
                    printf("Child exited with status %d\n", WEXITSTATUS(status));
                } else if (WIFSIGNALED(status)) {
                    printf("Child terminated by signal %d\n", WTERMSIG(status));
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

int main() {
    char *argv[MAX_ARGS];
    int argc;

    while (1) {
        argc = read_and_parse_input(argv);
        if (argc == 0) continue;  // skip empty input
        else if (strcmp(argv[0], "exit") == 0) {
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