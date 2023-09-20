#include "shell.h"
/**
* error_exit - Prints an error message and exits with the specified exit code.
* @exit_code: The exit code to use.
* @message: The error message to print.
*/
void error_exit(int exit_code, const char *message)
{
dprintf(STDERR_FILENO, "%s\n", message);
exit(exit_code);
}
