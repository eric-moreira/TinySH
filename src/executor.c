#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/parser.h"
#include "../include/redirection.h"

/*
 * execute_command:
 * Handles parsing, forking, signal management, output redirection, 
 * and command execution for each user input.
 */

void execute_command(const char *input) {    
    int is_background = 0;
    char *args[128];
    int *bg = &is_background;
    char *input_copy = NULL;
    redirection_type_t redirect = REDIRECT_NONE;
    char *output_file = NULL;

    input_copy = strdup(input);

    if(parse_command(input, &input_copy, args, bg, &redirect, &output_file)) {
        return;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Processo filho
        signal(SIGINT, SIG_DFL);
        if (setup_output_redirection(redirect, output_file) < 0) {
            exit(EXIT_FAILURE);
        }
        
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