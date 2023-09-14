/**
* custom_cd - Change the current working directory.
* @args: An array of command arguments.
* @env: The environment variables.
*
* Return: 0 on success, 1 on failure.
*/
int custom_cd(char **args, char **env)
{
char *new_dir;
char *previous_dir = NULL;
char *current_dir = NULL;

if (args[1] == NULL)
{
new_dir = getenv("HOME");
}
else if (strcmp(args[1], "-") == 0)
{
previous_dir = getenv("OLDPWD");
if (previous_dir == NULL)
{
fprintf(stderr, "cd: OLDPWD not set\n");
return (1);
}
new_dir = previous_dir;
}
else
{
new_dir = args[1];
}

current_dir = getcwd(NULL, 0);
if (current_dir == NULL)
{
perror("getcwd");
return (1);
}

if (chdir(new_dir) == -1)
{
perror("chdir");
free(current_dir);
return (1);
}

if (setenv("PWD", getcwd(NULL, 0), 1) == -1)
{
perror("setenv");
free(current_dir);
return (1);
}
if (setenv("OLDPWD", current_dir, 1) == -1)
{
perror("setenv");
free(current_dir);
return (1);
}

free(current_dir);
return (0);
}
