#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int is_valid_integer(const char *str) {
    if (*str == '\0') return 0;

    if (*str == '+' || *str == '-') str++;

    if (!*str) return 0;  // Sign only, no digits

    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }

    return 1;
}