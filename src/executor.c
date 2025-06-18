#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_command(const char *input) {
    char *args[128];
    char *token;
    char *input_copy = strdup(input);
    int i = 0;

    token = strtok(input_copy, " ");
    while (token != NULL && i < 127) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[0] == NULL) {
        free(input_copy);
        return;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Processo filho
        execvp(args[0], args);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Processo pai
        waitpid(pid, NULL, 0);
    } else {
        perror("fork failed");
    }

    free(input_copy);
}
