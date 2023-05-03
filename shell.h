#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>

#define BUFSIZE 1024
#define MAX_ARGS 128
#define INTERACTIVE_ERRNO 42
#define PROMPT_MSG "$ "

/**
 * struct shell_data - data needed for the execution of the shell
 * @environ: environment variables
 * @args: arguments
 * @commands: list of commands
 * @buffer: line read from standard input
 * @prompt: shell prompt
 * @exit_status: exit status
 */

#include "macros.h" /* for msg help and prompt */

typedef struct shell_data
{
	char **environ;
	char **args;
	char **commands;
	char *buffer;
	char *prompt;
	int exit_status;
} shell_data;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each
 * builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(shell_data *data);
} builtins;

/* main functions */
int main(int argc, char *argv[], char *env[]);
void handle_ctrl_c(int opr UNUSED);
void initialize_shell_data(Shell_data *data, int argc, char *argv[], char **env;
void run_shell_loop(char *prompt, Shell_data *data);

/* checkline.c */
int _getline(shell_data *data);
int check_logic_ops(char *array_commands[], int i, char array_operators[]);

/* expansions.c */
void expand_variables(shell_data *data);
void expand_alias(shell_data *data);
int buffer_add(char *buffer, char *str_to_add);

/* builtins_list.c */
int (*find_builtin(shell_data *data))(shell_data *);
int run_builtin(shell_data *data);

/* shell_utils.c */
void tokenize(shell_data *data);
char *custom_strtok(char *str, const char *delim);

/* execute.c */
int execute(shell_data *data);

/* find_program_path.c */
char **tokenize_path(shell_data *data);
int find_shell_command(shell_data *data);

/* memory management helpers */
void free_array_of_pointers(char **directories);
void free_recurrent_data(shell_data *data);
void free_all_data(shell_data *data);

/* builtins */
int builtin_exit(shell_data *data);
int builtin_cd(shell_data *data);
int set_work_directory(shell_data *data, char *new_dir);
int builtin_help(shell_data *data);
int builtin_alias(shell_data *data);
int builtin_env(shell_data *data);
int builtin_set_env(shell_data *data);
int builtin_unset_env(shell_data *data);

/* environment variables management helpers */
char *get_env_var(char *var_name, shell_data *data);
int set_env_var(char *var_name, char *var_value, shell_data *data);
int unset_env_var(char *var_name, shell_data *data);
void print_shell_env(shell_data *data);

/* printing helpers */
int print_to_stdout(char *string);
int print_to_stderr(char *string);
int print_error(int errorcode, shell_data *data);

/* string management helpers */
int shell_str_length(char *string);
char *shell_str_duplicate(char *string);
int shell_str_compare(char *string1, char *string2, int number);
char *shell_str_concat(char *string1, char *string2);
void shell_str_reverse(char *string);


/* helpers_numbers.c */
void convert_long_to_string(long number, char *string, int base);
int convert_string_to_int(char *s);
int count_occurrences(char *string, char *character);

/*alias_management.c */
int print_alias(shell_data *data, char *alias);
char *get_alias(shell_data *data, char *alias);
int set_alias(char *alias_string, shell_data *data);


#endif /* SHELL_H */

