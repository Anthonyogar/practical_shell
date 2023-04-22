#include "shell.h"

/**
 * main - initialize the variables of the program
 * @argc: number of values recieved from the command line
 * @argv: values recived from the command line
 * @env: number of values recieved from the command line
 *
 * Return: 0 on success, non-zero on failure
 */
int main(int argc, char *argv[], char *env[])
{
	/* declare the data structure and set the pointer */
	data_of_program data_structure = {NULL}, *data = &data_struct;
	/* declare an empty prompt string */
	char *prompt = "";

	/* initialize the data structure with program info */
	initialize_data(data, argc, argv, env);

	/* register signal handleer for SIGINT */
	signal(SIGINT, handle_ctrl_c);

	/*Check if we are in the interactive mode in a terminal */
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		/* set errno to a custom value to indicate inteeractive mode */
		errno = INTERACTIVE_ERRNO;
		/* set the prompt to default prompt message */
		prompt = DEFAULT_PROMPT;
	}

	/* reset errno to 0 */
	errno = 0;

	/* start the main loop */
	sisifo(prompt. data);

	/* Return 0 to indicate success */
	return (0);
}

/**
 * initialize_data - initialize the struct with the info
 *                   of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments passed to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values recieved from the command line
 */

/* Initialixze the struct with the info of the program */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	data->environ = env;
	data->args = argv;
	data->commands = NULL;
	data->buffer = NULL;
	data->prompt = NULL;
	data->exit_status = 0;
}

/**
 * sisifo - its a infinte loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */

/* makes the infinite loop that shows the prompt */
void sisifo(char *prompt, data_of_program *data)
{
	size_t len = 0;
	ssize_t read = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("%s", prompt);

		read = getline(&(data->buffer), &len, stdin);

		if (read == 1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			exit(0);
		}

		/* remove trailing newline character */
		data->buffer[read - 1] = '\0';

		/* handle empty input */
		if (strcmp(data->buffer, "") == 0)
			continue;

		/* handle ctrl-C signal */
		signal(SIGINT, handle_ctrl_c);

		/* parse input and execute command */
		data->commands = parse_input(data->buffer);
		execute_command(data);
	}
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is sent to the program
 * @UNUSED: option of prorotype
 */

/* print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED)
{
	printf("\n");
	printf("%s", PROMPT);
	fflush(stdout);
}
