#include "shell.h"
/**
* check_files - check if file exists
* @file_path: filename
* Return: 0 on succes
*/
int check_files(char *file_path)
{
struct stat s;

if (stat(file_path, &s) != -1)
{
if (S_ISDIR(s.st_mode) || access(file_path, X_OK))
{
errno = 126;
return (126);
}
return (0);
}
errno = 127;
return (127);
}
/**
* finding_program - find program
* @data: structure for program data
* Return: 0 on success, or error code
*/
int finding_program(program_data *data)
{
int m = 0, r_code = 0;
char **dir;

if (!data->command_name)
return (2);

if (data->command_name[0] == '/' || data->command_name[0] == '.')
return (check_files(data->command_name));
free(data->tokens[0]);
data->tokens[0] = str_concat(str_duplicate("/")
, data->command_name);
if (!data->tokens[0])
return (2);
dir = tokenize_paths(data);
if (!dir || !dir[0])
{
errno = 127;
return (127);
}
for (m = 0; dir[m]; m++)
{
dir[m] = str_concat(dir[m], data->tokens[0]);
r_code = check_files(dir[m]);
if (r_code == 0 || r_code == 126)
{
errno = 0;
free(data->tokens[0]);
data->tokens[0] = str_duplicate(dir[m]);
free_array_of_pointers(dir);
return (r_code);
}
}
free(data->tokens[0]);
data->tokens[0] = NULL;
free_array_of_pointers(dir);
return (r_code);
}
/**
* tokenize_paths - tokenizeer
* @data: program data
* Return: d array of paths
*/
char **tokenize_paths(program_data *data)
{
int m = 0, count_dir = 2;
char **tok = NULL, *path;

path = environment_get_key("PATH", data);
if ((path == NULL || path[0] == '\0'))
return (NULL);

path = str_duplicate(path);
for (m = 0; path[m]; m++)
{
if (path[m] == ':')
count_dir++;
}
tok = malloc(sizeof(char *) * count_dir);
m = 0;
tok[m] = str_duplicate(_strtok(path, ":"));
while (tok[m++])
{
tok[m] = str_duplicate(_strtok(NULL, ":"));
}
free(path);
path = NULL;
return (tok);
}

