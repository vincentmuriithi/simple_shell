#include "shell.h"
#include <stdlib.h>
#include <string.h>

int handle_exit(char *input, int *status)
{
char *status_str = NULL;

if (input == NULL || status == NULL)
return (1);

if (strcmp(input, "exit") == 0)
{
exit(0);
}
else if (strncmp(input, "exit ", 5) == 0)
{
status_str = input + 5;
*status = atoi(status_str);
return (1);
}
return (0);
}

