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

/* initialize the struct with the info of the program */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env);

/* makes the infinite loop that shows the prompt */
void sisifo(char *prompt, data_of_program *data);

/* print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);




#endif /* SHELL_H */
