#include "shell.h"

/**
* custom_tokenize - Tokenize a string based on a custom delimiter
* @input: The input string
* @args: An array to store the tokens
* @delimiter: The delimiter to use for tokenization
* Return: The number of tokens found
*/
int custom_tokenize(char *input, char **args, const char *delimiter)
{
int arg_count = 0;
char *token;

while (input && *input)
{
while (*input && strchr(delimiter, *input))
input++;

if (*input)
{
token = input;
while (*input && !strchr(delimiter, *input))
input++;

if (*input)
*input++ = '\0';
args[arg_count++] = token;
}
}

args[arg_count] = NULL;
return (arg_count);
}

