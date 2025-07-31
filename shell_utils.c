
char shift_char(char c, int shift) {
    if (c >= 'a' && c <= 'z') {
        return ((c - 'a' + shift + 26) % 26) + 'a';
    } else if (c >= 'A' && c <= 'Z') {
        return ((c - 'A' + shift + 26) % 26) + 'A';
    } else {
        return c;  // Non-alphabetical characters remain unchanged
    }
}

// Encrypt argv[2] ... argv[argc-1] and return the result as a malloc’d string
char *caesar_encrypt_all_args(int argc, char *argv[], int shift) {
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