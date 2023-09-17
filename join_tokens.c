#include "shell.h"

char* join_tokens(char** tokens, int count, const char* delimiter) {
int total_length = 0;
int i;
int j;
char* result;

for (i = 0; i < count; i++) {
total_length += strlen(tokens[i]) + strlen(delimiter);
}


result = (char*)malloc(total_length + 1);

if (!result) {
perror("Memory allocation failed");
exit(1);
}

result[0] = '\0';

for (j = 0; j < count; j++) {
strcat(result, tokens[j]);
if (j < count - 1) {
strcat(result, delimiter);
}
}

return (result);
}
