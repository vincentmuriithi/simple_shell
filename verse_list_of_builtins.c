#include "shell.h"
/**
* list_of_builtins - search and execute builtins match
* @data: structure for program data
* Return: a function executed of -1 on failure
*/
int list_of_builtins(program_data *data)
{
int t;
builtins options[] = {
{"exit", exit_builtin},
{"help", help_builtin},
{"cd", cd_builtin},
{"alias", alias_builtin},
{"env", builtin_environment},
{"setenv", builtin_set_environment},
{"unsetenv", builtin_unset_environment},
{NULL, NULL}
};
for (t = 0; options[t].builtin != NULL; t++)
{
if (str_compare(options[t].builtin, data->command_name, 0))
{
return (options[t].function(data));
}
}
return (-1);
}
