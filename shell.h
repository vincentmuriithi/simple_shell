#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"

void handleCommand(char *command);
int check_command(const char *command, const char *path, char *full_path, size_t buf_size);
void error_exit(int exit_code, const char *message);

#endif
