#include "shell.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int wait_and_check(pid_t *pid, int *point)
{
int status;
int exit_status;

waitpid(*pid,& status, 0);
if (WIFEXITED(status))
{
exit_status = WEXITSTATUS(status);
if (exit_status != 0)
{
fprintf(stderr, "Command not found: %d\n", *point);
}
return (exit_status);
}
return (-1);
}
