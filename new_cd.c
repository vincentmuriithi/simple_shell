#include "shell.h"
#include <stdio.h>

extern char **environ;
/**
* change_directory - Change the current working directory
* @new_dir: The directory to change to
* Return: 0 on success, -1 on failure
*/
int change_directory(char *new_dir)
{
char current_dir[PATH_MAX];
if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
perror("getcwd");
return (-1);
}

if (chdir(new_dir) == -1)
{

perror("chdir");
return (-1);
}

if (setenv("PWD", getcwd(NULL, 0), 1) == -1) {
perror("setenv");
return (-1);
}

if (setenv("OLDPWD", current_dir, 1) == -1)
{
perror("setenv");
return (-1);
}

return (0);
}
