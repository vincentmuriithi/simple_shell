#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
/**
 * my_getline - reads a line from srandard input
 * Return: pointer
 */
char *my_getline(void)
{
char *line = NULL;
size_t bufsize = 0;

if (getline(&line, &bufsize, stdin) == -1)
{
perror("getline");
exit(EXIT_FAILURE);
}
return (line);
}
