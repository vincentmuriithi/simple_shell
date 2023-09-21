#include "shell.h"
/**
* _strtok - separates strings wit delimiters
* By Kene and Esther
* @line: a pointer to array we received in getline.
* @delimiters: a char we mark off string in parts.
* Return: a pointer to the created token
*/
char *_strtok(char *line, char *delimiters)
{
int v;
static char *str;
char *copystr;

if (line != NULL)
str = line;
for (; *str != '\0'; str++)
{
for (v = 0; delimiters[v] != '\0'; v++)
{
if (*str == delimiters[v])
break;
}
if (delimiters[v] == '\0')
break;
}
copystr = str;
if (*copystr == '\0')
return (NULL);
for (; *str != '\0'; str++)
{
for (v = 0; delimiters[v] != '\0'; v++)
{
if (*str == delimiters[v])
{
*str = '\0';
str++;
return (copystr);
}
}
}
return (copystr);
}
