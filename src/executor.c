#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_command(const char *input) {
    char *args[128];
    char *token;
    char *input_copy = strdup(input);
    int is_background = 0;
    int i = 0;

    token = strtok(input_copy, " ");
    while (token != NULL && i < 127) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    if (i > 0 && strcmp(args[i - 1], "&") == 0) {
        is_background = 1;
        args[i - 1] = NULL;  // Remover o "&" da lista
    }
    args[i] = NULL;

    if (args[0] == NULL) {
        free(input_copy);
        return;
    }

    if (strcmp(args[0], "&") == 0) {
    // Usuário só digitou "&" como comando, ignora
    return;
}
    pid_t pid = fork();

    if (pid == 0) {
        // Processo filho
        signal(SIGINT, SIG_DFL);
        execvp(args[0], args);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Processo pai
        if (!is_background) {
            waitpid(pid, NULL, 0);
        } else {
            printf("pid: %d\n", pid);
        }
    } else {
        perror("fork failed");
    }

    free(input_copy);
}
