#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PARSE_SUCCESS 0
#define PARSE_EMPTY 1

int parse_command(const char *input, char **input_copy, char **args, int *is_background){
    char *token;
    int i = 0;
    
    *input_copy = strdup(input);
    if (*input_copy == NULL) {
        perror("strdup failed");
        return PARSE_EMPTY;
    }

    token = strtok(*input_copy, " ");

    while (token != NULL && i < 127) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    if (i > 0 && strcmp(args[i - 1], "&") == 0) {
        *is_background = 1;
        args[i - 1] = NULL;  // Remover o "&" da lista
    }
    args[i] = NULL;

    if (args[0] == NULL) {
        return PARSE_EMPTY;
    }

    if (strcmp(args[0], "&") == 0) {
        return PARSE_EMPTY;
    }
    return PARSE_SUCCESS;
}

void execute_command(const char *input) {    
    int is_background = 0;
    char *args[128];
    int *bg = &is_background;
    char *input_copy;


    if(parse_command(input, &input_copy, args, bg)) {
        return;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Processo filho
        signal(SIGINT, SIG_DFL);
        execvp(args[0], args);
        fprintf(stderr, "tinysh: command not found: %s\n", args[0]);
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