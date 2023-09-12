#include "shell.h"
/**
* handleCommand - handles
* @command: input
*
*/
void handleCommand(char *command)
{
int argCount;
char *pathDirs = NULL;
char *args[MAX_INPUT_LENGTH];
char *path = NULL;
char *token = strtok(command, " ");
if (token == NULL)
{
return;
}

argCount = 0;

while (1)
{
args[argCount] = strtok(NULL, " ");
if (args[argCount] == NULL)
{
break;
}
argCount++;
}
args[argCount] = NULL;

path = getenv("PATH");
pathDirs = strtok(path, ":");

while (pathDirs != NULL)
{
char full_path[MAX_INPUT_LENGTH];
snprintf(full_path, sizeof(full_path), "%s/%s", pathDirs, token);

if (access(full_path, X_OK) == 0)
{
pid_t pid = fork();
if (pid == -1)
{
error_exit(1, "Fork failed");
}
else if (pid == 0)
{
execv(full_path, args);
error_exit(1, "Exec failed");
}
else
{
int status;
waitpid(pid, &status, 0);
if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
{
fprintf(stderr, "Command not found: %s\n", token);
}
}
break;
}

pathDirs = strtok(NULL, ":");
}
}
