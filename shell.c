
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "shell_utils.c"

#define MAX_LINE 1024
#define MAX_ARGS 100


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

int handle_fib(int argc, char *argv[]){
    if (argc != 2) {
        printf("Usage: fib <n>\n");
        return 1;
    }

    char *endptr;
    errno = 0;
    long n = strtol(argv[1], &endptr, 10);

    // Check for errors: invalid characters or out-of-range
    if (*endptr != '\0' || errno != 0 || n < 0) {
        printf("Invalid input. Usage: fib <n>\n");
        return 1;
    }
    
    long result = compute_fibonacci(n);

    if (result < 0) {
        printf("Error: Fibonacci number too large.\n");
        return 1;
    }
    // Print the result
    printf("%ld\n", result);
    return 0;
}


int handle_caesar(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Invalid input. Usage: caesar <shift> <text>\n");
        return 1;
    }

    char *endptr;
    errno = 0;

    long shift = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || shift > INT_MAX) {
        printf("Invalid input. Usage: caesar <shift> <text>\n");
        return 1;
    }

    int shift_val = (int)shift;
        char *encrypted = caesar_encrypt_all_args(argc, argv, shift_val);
    if (!encrypted) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    printf("%s\n", encrypted);
    free(encrypted);

    return 0;
}

int main() {
    char *argv[MAX_ARGS];
    int argc;

    while (1) {
        argc = read_and_parse_input(argv);
        if (argc == 0) continue;  // skip empty input

        if (strcmp(argv[0], "exit") == 0) {
            break;
        } else if (strcmp(argv[0], "fib") == 0) {
           handle_fib(argc, argv);
        } else if (strcmp(argv[0], "caesar") == 0) {
           handle_caesar(argc, argv);
        } else {
            //execute_external_command(argv);
        }
    }

    return 0;
}