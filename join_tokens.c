#include <stdio.h>
#include "shell.h"
#include <stdlib.h>
#include <string.h>

char* join_tokens(char** tokens, int count, const char* delimiter) {
int i;
int total_length = 0;
char* joined_str = NULL;

if (count <= 0 || tokens == NULL) {
return NULL;
}


for (i = 0; i < count; i++) {
total_length += strlen(tokens[i]);
if (i < count - 1) {
total_length += strlen(delimiter);
}
}

joined_str = (char*)malloc(total_length + 1);

if (joined_str == NULL) {
perror("Failed to allocate memory for joined string");
exit(EXIT_FAILURE);
}

strcpy(joined_str, tokens[0]);

for (i = 1; i < count; i++) {
strcat(joined_str, delimiter);
strcat(joined_str, tokens[i]);
}

return (joined_str);
}
