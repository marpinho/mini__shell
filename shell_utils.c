
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "log.h"


/**
 * @brief        Shifts a character by a given Caesar cipher shift.
 *
 * @details      Only letters (a–z, A–Z) are shifted; case is preserved.
 *               Non-alphabetic characters are returned unchanged.
 *
 * @param c      Character to shift
 * @param shift  Shift value for Caesar cipher
 * @return       Shifted character
 */
char shift_char(char c, int shift) {
    if (c >= 'a' && c <= 'z') {
        return ((c - 'a' + shift + 26) % 26) + 'a';
    } else if (c >= 'A' && c <= 'Z') {
        return ((c - 'A' + shift + 26) % 26) + 'A';
    } else {
        return c;  // Non-alphabetical characters remain unchanged
    }
}

/**
 * @brief        Shifts a character by a given Caesar cipher shift.
 *
 * @details      Only letters (a–z, A–Z) are shifted; case is preserved.
 *               Non-alphabetic characters are returned unchanged.
 *
 * @param c      Character to shift
 * @param shift  Shift value for Caesar cipher
 * @return       Shifted character
 */
char *caesar_encrypt_all_args(int argc, char *argv[], int shift) {
    // Encrypt argv[2] ... argv[argc-1] and return the result as a malloc’d string
    // First, calculate total length
    int total_len = 0;
    for (int i = 2; i < argc; i++) {
        total_len += strlen(argv[i]);
        if (i < argc - 1) total_len++; // for space
    }

    // Allocate space for result (+1 for '\0')
    char *result = malloc(total_len + 1);
    if (!result) return NULL; // Check for malloc failure

    int pos = 0;
    for (int i = 2; i < argc; i++) {
        for (int j = 0; argv[i][j] != '\0'; j++) {
            result[pos++] = shift_char(argv[i][j], shift);
        }
        if (i < argc - 1) {
            result[pos++] = ' ';
        }
    }

    result[pos] = '\0'; // Null-terminate
    return result;
}

/**
 * @brief        Computes the nth Fibonacci number using an iterative method.
 *
 * @param n      Index of the Fibonacci number (must be >= 0)
 * @return       The nth Fibonacci number
 */
long compute_fibonacci(long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    long a = 0, b = 1, temp;
    for (long i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}
/**
 * @brief        Handles the built-in 'fib' command.
 *
 * @details      Computes and prints the nth Fibonacci number (0-indexed).
 *               Validates the input to ensure it's a non-negative integer.
 *
 * @param argc   Argument count (should be exactly 2)
 * @param argv   Argument vector: argv[1] must be a non-negative integer
 * @return       0 on success, 1 on invalid input
 */
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

/**
 * @brief        Handles the built-in 'caesar' command.
 *
 * @details      Applies a Caesar cipher to the input text using the given shift.
 *               Validates input and prints the encrypted result.
 *
 * @param argc   Argument count; must be at least 3
 * @param argv   Argument vector; argv[1] is the shift, argv[2...] is the text
 * @return       0 on success, 1 on invalid input
 */
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
    DEBUG_PRINT("Handling Caesar with shift %d", shift_val);

    char *encrypted = caesar_encrypt_all_args(argc, argv, shift_val);
    if (!encrypted) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    printf("%s\n", encrypted);
    free(encrypted);

    return 0;
}