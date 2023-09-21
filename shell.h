#ifndef OURSHELL_H
#define OURSHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#include "v_macros.h"

/**
* struct info- d structure 4 d prog's data
* @program_name: d name of d executable
* @input_line: d pointer 2 d input read 4 _getline
* @command_name: d pointer 2 d 1st cmd typed by d user
* @exec_counter: d numb of excecuted cmds
* @file_descriptor: d file descriptor 2 d input of cmds
* @tokens: d pointer 2 array of tokenized input
* @env: d copy of d env
* @alias_list: d array of pointers wit aliases.
*/
typedef struct info
{
char *program_name;
char *input_line;
char *command_name;
int exec_counter;
int file_descriptor;
char **tokens;
char **env;
char **alias_list;
} data_of_program;

/**
* struct builtins - d structure 4 d builtins
* @builtin: d name of d builtin
* @function: d associated fxn 2 be called 4 each builtin
*/
typedef struct builtins
{
char *builtin;
int (*function)(data_of_program *data);
} builtins;

/*2 add, remove or show aliases*/
int output_alias(data_of_program *data, char *alias);

/*2 get d alias*/
char *fetch_alias(data_of_program *data, char *name);

/*2 add alias*/
int write_alias(char *string_alias, data_of_program *data);

/*2 allow 2 read a line frm cmd prompt*/
int _getlines(data_of_program * data);

/*2 check 4 logical operators nd split*/
int check_ops_logic(char *array_of_commands[], int m,
char array_of_operators[]);

/*exit prog wit status*/
int exit_builtin(data_of_program *data);

/*change wrking directory*/
int cd_builtin(data_of_program *data);

/*set wrking directory*/
int set_working_directory(data_of_program *data, char *new_dir);

/*show env of shell*/
int help_builtin(data_of_program *data);

/*aliases*/
int alias_builtin(data_of_program *data);

/*search nd execute builtins match*/
int list_of_builtins(data_of_program *data);

/*show shell env*/
int builtin_environment(data_of_program *data);

/*set env*/
int builtin_set_environment(data_of_program *data);

/*unset env*/
int builtin_unset_environment(data_of_program *data);

/*2 free an array of pointers*/
void free_array_of_pointers(char **array);

/*2 free all fields of a prog*/
void free_all_data(data_of_program *data);

/*2 free d fields needed 4 each loop of a prog*/
void free_recurrent_data(data_of_program *data);

/*2 execute cmd*/
int execution(data_of_program *data);

/*2 expand variables*/
void variables_expansion(data_of_program *data);

/*2 expand alias*/
void alias_expansion(data_of_program *data);

/*2 append 2 buffer*/
int add_to_buffer(char *buffer, char *strings);

/*2 check if file exists*/
int check_files(char *file_path);

/*2 find prog*/
int finding_program(data_of_program *data);

/*2 tokenize*/
char **tokenize_paths(data_of_program *data);

/*2 converts a numb 2 a string type*/
void long_to_string(long number, char *string, int base);

/*2 convert a string of digits 2 an int*/
int _atoi(char *s);

/*2 count d coincidences of char in string*/
int count_characters(char *string, char *character);

/*2 write an array of chars in d stderr*/
int _print_error(int errorcode, data_of_program *data);

/*2 write an array of chars in d stderr*/
int _printe(char *string);

/*2 write an array of chars in d stdout*/
int _print(char *string);

/*2 return d len of a null terminated string*/
int str_length(char *str);

/*2 duplicate a string*/
char *str_duplicate(char *str);

/*2 Compare two strings*/
int str_compare(char *str1, char *str2, int number);

/*2 concatenates two strings*/
char *str_concat(char *str1, char *str2);

/*2 reverse a string*/
void str_reverse(char *str);

/*2 initialize d variables of d prog*/
int main(int argc, char *argv[], char *env[]);

/*2 print d prompt in a new line when d signal SIGINT*/
void handle_ctrl_c(int opr UNUSED);

/*2 inicialize d structure wit d info of d prog*/
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env);

/*An infinite loop dat shows d prompt*/
void sisifo(char *prompt, data_of_program *data);

/*2 separate strings wit delimiters*/
char *_strtok(char *line, char *delim);

char *environment_get_key(char *key, data_of_program *data);

int environment_set_key(char *key, char *value, data_of_program *data);

int environment_remove_key(char *key, data_of_program *data);

void print_environment(data_of_program *data);

void tokenize(data_of_program *data);

#endif
