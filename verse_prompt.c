#include "shell.h"
/**
* main - entry of main program
* @argc: argument count
* @argv: argument value
* @env: number  of values received from the command line
* Return: Nothing (zero on succes).
*/
int main(int argc, char *argv[], char *env[])
{
program_data  data_struct = {NULL}, *data = &data_struct;
char *prompt = "";

inicialize_data(data, argc, argv, env);

signal(SIGINT, handle_ctrl_c);

if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
{
errno = 2;
prompt = PROMPT_MSG;
}
errno = 0;
sisifo(prompt, data);
return (0);
}


/**
* handle_ctrl_c - prints the prompt in a new line when d signal SIGINT
* which is ctrl + c is sent to the program
* @UNUSED: option of d prototype
*/
void handle_ctrl_c(int opr UNUSED)
{
_print("\n");
_print(PROMPT_MSG);
}

/**
* inicialize_data - initialize the structure with the info of the program
* @data: a pointer to d structure of the data
* @argv: an array of arg passed to d prog execution
* @env: d environ passed to d prog execution
* @argc: d numb of values received frm d cmd line
*/
void inicialize_data(program_data *data, int argc, char *argv[], char **env)
{
int t = 0;

data->program_name = argv[0];
data->input_line = NULL;
data->command_name = NULL;
data->exec_counter = 0;

/* define the file descriptor to be read*/
if (argc == 1)
data->file_descriptor = STDIN_FILENO;
else
{
data->file_descriptor = open(argv[1], O_RDONLY);
if (data->file_descriptor == -1)
{
_printe(data->program_name);
_printe(": 0: Can't open ");
_printe(argv[1]);
_printe("\n");
exit(127);
}
}
data->tokens = NULL;
data->env = malloc(sizeof(char *) * 50);
if (env)
{
for (; env[t]; t++)
{
data->env[t] = str_duplicate(env[t]);
}
}
data->env[t] = NULL;
env = data->env;

data->alias_list = malloc(sizeof(char *) * 20);
for (t = 0; t < 20; t++)
{
data->alias_list[t] = NULL;
}
}


/**
* sisifo - infinite loop dat shows the prompt
* @prompt: prompt to  be printed
* @data: an infinite loop dat shows d prompt
*/
void sisifo(char *prompt, program_data  *data)
{
int error_code = 0, string_len = 0;

for (data->exec_counter = 1;; ++(data->exec_counter))
{
_print(prompt);
error_code = string_len = _getlines(data);

if (error_code == EOF)
{
free_all_data(data);
exit(errno);
}
if (string_len >= 1)
{
alias_expansion(data);
variables_expansion(data);
tokenize(data);
if (data->tokens[0])
{
error_code = execution(data);
if (error_code != 0)
_print_error(error_code, data);
}
free_recurrent_data(data);
}
}
}
