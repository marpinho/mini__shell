// shell_utils.h
#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H

char *caesar_encrypt_all_args(int argcount, char *arguments[], int shift);
char shift_char(char c, int shift);
long compute_fibonacci(long n);
int handle_fib(int argcount, char *arguments[]);
int handle_caesar(int argcount, char *arguments[]);

#endif