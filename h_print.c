#include "shell.h"

/**
 * print_to_stdout - writes a string to stdout
 * @string: pointer to the string to be written
 * Return: the number of bytes written, or -1 on error
 */
int print_to_stdout(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}

/**
 * print_to_stderr - writes a string to stderr
 * @string: pointer to the string to be written
 * Return: the number of bytes written, or -1 on error
 */
int print_to_stderr(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * print_error - writes an error message to stderr
 * @data: pointer to the program's data
 * @errorcode: the error code to print
 * Return: 0 on success, or -1 on error
 */
int print_error(int errorcode, shell_data *data)
{
	char exec_counter_str[10] = {'\0'};

	long_to_string((long) data->exec_counter, exec_counter_str, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		print_to_stderr(data->program_name);
		print_to_stderr(": ");
		print_to_stderr(exec_counter_str);
		print_to_stderr(": ");
		print_to_stderr(data->tokens[0]);
		if (errorcode == 2)
			print_to_stderr(": Illegal number: ");
		else
			print_to_stderr(": can't cd to ");
		print_to_stderr(data->tokens[1]);
		print_to_stderr("\n");
	}
	else if (errorcode == 127)
	{
		print_to_stderr(data->program_name);
		print_to_stderr(": ");
		print_to_stderr(exec_counter_str);
		print_to_stderr(": ");
		print_to_stderr(data->command_name);
		print_to_stderr(": not found\n");
	}
	else if (errorcode == 126)
	{
		print_to_stderr(data->program_name);
		print_to_stderr(": ");
		print_to_stderr(exec_counter_str);
		print_to_stderr(": ");
		print_to_stderr(data->command_name);
		print_to_stderr(": Permission denied\n");
	}
	return (0);
}
