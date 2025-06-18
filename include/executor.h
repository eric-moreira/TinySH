#ifndef EXECUTOR_H
#define EXECUTOR_H

void execute_command(const char *input);
int parse_command(const char *input, char *input_copy, char **args, int *is_background);
void setup_child_signals(void);
void launch_process(char **args, int is_background);

#endif


