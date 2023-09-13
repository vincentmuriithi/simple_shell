#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
extern char **environ;
/**
* main - entry of program
* Return: 0 upon success
*/
int main(void)
{
char *args[32];
pid_t pid;
int count = 0;
char **env = NULL;
char *path = getenv("PATH");
char *input = NULL;

if (path == NULL)
error_exit(1, "Failed to get PATH environment variable");

while (1)
{
printf("($) ");
input = my_getline();
input[strcspn(input, "\n")] = '\0';

if (strcmp(input, "exit") == 0)
{
exit(0);
}
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

return (0);
}
