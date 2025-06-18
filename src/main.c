#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/executor.h"
#include <signal.h>
#define MAX_INPUT 1024

int main() {
    signal(SIGINT, SIG_IGN);
    char input[MAX_INPUT];

    while (1) {
        printf("tinysh> ");
        fflush(stdout);

        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            break;  // EOF
        }

        // Remove newline
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        execute_command(input);
    }

    return 0;
}
