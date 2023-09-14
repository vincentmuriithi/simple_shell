#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int change_directory(const char *path)
{
if (chdir(path) == -1)
{
perror("cd");
return (-1);
}
return (0);
}

