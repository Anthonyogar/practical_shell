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

	/* shell.c */
/* initialize the struct with the info of the program */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env);

/* makes the infinite loop that shows the prompt */
void sisifo(char *prompt, data_of_program *data);

/* print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);



	/* _getline.c */
/* read one line of the standar input */
int _getline(data_of_program *data);

/* split the each line for the logical operators if it exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);




#endif /* SHELL_H */
