#ifndef PARSER_H
#define PARSER_H

#define PARSE_SUCCESS 0
#define PARSE_EMPTY 1

#define MAX_PIPE_CMDS 10
#define MAX_ARGS 128

typedef struct {
    char *args[MAX_ARGS];
} command_t;

typedef struct {
    command_t commands[MAX_PIPE_CMDS];
    int num_commands;
} pipeline_t;

/*
 * redirection_type_t:
 * Enumeration for output redirection types.
 */

typedef enum {
    REDIRECT_NONE,
    REDIRECT_TRUNCATE,
    REDIRECT_APPEND
} redirection_type_t;

/*
 * parse_command:
 * Parses the input command line, identifying command arguments,
 * output redirection (truncate or append), and background execution symbol (&).
 *
 * Memory Management:
 * This function internally allocates and frees memory for parsing purposes.
 * The caller must not attempt to free any memory related to parsing.
 *
 * Parameters:
 *  - input:          The raw input command line string.
 *  - args:           Output array to store command arguments for execvp (NULL-terminated).
 *  - is_background:  Output flag (set to 1 if the command should run in the background).
 *  - redir_type:     Output: indicates if output redirection is needed.
 *  - output_file:    Output: file name for output redirection, if applicable.
 *
 * Returns:
 *  - PARSE_SUCCESS (0) if parsing was successful.
 *  - PARSE_EMPTY (1) if the input was empty or invalid.
 */

int parse_command(const char *input, char **input_copy, pipeline_t *pipeline, int *is_background, redirection_type_t *redir_type, char **output_file);

#endif

