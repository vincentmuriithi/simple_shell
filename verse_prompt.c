#include "ourshell.h"
/**
* main - a fxn dat initialize d variables of d prog
* @argc: d arg count
* By Kene and Esther
* @argv: d arg value
* @env: d numb of values received frm d cmd line
* Return: Nothing (zero on succes).
*/
int main(int argc, char *argv[], char *env[])
{
data_of_program data_struct = {NULL}, *data = &data_struct;
char *prompt = "";

inicialize_data(data, argc, argv, env);

signal(SIGINT, handle_ctrl_c);

if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
{/* We re in d terminal, interactive mode */
errno = 2;/*???????*/
prompt = PROMPT_MSG;
}
errno = 0;
sisifo(prompt, data);
return (0);
}


/**
* handle_ctrl_c - a fxn dat prints d prompt in a new line when d signal SIGINT
* which is ctrl + c is sent 2 d prog
* @UNUSED: option of d prototype
* By Kene and Esther
*/
void handle_ctrl_c(int opr UNUSED)
{
_print("\n");
_print(PROMPT_MSG);
}

/**
* inicialize_data - a fxn dat inicialize d structure wit d info of d prog
* @data: a pointer 2 d structure of d data
* @argv: an array of arg passed 2 d prog execution
* @env: d environ passed 2 d prog execution
* @argc: d numb of values received frm d cmd line
* By Kene and Esther
*/
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
int t = 0;

data->program_name = argv[0];
data->input_line = NULL;
data->command_name = NULL;
data->exec_counter = 0;
/* define d file descriptor 2 be readed*/
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
* sisifo - a fxn of an infinite loop dat shows d prompt
* @prompt: d prompt 2 be printed
* By Kene and Esther
* @data: an infinite loop dat shows d prompt
*/
void sisifo(char *prompt, data_of_program *data)
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
