#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

/*
 * parse_command:
 * Tokenizes the input command line, populates the args array,
 * detects output redirection operators (">", ">>"), 
 * and checks for background execution symbol (&).
 *
 * This function performs destructive parsing using strtok().
 * Memory allocated internally is freed before returning.
 */


int parse_command(const char *input, char **input_copy, char **args, int *is_background, redirection_type_t *redir_type, char **output_file) {
    char *token;
    int i = 0;

    *input_copy = strdup(input);
    if (*input_copy == NULL) {
        perror("strdup failed");
        free(input_copy);
        return PARSE_EMPTY;
    }

    token = strtok(*input_copy, " ");

    while (token != NULL && i < 127) {
        if (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0) {
            *redir_type = (strcmp(token, ">>") == 0) ? REDIRECT_APPEND : REDIRECT_TRUNCATE;
            token = strtok(NULL, " ");
            if (token != NULL) {
                *output_file = token;
            } else {
                fprintf(stderr, "tinysh: syntax error near unexpected token `newline`\n");
                free(input_copy);
                return PARSE_EMPTY;
            }
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " ");
    }

    if (i > 0 && strcmp(args[i - 1], "&") == 0) {
        *is_background = 1;
        args[i - 1] = NULL;  // Remove "&" da lista de args
    }
    args[i] = NULL;

    if (args[0] == NULL || strcmp(args[0], "&") == 0) {
        free(input_copy);
        return PARSE_EMPTY;
    }
    free(input_copy);
    return PARSE_SUCCESS;
}
