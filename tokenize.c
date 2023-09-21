#include "shell.h"

/**
* tokenize - separates the string using a designed delimiter
* @data: a pointer to the program's data
* Return: an array of d diff parts of d string
*/
void tokenize(program_data *data)
{
char *delimiter = " \t";
int m, q, counter = 2, length;

length = str_length(data->input_line);
if (length)
{
if (data->input_line[length - 1] == '\n')
data->input_line[length - 1] = '\0';
}

for (m = 0; data->input_line[m]; m++)
{
for (q = 0; delimiter[q]; q++)
{
if (data->input_line[q] == delimiter[q])
counter++;
}
}

data->tokens = malloc(counter *sizeof(char *));
if (data->tokens == NULL)
{
perror(data->program_name);
exit(errno);
}
m = 0;
data->tokens[m] = str_duplicate(_strtok(data->input_line, delimiter));
data->command_name = str_duplicate(data->tokens[0]);
while (data->tokens[m++])
{
data->tokens[m] = str_duplicate(_strtok(NULL, delimiter));
}
}

