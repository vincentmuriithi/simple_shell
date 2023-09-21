#include "shell.h"
/**
* exit_builtin -exit program wit status
* @data: a structure 4 prog data
* Return: 0 on success, otherwise if declared
*/
int exit_builtin(program_data *data)
{
int m;

if (data->tokens[1] != NULL)
{
for (m = 0; data->tokens[1][m]; m++)
if ((data->tokens[1][m] < '0' || data->tokens
[1][m] > '9') && data->tokens[1][m] != '+')
{
errno = 2;
return (2);
}
errno = _atoi(data->tokens[1]);
}
free_all_data(data);
exit(errno);
}
/**
* cd_builtin - change working directory
* @data: a structure 4 prog data
* Return: 0 on success, otherwise if declared
*/
int cd_builtin(program_data *data)
{
char *home_directory = environment_get_key
("HOME", data), *old_directory = NULL;
char old_directories[126] = {0};
int error_codes = 0;

if (data->tokens[1])
{
if (str_compare(data->tokens[1], "-", 0))
{
old_directory = environment_get_key("OLDPWD", data);
if (old_directory)
error_codes = set_working_directory(data, old_directory);
_print(environment_get_key("PWD", data));
_print("\n");
return (error_codes);
}
else
return (set_working_directory(data, data->tokens[1]));
}
else
{
if (!old_directory)
home_directory = getcwd(old_directories, 128);
return (set_working_directory(data, home_directory));
}
return (0);
}
/**
* set_working_directory - set working directory
* @data: a structure for program  data
* @new_dir:  path for wrking directory
* Return: 0 on success, otherwise if declared
*/
int set_working_directory(program_data *data, char *new_dir)
{
char old_directories[128] = {0};
int error_code = 0;

getcwd(old_directories, 128);
if (!str_compare(old_directories, new_dir, 0))
{
error_code = chdir(new_dir);
if (error_code == -1)
{
errno = 2;
return (3);
}
environment_set_key("PWD", new_dir, data);
}
environment_set_key("OLDPWD", old_directories, data);
return (0);
}
/**
* help_builtin - shows environment of shell
* @data: a structure for program data
* Return: 0 on succes, otherwise if declared
*/
int help_builtin(program_data *data)
{
int m, len = 0;
char *messages[6] = {NULL};

messages[0] = HELP_MSG;
if (data->tokens[1] == NULL)
{
_print(messages[0] + 6);
return (1);
}
if (data->tokens[2] != NULL)
{
errno = E2BIG;
perror(data->command_name);
return (5);
}
messages[1] = HELP_EXIT_MSG;
messages[2] = HELP_ENV_MSG;
messages[3] = HELP_SETENV_MSG;
messages[4] = HELP_UNSETENV_MSG;
messages[5] = HELP_CD_MSG;

for (m = 0; messages[m]; m++)
{
len = str_length(data->tokens[1]);
if (str_compare(data->tokens[1], messages[m], len))
{
_print(messages[m] + len + 1);
return (1);
}
}
errno = EINVAL;
perror(data->command_name);
return (0);
}
/**
* alias_builtin -  aliases
* @data: a structure for program data
* Return: 0 on succes, otherwise if declared
*/
int alias_builtin(program_data *data)
{
int m = 0;

if (data->tokens[1] == NULL)
return (output_alias(data, NULL));
while (data->tokens[++m])
{
if (count_characters(data->tokens[m], "="))
write_alias(data->tokens[m], data);
else
output_alias(data, data->tokens[m]);
}
return (0);
}

