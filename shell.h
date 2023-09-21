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
* struct verse_info- d structure 4 d prog's data
* @program_name: d name of d executable
* @input_line: pointer to the input read for _getline
* @command_name: pointer 2 d 1st cmd typed by d user
* @exec_counter: number of excecuted cmds
* @file_descriptor:  file descriptor to the input of cmds
* @tokens: pointer to array of tokenized input
* @env: copy of the environment
* @alias_list: the array of pointers with  aliases.
*/
typedef struct verse_info
{
char *program_name;
char *input_line;
char *command_name;
int exec_counter;
int file_descriptor;
char **tokens;
char **env;
char **alias_list;
} program_data;

/**
* struct builtins - structure for the builtins
* @builtin: the name of the builtin
* @function: the associated function to be called for each builtin
*/
typedef struct builtins
{
char *builtin;
int (*function)(program_data *data);
} builtins;

/*2 add, remove or show aliases*/
int output_alias(program_data *data, char *alias);

/*2 get d alias*/
char *fetch_alias(program_data  *data, char *name);

/*2 add alias*/
int write_alias(char *string_alias, program_data *data);

/*2 allow 2 read a line frm cmd prompt*/
int _getlines(program_data * data);

/*2 check 4 logical operators nd split*/
int check_ops_logic(char *array_of_commands[], int m,
char array_of_operators[]);

/*exit prog wit status*/
int exit_builtin(program_data *data);

/*change wrking directory*/
int cd_builtin(program_data *data);

/*set wrking directory*/
int set_working_directory(program_data *data, char *new_dir);

/*show env of shell*/
int help_builtin(program_data *data);

/*aliases*/
int alias_builtin(program_data *data);

/*search nd execute builtins match*/
int list_of_builtins(program_data *data);

/*show shell env*/
int builtin_environment(program_data *data);

/*set env*/
int builtin_set_environment(program_data *data);

/*unset env*/
int builtin_unset_environment(program_data *data);

/*to free an array of pointers*/
void free_array_of_pointers(char **array);

/*to free all fields of a prog*/
void free_all_data(program_data *data);

/*to free d fields needed 4 each loop of a prog*/
void free_recurrent_data(program_data *data);

/*to execute cmd*/
int execution(program_data *data);

/*to expand variables*/
void variables_expansion(program_data *data);

/*to expand alias*/
void alias_expansion(program_data *data);

/*to append to buffer*/
int add_to_buffer(char *buffer, char *strings);

/*to check if file exists*/
int check_files(char *file_path);

/*to find prog*/
int finding_program(program_data  *data);

/*to tokenize*/
char **tokenize_paths(program_data *data);

/*2 converts a numb 2 a string type*/
void long_to_string(long number, char *string, int base);

/*2 convert a string of digits 2 an int*/
int _atoi(char *s);

/*2 count d coincidences of char in string*/
int count_characters(char *string, char *character);

/*2 write an array of chars in d stderr*/
int _print_error(int errorcode, program_data *data);

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
void inicialize_data(program_data *data, int argc, char *argv[], char **env);

/*An infinite loop dat shows d prompt*/
void sisifo(char *prompt, program_data *data);

/*2 separate strings wit delimiters*/
char *_strtok(char *line, char *delim);

char *environment_get_key(char *key, program_data *data);

int environment_set_key(char *key, char *value, program_data *data);

int environment_remove_key(char *key, program_data *data);

void print_environment(program_data *data);

void tokenize(program_data *data);

#endif
