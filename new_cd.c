#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
* change_directory - Change the current working directory.
* @path: The directory path to change to.
* Return: 0 on success, -1 on failure.
*/
int change_directory(const char *path)
{
char *oldpwd = NULL;
char *currentpwd = NULL;
char *previous_dir = NULL;

if (path != NULL && strcmp(path, "-") == 0)
{
previous_dir = getenv("OLDPWD");
if (previous_dir == NULL)
{
fprintf(stderr, "cd: OLDPWD not set\n");
return (-1);
}
path = previous_dir;
}

oldpwd = getcwd(NULL, 0);
if (oldpwd == NULL)
{
perror("getcwd");
return (-1);
}
if (chdir(path) == -1)
{
perror("chdir");
free(oldpwd);
return (-1);
}

currentpwd = getcwd(NULL, 0);
if (currentpwd == NULL)
{
perror("getcwd");
free(oldpwd);
return (-1);
}

if (setenv("PWD", currentpwd, 1) == -1)
{
perror("setenv");
free(oldpwd);
free(currentpwd);
return (-1);
}

printf("%s\n", currentpwd);
if (setenv("OLDPWD", oldpwd, 1) == -1)
{

perror("setenv");
free(oldpwd);
free(currentpwd);
return (-1);
}

free(oldpwd);
free(currentpwd);

return (0);
}
