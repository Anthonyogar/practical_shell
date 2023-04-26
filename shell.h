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
#include <sys/types.H>
#include <errno.h>
#include <stddef.h>

#define BUFSIZE 1024

/**
 * struct data_of_program - data needed for the execution of the program
 * @input_buffer: buffer to hold user input
 * @commands: array of pointers to hold individual commands
 * @env: pointer to environment
 * @status: exit status
 */

#include "macros.h" /* for msg help and prompt */

/* data of the program struct */
typedef struct data_of_program
{
	char **environ; /* Enviroment variables */
	char **args; /* Arguments */
	char **commands; /* list of commands */
	char *buffer; /* line read from standard input */
	char *prompt; /* shell prompt */
	int exit_status; /* exit status */
} data_of_program;


/**
 * struct builtins - struct for the builtins
 * @builtin: the name oth the builtin
 * @function: the associated function to be called for each
 * builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;

			/************* MAIN FUNCTIONS *************/

	/* shell.c */
/* initialize the struct with the info of the program */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env);

/* makes the infinite loop that shows the prompt */
void sisifo(char *prompt, data_of_program *data);

/* print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);



	/* checkline.c */
/* read one line of the standar input */
int _getline(data_of_program *data);

/* split the each line for the logical operators if it exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


	/* expansions.c */
/* expand variables */
void expand_variables(data_of_program *data);

/* expand aliases */
void expand_alias(data_of_program *data);

/* append the string to the end of the buffer */
int buffer_add(char *buffer, char *str_to_add);


	/* builtins_list.c */
/* checks if the command matches a built-in and excutes it */
int builtins_list(data_of_program *data);

	/* shell_utils.c */
/* Separate the string in tokens using a designed delimiter */
void tokenize(data_of_program *data);

/* Creates a pointer to a part of a string */
char *_strtok(char *line, char *delim);


	/* execute.c */
/* Execute a command with its entire path */
int execute(data_of_program *data);


	/* find_program_path.c */
/* Creates an array of the path directories */
char **tokenize_path(data_of_program *data);

/* Search for program in path */
int find_program(data_of_program *data);


			/************** HELPERS FOR MEMORY MANAGEMENT **************/


	/* h_free.c */
/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed each loop */
void free_recurrent_data(data_of_program *data);

/* Free all field of the data */
void free_all_data(data_of_program *data);


			/************** BUILTINS **************/


	/* builtins.c */
/* Close the shell */
int builtin_exit(data_of_program *data);

/* Change the current directory */
int builtin_cd(data_of_program *data);

/* set the work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* show help information */
int builtin_help(data_of_program *data);

/* set, unset and show alias */
int builtin_alias(data_of_program *data);


	/* builtins_env.c */
/* Shows the environment where the shell runs */
int builtin_env(data_of_program *data);

/* create or override a variable of environment */
int builtin_set_env(data_of_program *data);

/* delete a variable of environment */
int builtin_unset_env(data_of_program *data);


			/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/
	/* env_management.c */
/* Gets the value of an environment variable */
char *env_get_key(char *name, data_of_program *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, data_of_program *data);

/* Remove a key from the environment */
int env_remove_key(char *key, data_of_program *data);

/* prints the current environ */
void print_environ(data_of_program *data);


#endif /* SHELL_H */
