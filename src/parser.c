#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

/*
 * parse_command:
 * Tokenizes the input command line, populates the pipeline array,
 * detects output redirection operators (">", ">>") and checks for background execution symbol (&).
 * This function performs destructive parsing using strtok().
 * Memory allocated internally is freed before returning.
 */

int parse_command(const char *input, char **input_copy, pipeline_t *pipeline, int *is_background, redirection_type_t *redir_type, char **output_file) {
    char *token;
    size_t cmd_idx = 0, arg_idx = 0;

    if (*input_copy == NULL) {
        perror("strdup failed");
        return PARSE_EMPTY;
    }

    token = strtok(*input_copy, " ");
    pipeline->num_commands = 0;

    while (token != NULL && cmd_idx < MAX_PIPE_CMDS) {
        if (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0) {
            *redir_type = (strcmp(token, ">>") == 0) ? REDIRECT_APPEND : REDIRECT_TRUNCATE;
            token = strtok(NULL, " ");
            if (token != NULL) {
                *output_file = token;
            } else {
                fprintf(stderr, "tinysh: syntax error near unexpected token `newline`\n");
                return PARSE_EMPTY;
            }
        } else if (strcmp(token, "|") == 0) {
            pipeline->commands[cmd_idx].args[arg_idx] = NULL;
            cmd_idx++;
            arg_idx = 0;
        } else {
            pipeline->commands[cmd_idx].args[arg_idx++] = token;
        }
        token = strtok(NULL, " ");
    }
    pipeline->commands[cmd_idx].args[arg_idx] = NULL;
    pipeline->num_commands = cmd_idx + 1;

    if (arg_idx > 0 && strcmp(pipeline->commands[cmd_idx].args[arg_idx - 1], "&") == 0) {
        *is_background = 1;
        pipeline->commands[cmd_idx].args[arg_idx - 1] = NULL;
    }

    if (pipeline->commands[0].args[0] == NULL) {
        return PARSE_EMPTY;
    }
    return PARSE_SUCCESS;
}
