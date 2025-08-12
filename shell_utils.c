/**
 * @file shell_utils.c
 * @author Margarida Pinho
 * @brief Implementation of built-in shell commands and parsing logic.
 * @date August 2025
 *
 * @details This file contains the core logic for commands that are handled
 * directly by the shell, such as 'fib' and 'caesar'. It also includes
 * the functions responsible for parsing user input and executing external
 * commands.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "log.h"


/**
 * @brief Computes the nth Fibonacci number using an iterative method.
 *
 * @param n The index in the Fibonacci sequence (must be non-negative).
 * @return long The nth Fibonacci number, or a negative value on overflow.
 */
long compute_fibonacci(long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    // Use an iterative approach to avoid stack overflow from deep recursion.
    long a = 0, b = 1, temp;
    for (long i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

/**
 * @brief Shifts a single character by a given value for the Caesar cipher.
 *
 * @details The core of the Caesar cipher is this modular arithmetic. It ensures
 * that letters "wrap around" the alphabet (e.g., 'z' + 1 becomes 'a') and
 * handles both positive and negative shifts correctly. Non-alphabetic
 * characters are returned unchanged.
 *
 * @param c The character to be shifted.
 * @param shift The integer value to shift by.
 * @return char The shifted character.
 */
char shift_char(char c, int shift) {
    if (c >= 'a' && c <= 'z') {
        return ((c - 'a' + shift + 26) % 26) + 'a';
    } else if (c >= 'A' && c <= 'Z') {
        return ((c - 'A' + shift + 26) % 26) + 'A';
    } else {
        return c;  
    }
}

/**
 * @brief Encrypts and concatenates multiple string arguments into a single message.
 *
 * @details Iterates through the provided arguments, encrypts each character
 * using shift_char(), and joins them with spaces into a single string.
 * This function calculates the required memory upfront to avoid multiple
 * costly reallocations.
 *
 * @param argcount The total number of arguments.
 * @param arguments The array of string arguments. Text to be encrypted starts at index 2.
 * @param shift The integer shift value for the Caesar cipher.
 *
 * @return char* A newly allocated string containing the full encrypted message.
 * @return NULL If memory allocation fails.
 *
 * @note The caller is responsible for freeing the returned string to prevent memory leaks.
 */
char *caesar_encrypt_all_args(int argcount, char *arguments[], int shift) {
    int total_len = 0;
    for (int i = 2; i < argcount; i++) {
        total_len += strlen(arguments[i]);
    }
    // Add space for spaces between words and the final null terminator.
    total_len += (argcount - 3) + 1;

    char *result = malloc(total_len);
    if (!result) return NULL; // Check for malloc failure

    int pos = 0;
    for (int i = 2; i < argcount; i++) {
        for (int j = 0; arguments[i][j] != '\0'; j++) {
            result[pos++] = shift_char(arguments[i][j], shift);
        }
        // Add a space after each word except the last one.
        if (i < argcount - 1) {
            result[pos++] = ' ';
        }
    }

    result[pos] = '\0'; // Null-terminate
    return result;
}

/**
 * @brief Handles the 'fib' built-in command.
 *
 * @details Parses the user's input, validates it, and if valid, computes
 *          and prints the nth Fibonacci number. Provides user-friendly error
 *          messages for incorrect usage.
 *
 * @param argcount The number of arguments in the 'arguments' array. Expected to be 2.
 * @param arguments A null-terminated array of strings.
 *                  - arguments[0] is expected to be "fib".
 *                  - arguments[1] is the string to be converted to a number 'n'.
 *
 * @return int Returns 0 on successful execution.
 * @return int Returns 1 if the input is invalid.
 */
int handle_fib(int argcount, char *arguments[]){
    if (argcount != 2) {
        printf("Usage: fib <n>\n");
        return 1;
    }

    char *endptr;
    errno = 0;
    // Use strtol instead of atoi for robust error checking.
    long n = strtol(arguments[1], &endptr, 10);

    // - *endptr != '\0' means there were non-numeric characters left.
    // - errno != 0 means the number was out of range (e.g., too large).
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
 * @brief Handles the 'caesar' built-in command.
 *
 * @details Parses the user's input for a shift value and text, then encrypts
 *          and prints the result. Provides user-friendly error messages.
 *
 * @param argcount The number of arguments. Expected to be at least 3.
 * @param arguments A null-terminated array of strings.
 *                  - arguments[0] is expected to be "caesar".
 *                  - arguments[1] is the shift value.
 *                  - arguments[2...] is the text to be encrypted.
 *
 * @return int Returns 0 on successful execution.
 * @return int Returns 1 if the input is invalid.
 */
int handle_caesar(int argcount, char *arguments[]) {

    if (argcount < 3) {
        printf("Invalid input. Usage: caesar <shift> <text>\n");
        DEBUG_PRINT("Insufficient arguments for 'caesar' command");
        return 1;
    }

    char *endptr;
    errno = 0;

    long shift = strtol(arguments[1], &endptr, 10);

    // Check for a range error (overflow/underflow) with errno
    // Check for a format error with endptr (non-numeric characters)
    if (errno != 0 || *endptr != '\0') {
        printf("Invalid input. Usage: caesar <shift> <text>\n");
        DEBUG_PRINT("Invalid shift value: %s", arguments[1]);
        return 1;
    }

    int shift_val = (int)shift;
    DEBUG_PRINT("Handling Caesar with shift %d", shift_val);

    char *encrypted = caesar_encrypt_all_args(argcount, arguments, shift_val);
    if (!encrypted) {
        DEBUG_PRINT("Memory allocation failed for Caesar encryption");
        return 1;
    }

    printf("%s\n", encrypted);
    free(encrypted);    
    encrypted = NULL;

    return 0;
}