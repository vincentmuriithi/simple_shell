#include "shell.h"
/**
* custom_tokenize - Tokenize a string based on spaces
* @input: The input string
* @args: An array to store the tokens
* Return: The number of tokens found
*/
int custom_tokenize(char *input, char **args)
{
int arg_count = 0;
char *token;
char *delimiter = " ";

while (input && *input) {
while (*input && strchr(delimiter, *input))
input++;

if (*input) {
token = input;

if (*input)
*input++ = '\0';
args[arg_count++] = token;
}
}

args[arg_count] = NULL;
return (arg_count);
}
