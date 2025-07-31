#include <assert.h>
#include <string.h>
#include "shell_utils.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief        Tests the successful computation of Fibonacci numbers.
 * @details      Validates the Fibonacci sequence for known values.
 *  @param argc   Argument count (should be >= 2 for valid input)
 *  @param argv   Argument values; argv[1] must be a non-negative integer
 *  @return       0 on success, 1 on invalid input  
 */
void test_compute_fibonacci_success() {
    assert(compute_fibonacci(0) == 0);
    assert(compute_fibonacci(1) == 1);
    assert(compute_fibonacci(10) == 55);
    printf("test_compute_fibonacci_success passed\n");
}

/**
 * @brief        Tests the error handling of the 'fib' command.
 * @details      Checks for invalid inputs such as missing arguments, non-integer values,
 *              and negative numbers.
 *  @param argc   Argument count (should be >= 2 for valid input)
 *  @param argv   Argument values; argv[1] must be a non-negative integer
 *  @return       0 on success, 1 on invalid input  
 */
void test_compute_fibonacci_invalid() {
    char *args1[] = {"fib"};
    assert(handle_fib(1, args1) == 1);

    char *args2[] = {"fib", "abc"};
    assert(handle_fib(2, args2) == 1);

    char *args3[] = {"fib", "-1"};
    assert(handle_fib(2, args3) == 1);

    printf("test_compute_fibonacci_invalid passed\n");
}

/**
 * @brief        Tests the successful encryption of arguments using Caesar cipher.
 * @details      Validates the encryption for various shifts and multiple arguments.
 *  @param argc   Argument count (should be >= 3 for valid input)
 *  @param argv   Argument values; argv[2] and onward are encrypted and joined
 *  @return       A newly allocated string containing the encrypted message.
 *               Returns NULL on allocation failure.
 *
 * @note         Caller is responsible for freeing the returned string.
 */
void test_caesar_encrypt_all_args_success() {
    char *args1[] = {"caesar", "2", "Hello", NULL};
    char *res1 = caesar_encrypt_all_args(3, args1, 2);
    assert(strcmp(res1, "Jgnnq") == 0);
    free(res1);

    char *args2[] = {"caesar", "-1", "abc", NULL};
    char *res2 = caesar_encrypt_all_args(3, args2, -1);
    assert(strcmp(res2, "zab") == 0);
    free(res2);

    char *args3[] = {"caesar", "3", "Hello,", "World!", NULL};
    char *res3 = caesar_encrypt_all_args(4, args3, 3);
    assert(strcmp(res3, "Khoor, Zruog!") == 0);
    free(res3);

    printf("test_caesar_encrypt_all_args_success passed\n");
}

/**
 * @brief        Tests the error handling of the 'caesar' command.
 * @details      Checks for invalid inputs such as missing arguments, non-integer shifts,
 *              and insufficient arguments.
 *  @param argc   Argument count (should be >= 3 for valid input)
 *  @param argv   Argument values; argv[1] is the shift, argv[2...] is the text
 *  @return       0 on success, 1 on invalid input  
 */
void test_handle_caesar_invalid() {
    char *args1[] = {"caesar"};
    assert(handle_caesar(1, args1) == 1);

    char *args2[] = {"caesar", "x", "Hello"};
    assert(handle_caesar(3, args2) == 1);

    char *args3[] = {"caesar", "3"};
    assert(handle_caesar(2, args3) == 1);

    printf("test_handle_caesar_invalid passed\n");
}
/**
 * @brief        Main function to run all tests.
 * @details      Calls each test function and checks assertions.
 *  @return       0 on success, non-zero on failure
 */
int main() {
    test_compute_fibonacci_success();
    test_compute_fibonacci_invalid();
    test_caesar_encrypt_all_args_success();
    test_handle_caesar_invalid();
    printf("All success & error tests passed!\n");
    return 0;
}