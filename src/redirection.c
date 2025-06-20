#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/redirection.h"

/*
 * setup_output_redirection:
 * Handles file opening and file descriptor duplication for output redirection.
 * Supports both truncate (">") and append (">>") modes.
 */

int setup_output_redirection(redirection_type_t redirect_type, const char *output_file){
    int fd;

    if(redirect_type == REDIRECT_TRUNCATE) {
        fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    } else if (redirect_type == REDIRECT_APPEND) {
        fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    } else {
        return 0;  // Nenhum redirecionamento
    }
    if (fd < 0) {
        perror("open failed for redirection");
        return -1;
    }

    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2 failed for redirection");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}