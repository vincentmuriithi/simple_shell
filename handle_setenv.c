#include "shell.h"
#include <stdio.h>
#include <string.h>

int handle_setenv(char *input, char *setenv_args[], int *setenv_count) {
if (strncmp(input, "setenv ", 7) == 0) {
*setenv_count = custom_tokenize(input, setenv_args);
if (*setenv_count != 3) {
fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
} else {
if (setenv(setenv_args[1], setenv_args[2], 1) != 0) {
fprintf(stderr, "Failed to set environment variable.\n");
}
}
return (1);
}
return (0);
}

