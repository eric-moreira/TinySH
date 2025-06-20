#ifndef REDIRECTION_H
#define REDIRECTION_H

#include "parser.h"  // Para ter acesso ao enum redirection_type_t


/*
 * setup_output_redirection:
 * Handles output redirection for the current process.
 * Opens the target output file and redirects STDOUT accordingly (using dup2).
 *
 * This function must be called from within the child process after fork,
 * but before execvp.
 *
 * Parameters:
 *  - redirect_type:  Type of redirection (none, truncate, append).
 *  - output_file:    Path to the output file for redirection.
 *
 * Returns:
 *  - 0 on success.
 *  - Negative value on failure (stderr will contain the error message).
 */

int setup_output_redirection(redirection_type_t redirect_type, const char *output_file);

#endif
