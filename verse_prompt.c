#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
extern char **environ;

int main(void)
{
char *args[32];
pid_t pid;
int count = 0;
char **env = NULL;
char *path = getenv("PATH");
char *input = NULL;
char *status_str = NULL;
int status = 0;
char *setenv_args[3];
int setenv_count = 0;
char *unsetenv_args[2];
int unsetenv_count = 0;
char *home_dir = NULL;
char *commands[32];
int command_count = 0;
char *command = NULL;
int i;

if (path == NULL)
error_exit(1, "Failed to get PATH environment variable");

while (1)
{
printf("($) ");
input = my_getline();
input[strcspn(input, "\n")] = '\0';

command_count = custom_tokenize(input, commands, ";");

for (i = 0; i < command_count; i++)
{
command = commands[i];

if (strcmp(command, "exit") == 0)
{
exit(0);
}
else if (strncmp(command, "exit ", 5) == 0)
{
status_str = command + 5;
status = atoi(status_str);
exit(status);
}
else if (strncmp(command, "setenv ", 7) == 0)
{
setenv_count = custom_tokenize(command, setenv_args, " ");

if (setenv_count != 3)
{
fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
}
else
{
if (setenv(setenv_args[1], setenv_args[2], 1) != 0)
{
perror("setenv");
}
}
}
else if (strncmp(command, "unsetenv ", 9) == 0)
{
unsetenv_count = custom_tokenize(command, unsetenv_args, " ");

if (unsetenv_count != 2)
{
fprintf(stderr, "Usage: unsetenv VARIABLE\n");
}
else
{
if (unsetenv(unsetenv_args[1]) != 0)
{
perror("unsetenv");
}
}
}
else if (strncmp(command, "cd", 2) == 0)
{
count = custom_tokenize(command, args, " ");
if (count > 1)
{
if (change_directory(args[1]) != 0)
{
fprintf(stderr, "cd: Unable to change directory\n");
}
}
else
{
home_dir = getenv("HOME");
if (home_dir != NULL)
{
if (change_directory(home_dir) != 0)
{
fprintf(stderr, "cd: Unable to change directory\n");
}
}
}
}
else if (strcmp(command, "env") == 0)
{
env = environ;
while (*env)
{
printf("%s\n", *env);
env++;
}
}
else
{
count = custom_tokenize(command, args, " ");
args[count] = NULL;
pid = fork();
if (pid == -1)
{
perror("Fork failed");
exit(1);
}
else if (pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("Exec failed");
exit(1);
}
}
else
{
int status;
waitpid(pid, &status, 0);
if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
{
printf("Command not found: %s\n", args[0]);
}
}
}
}
}

return (0);
}

