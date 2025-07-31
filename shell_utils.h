// shell_utils.h
#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H

char *caesar_encrypt_all_args(int argc, char *argv[], int shift);
char shift_char(char c, int shift);
long compute_fibonacci(long n);
int handle_fib(int argc, char *argv[]);
int handle_caesar(int argc, char *argv[]);

#endif