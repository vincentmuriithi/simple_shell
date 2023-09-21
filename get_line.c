#include "shell.h"
/**
* _getlines - allow to read a line from  command prompt
* @data: The structure containing data of program
* Return: The number of bytes
*/
int _getlines(program_data *data)
{
char buffer[BUFFER_SIZE] = {'\0'};
static char *array_of_commands[10] = {NULL};
static char array_of_operators[10] = {'\0'};
ssize_t read_bytes, m = 0;


if (!array_of_commands[0] || (array_of_operators[0] == '&' && errno != 0) || (
array_of_operators[0] == '|' && errno == 0))
{

for (m = 0; array_of_commands[m]; m++)
{
free(array_of_commands[m]);
array_of_commands[m] = NULL;
}

read_bytes = read(data->file_descriptor, &buffer, BUFFER_SIZE - 1);
if (read_bytes == 0)
{
return (-1);
}
m = 0;
do {
array_of_commands[m] = str_duplicate(_strtok
(m ? NULL : buffer, "\n;"));
m = check_ops_logic(array_of_commands, m, array_of_operators);
} while (array_of_commands[m++]);
}

data->input_line = array_of_commands[0];

for (m = 0; array_of_commands[m]; m++)
{
array_of_commands[m] = array_of_commands[m + 1];
array_of_operators[m] = array_of_operators[m + 1];
}

return (str_length(data->input_line));
}

/**
* check_ops_logic - check for logical operators nd split
* @array_of_commands: The array of various cmds
* @m: The index in array of cmds being checked
* @array_of_operators: The array of previous cmd's logical operators
* Return: The index of last cmd in array of cmds
*/
int check_ops_logic(char *array_of_commands[], int m,
char array_of_operators[])
{
char *temporary = NULL;
int q;

for (q = 0; array_of_commands[m] != NULL && array_of_commands[m][q]; q++)
{
if (array_of_commands[m][q] == '&' && array_of_commands[m][q + 1] == '&')
{

temporary = array_of_commands[m];
array_of_commands[m][q] = '\0';
array_of_commands[m] = str_duplicate(array_of_commands[m]);
array_of_commands[m + 1] = str_duplicate(temporary + q + 2);
m++;
array_of_operators[m] = '&';
free(temporary);
}
if (array_of_commands[m][q] == '|' && array_of_commands[m][q + 1] == '|')
{

temporary = array_of_commands[m];
array_of_commands[m][q] = '\0';
array_of_commands[m] = str_duplicate(array_of_commands[q]);
array_of_commands[m + 1] = str_duplicate(temporary + q + 2);
m++;
array_of_operators[m] = '|';
free(temporary);
q = 0;
}
}
return (m);
}

