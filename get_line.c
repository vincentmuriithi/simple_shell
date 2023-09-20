#include "shell.h"
char* my_getline(void)
{
char* line = NULL;
size_t len = 0;
ssize_t read;


read = getdelim(&line, &len, '\n', stdin);

if (read == -1)
{
perror("getdelim");
free(line);
return (NULL);
}

if (read > 0 && line[read - 1] == '\n')
{
line[read - 1] = '\0';
}

return (line);
}
