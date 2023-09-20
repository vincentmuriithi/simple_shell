#include "shell.h"

int execute_command(const char *command)
{
int count;
pid_t pid;
char *args[32];
char command_copy[MAX_INPUT_LENGTH];
strncpy(command_copy, command, sizeof(command_copy));

count = custom_tokenize(command_copy, args, " ");
args[count] = NULL;
pid = fork();

if (pid == -1)
{
perror("Fork failed");
return (-1);
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
return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

return (0);
}

