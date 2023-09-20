#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int handle_execute(char *args[], pid_t *pid) {
*pid = fork();

if (*pid == -1) {
perror("Fork failed");
return (-1);
}
else if (*pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("./shell");
exit(1);
}
}
return (0);
}
