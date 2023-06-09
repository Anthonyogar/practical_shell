#include "shell.h"

/**
 * main - initializes the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: zero on success.
 */
int main(int argc, char *argv[], char *env[])
{
	ShellData data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	initialize_shell_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	run_shell_loop(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initialize_shell_data - initializes the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments passed to the program execution
 * @env: environ passed to the program execution
 * @argc: number of values received from the command line
 */
void initialize_shell_data(Shell_data *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be read */
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
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}

/**
 * run_shell_loop - an infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: pointer to ShellData struct
 */
void run_shell_loop(char *prompt, Shell_data *data)
{
    int error_code = 0, string_len = 0;

    while (++(data->exec_counter))
    {
        _print(prompt);
        error_code = string_len = read_input(data);

        if (error_code == EOF)
        {
            cleanup_shell_data(data);
            exit(errno);
        }
        if (string_len >= 1)
        {
            expand_aliases(data);
            expand_variables(data);
            tokenize_input(data);
            if (data->tokens[0])
            {
                error_code = execute_command(data);
                if (error_code != 0)
                    print_error(error_code, data);
            }
            cleanup_recurrent_data(data);
        }
    }
}

