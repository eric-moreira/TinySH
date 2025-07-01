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
    pipeline_t pipeline;
    char *input_copy = NULL;
    redirection_type_t redirect = REDIRECT_NONE;
    char *output_file = NULL;

    input_copy = strdup(input);
    if (input_copy == NULL) {
        perror("strdup failed");
        return;
    }

    if (parse_command(input, &input_copy, &pipeline, &is_background, &redirect, &output_file)) {
        free(input_copy);
        return;
    }

    int num_cmds = pipeline.num_commands;
    int pipefd[2 * (num_cmds - 1)];
    pid_t pids[MAX_PIPE_CMDS];

    for (int i = 0; i < num_cmds - 1; i++) {
        if (pipe(pipefd + 2 * i) < 0) {
            perror("pipe failed");
            free(input_copy);
            return;
        }
    }

    for (int i = 0; i < num_cmds; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork failed");
            free(input_copy);
            return;
        }
        if (pids[i] == 0) {
            signal(SIGINT, SIG_DFL);
            if (i > 0) {
                dup2(pipefd[2 * (i - 1)], 0);
            }
            if (i < num_cmds - 1) {
                dup2(pipefd[2 * i + 1], 1);
            }
            for (int j = 0; j < 2 * (num_cmds - 1); j++) {
                close(pipefd[j]);
            }
            if (i == num_cmds - 1 && setup_output_redirection(redirect, output_file) < 0) {
                exit(EXIT_FAILURE);
            }
            execvp(pipeline.commands[i].args[0], pipeline.commands[i].args);
            fprintf(stderr, "tinysh: command not found: %s\n", pipeline.commands[i].args[0]);
            perror("exec failed");
            exit(EXIT_FAILURE);
        }
    }
    for (int j = 0; j < 2 * (num_cmds - 1); j++) {
        close(pipefd[j]);
    }
    if (!is_background) {
        for (int i = 0; i < num_cmds; i++) {
            waitpid(pids[i], NULL, 0);
        }
    } else {
        printf("[background] pids:");
        for (int i = 0; i < num_cmds; i++) {
            printf(" %d", pids[i]);
        }
        printf("\n");
    }
    free(input_copy);
}