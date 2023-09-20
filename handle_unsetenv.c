#include "shell.h"
#include <stdio.h>
#include <string.h>

int handle_unsetenv(char *input, char *unsetenv_args[], int *unsetenv_count) {
if (strncmp(input, "unsetenv ", 9) == 0) {
*unsetenv_count = custom_tokenize(input, unsetenv_args);
if (*unsetenv_count != 2) {
fprintf(stderr, "Usage: unsetenv VARIABLE\n");
} else {
if (unsetenv(unsetenv_args[1]) != 0) {
fprintf(stderr, "Failed to unset environment variable.\n");
}
}
return (1);
}
return (0);
}
