#include "shell.h"
/**
* output_alias - add, remove or show aliases
* @data: a structure for program data
* @alias: input
* Return: 0 on success, otherwise if declared
*/
int output_alias(program_data *data, char *alias)
{
int m, q, length_of_alias;
char buff[250] = {'\0'};

if (data->alias_list)
{
length_of_alias = str_length(alias);
for (m = 0; data->alias_list[m]; m++)
{
if (!alias || (str_compare(data->alias_list[m]
, alias, length_of_alias) && data->alias_list
[m][length_of_alias] == '='))
{
for (q = 0; data->alias_list[m][q]; q++)
{
buff[q] = data->alias_list[m][q];
if (data->alias_list[m][q] == '=')
break;
}
buff[q + 1] = '\0';
add_to_buffer(buff, "'");
add_to_buffer(buff, data->alias_list[m] + q + 1);
add_to_buffer(buff, "'\n");
_print(buff);
}
}
}
return (0);
}
/**
* fetch_alias -get the alias
* @data:structure for prog data
* @name: name of alias
* Return: 0 on success, otherwise if declared
*/
char *fetch_alias(program_data *data, char *name)
{
int m, length_of_alias;

if (name == NULL || data->alias_list == NULL)
return (NULL);
length_of_alias = str_length(name);
for (m = 0; data->alias_list[m]; m++)
{
if (str_compare(name, data->alias_list[m]
, length_of_alias) && data->alias_list[m][length_of_alias] == '=')
{
return (data->alias_list[m] + length_of_alias + 1);
}
}
return (NULL);
}
/**
* write_alias - add alias
* @string_alias: the alias
* @data: structure for prog data
* Return: 0 on success, otherwise if declared
*/
int write_alias(char *string_alias, program_data *data)
{
int m, q;
char buff[250] = {'0'}, *temporary = NULL;


if (string_alias == NULL || data->alias_list == NULL)
return (1);
for (m = 0; string_alias[m]; m++)
{
if (string_alias[m] != '=')
buff[m] = string_alias[m];
else
{
temporary = fetch_alias(data, string_alias + m + 1);
break;
}
}
for (q = 0; data->alias_list[q]; q++)
{
if (str_compare(buff, data->alias_list[q]
, m) && data->alias_list[q][m] == '=')
{
free(data->alias_list[q]);
break;
}
}
if (temporary)
{
add_to_buffer(buff, "=");
add_to_buffer(buff, temporary);
data->alias_list[q] = str_duplicate(buff);
}
else
data->alias_list[q] = str_duplicate(string_alias);
return (0);
}

