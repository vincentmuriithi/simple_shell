#include "shell.h"

/**
* free_recurrent_data -  free the fields nided for each loop of a program
* @data: structure of data
* Return: returns void
*/
void free_recurrent_data(program_data *data)
{
if (data)
{
if (data->tokens)
{
free_array_of_pointers(data->tokens);
data->tokens = NULL;
}
if (data->input_line)
{
free(data->input_line);
data->input_line = NULL;
}
if (data->command_name)
{
free(data->command_name);
data->command_name = NULL;
}
}
}

/**
*free_all_data - free all fields of a program
*@data: structure of  program's data
*Return: returns void
*/
void free_all_data(program_data *data)
{
if (data)
{
if (data->file_descriptor != 0)
{
if (close(data->file_descriptor) == -1)
{
perror(data->program_name);
}
}
free_recurrent_data(data);
if (data->env)
{
free_array_of_pointers(data->env);
}
if (data->alias_list)
{
free_array_of_pointers(data->alias_list);
}
}
}

/**
*free_array_of_pointers - free an array of pointers
*@array: array of pointers
*Return: void
*/
void free_array_of_pointers(char **array)
{
int t;

if (array == NULL)
{
return;
}

for (t = 0; array[t] != NULL; t++)
{
free(array[t]);
array[t] = NULL;
}

free(array);
array = NULL;
}

