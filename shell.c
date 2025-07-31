
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024

int main() {
    char input[MAX_INPUT];

    while (1) {
        // Display the shell prompt
        printf("sword-shell> ");
        fflush(stdout); // Ensure prompt is printed immediately

        // Read user input
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            printf("\n");
            break; // EOF (Ctrl+D), exit the shell
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';


        //just echo the command
        printf("You entered: %s\n", input);
    }

    printf("Exiting sword-shell.\n");
    return 0;
}

