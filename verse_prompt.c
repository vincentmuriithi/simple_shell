#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ALIASES 32
extern char **environ;

typedef struct {
    char *name;
    char *value;
} Alias;

Alias aliases[MAX_ALIASES];
int alias_count = 0;

int find_alias(const char *name) {
    int i;

    for (i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            return (i);
        }
    }
    return (-1);
}

void print_aliases(int argc, char *argv[]) {
    int i;

    if (argc == 1) {
        for (i = 0; i < alias_count; i++) {
            printf("alias %s='%s'\n", aliases[i].name, aliases[i].value);
        }
    } else {
        for (i = 1; i < argc; i++) {
            int alias_index = find_alias(argv[i]);
            if (alias_index != -1) {
                printf("alias %s='%s'\n", aliases[alias_index].name, aliases[alias_index].value);
            }
        }
    }
}

void define_alias(const char *name, const char *value) {
    int alias_index = find_alias(name);

    if (alias_index != -1) 
    {
        free(aliases[alias_index].name);
        free(aliases[alias_index].value);

        aliases[alias_index].name = strdup(name);
        aliases[alias_index].value = strdup(value);
    } else {
        if (alias_count < MAX_ALIASES) {
            aliases[alias_count].name = strdup(name);
            aliases[alias_count].value = strdup(value);
            alias_count++;
        } else {
            fprintf(stderr, "Too many aliases. Cannot define alias %s='%s'\n", name, value);
        }
    }
}

void handle_alias_command(char *command) {
    char *alias_args[32];
    int alias_count = custom_tokenize(command, alias_args, " ");
    int j;
    
    if (alias_count >= 2) {
        if (alias_count == 2) {
            print_aliases(1, alias_args);
        } else {
            for (j = 1; j < alias_count; j++) {
                char *alias_def = alias_args[j];
                char *name = alias_def;
                char *value = strchr(alias_def, '=');
                if (value != NULL) {
                    *value = '\0';
                    value++;
                    define_alias(name, value);
                }
            }
        }
    } else {
        fprintf(stderr, "Usage: alias [name[='value'] ...]\n");
    }
}

char* substitute_alias(char* input) {
    char* args[32];
    int count = custom_tokenize(input, args, " ");
    int i;
    char* substituted_input = NULL;

    for (i = 0; i < count; i++) {
        int alias_index = find_alias(args[i]);
        if (alias_index != -1) {
            free(args[i]);
            args[i] = strdup(aliases[alias_index].value);
        }
    }

    substituted_input = join_tokens(args, count, " ");
    return (substituted_input);
}

int main(void) {
    char *args[32];
    pid_t pid;
    int count = 0;
    int should_execute;
    char **env = NULL;
    char *path = getenv("PATH");
    char *input = NULL;
    char *status_str = NULL;
    int status = 0;
    char *setenv_args[3];
    int setenv_count = 0;
    char *unsetenv_args[2];
    int unsetenv_count = 0;
    char *home_dir = NULL;
    char *commands[32];
    int command_count = 0;
    char *command = NULL;
    int i;
    int j;

    if (path == NULL) {
        error_exit(1, "Failed to get PATH environment variable");
    }

    while (1) {
        printf("($) ");
        input = my_getline();
        input[strcspn(input, "\n")] = '\0';

        command_count = custom_tokenize(input, commands, ";");

        for (i = 0; i < command_count; i++) {
            command = commands[i];
            should_execute = 1;

            if (strcmp(command, "exit") == 0) {
                for (j = 0; j < alias_count; j++) {
                    free(aliases[j].name);
                    free(aliases[j].value);
                }
                exit(0);
            } else if (strncmp(command, "exit ", 5) == 0) {
                status_str = command + 5;
                status = atoi(status_str);
                for (j = 0; j < alias_count; j++) {
                    free(aliases[j].name);
                    free(aliases[j].value);
                }
                exit(status);
            } else if (strncmp(command, "setenv ", 7) == 0) {
                setenv_count = custom_tokenize(command, setenv_args, " ");

                if (setenv_count != 3) {
                    fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                } else {
                    if (setenv(setenv_args[1], setenv_args[2], 1) != 0) {
                        perror("setenv");
                    }
                }
            } else if (strncmp(command, "unsetenv ", 9) == 0) {
                unsetenv_count = custom_tokenize(command, unsetenv_args, " ");

                if (unsetenv_count != 2) {
                    fprintf(stderr, "Usage: unsetenv VARIABLE\n");
                } else {
                    if (unsetenv(unsetenv_args[1]) != 0) {
                        perror("unsetenv");
                    }
                }
            } else if (strncmp(command, "cd", 2) == 0) {
                count = custom_tokenize(command, args, " ");
                if (count > 1) {
                    if (change_directory(args[1]) != 0) {
                        fprintf(stderr, "cd: Unable to change directory\n");
                    }
                } else {
                    home_dir = getenv("HOME");
                    if (home_dir != NULL) {
                        if (change_directory(home_dir) != 0) {
                            fprintf(stderr, "cd: Unable to change directory\n");
                        }
                    }
                }
            } else if (strcmp(command, "env") == 0) {
                env = environ;
                while (*env) {
                    printf("%s\n", *env);
                    env++;
                }
            } else if (strncmp(command, "alias", 5) == 0) {
                handle_alias_command(command);
            } else {
                count = custom_tokenize(command, args, " ");

                if (strstr(command, "&&")) {
                    char *cmd1 = strtok(command, "&&");
                    char *cmd2 = strtok(NULL, "&&");
                    if (cmd1 && cmd2) {
                        int cmd1_status = execute_command(cmd1);
                        if (cmd1_status != 0) {
                            should_execute = 0;
                        }
                    }
                } else if (strstr(command, "||")) {
                    char *cmd1 = strtok(command, "||");
                    char *cmd2 = strtok(NULL, "||");
                    if (cmd1 && cmd2) {
                        int cmd1_status = execute_command(cmd1);
                        if (cmd1_status == 0) {
                            should_execute = 0;
                        }
                    }
                }
                if (should_execute) {
                    char* substituted_input = substitute_alias(command);
                    count = custom_tokenize(substituted_input, args, " ");
                    args[count] = NULL;
                    pid = fork();

                    if (pid == -1) {
                        perror("Fork failed");
                        for (j = 0; j < alias_count; j++) {
                            free(aliases[j].name);
                            free(aliases[j].value);
                        }
                        exit(1);
                    } else if (pid == 0) {
                        if (execvp(args[0], args) == -1) {
                            perror("Exec failed");
                            for (j = 0; j < alias_count; j++) {
                                free(aliases[j].name);
                                free(aliases[j].value);
                            }
                            exit(1);
                        }
                    } else {
                        int status;
                        waitpid(pid, &status, 0);
                        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                            printf("Command not found: %s\n", args[0]);
                        }
                    }

                    free(substituted_input);
                }
            }
        }
    }
    return (0);
}
