#include "shell.h"
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
int exec_status;
char *args[32], **env = NULL, *input = NULL;
pid_t pid;
int count = 0, status = 0;
char *setenv_args[3], *unsetenv_args[2];
int setenv_count = 0, unsetenv_count = 0;
char *path = getenv("PATH");

if (path == NULL)
error_exit(1, "Failed to get PATH environment variable");

while (1)
{
printf("($) ");
input = my_getline();
input[strcspn(input, "\n")] = '\0';

if (handle_exit(input, &status))
exit(status);
else if (handle_setenv(input, setenv_args, &setenv_count))
continue;
else if (handle_unsetenv(input, unsetenv_args, &unsetenv_count))
continue;

if (strcmp(input, "env") == 0)
{
env = environ;
while (*env)
{
printf("%s\n", *env);
env++;
}
continue;
}

count = custom_tokenize(input, args);
args[count] = NULL;

if (handle_execute(args, &pid) == -1)
perror("Fork failed");


if (wait_and_check(&pid, &exec_status) && WIFEXITED(exec_status) && WEXITSTATUS(exec_status) != 0)
printf("Command not found: %s\n", args[0]);
}

return (0);
}
