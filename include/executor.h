#ifndef EXECUTOR_H
#define EXECUTOR_H

/*
 * execute_command:
 * Forks and executes the input command line.
 * Supports background execution and output redirection.
 * Handles signal resetting for the child process.
 *
 * Parameters:
 *  - input: The raw command line input from the user.
 */

void execute_command(const char *input);
void setup_child_signals(void);
void launch_process(char **args, int is_background);

#endif


