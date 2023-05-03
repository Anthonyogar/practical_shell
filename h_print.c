#include "shell.h"

/**
 * _print - Prints a string to the standard output
 *
 * @string: The string to be printed
 *
 * Return: The number of characters printed
 */

int _print(char *string)
{
	int f = 0;

	while (string && string[f])
		f++;

	return (write(STDOUT_FILENO, string, f));
}

/**
 * _print_error - Prints an error message to the standard error
 *
 * @errorcode: The error code to be printed
 *
 * @data: A pointer to the data_of_program struct
 *
 * Return: The number of characters printed
 */

int _print_error(int errorcode, data_of_program *data)
{
	char *error_msg;

	switch (errorcode)
	{
		case ERROR_EXIT_OF_RANGE:
			error_msg = "exit: Illegal number: ";
			break;
		case ERROR_EXIT_TOO_MANY_ARGS:
			error_msg = "exit: too many arguments\n";
			break;
		case ERROR_INVALID_ARG:
			error_msg = "exit: Illegal number: ";
			break;
		case ERROR_CD_NO_FILE:
			error_msg = "cd: can't cd to ";
			break;
		case ERROR_CD_TOO_MANY_ARGS:
			error_msg = "cd: too many arguments\n";
			break;
		case ERROR_ENV_NO_FILE:
			error_msg = ": No such file or directory\n";
			break;
		case ERROR_SETENV_TOO_MANY_ARGS:
			error_msg = "setenv: too many arguments\n";
			break;
		case ERROR_UNSETENV_TOO_FEW_ARGS:
			error_msg = "unsetenv: Too few arguments.\n";
			break;
		default:
			return (0);
	}

	_printe(data->argv[0]);
	_printe(": ");

	if (errorcode == ERROR_EXIT_OUT_OF_RANGE ||
			errorcode == ERROR_EXIT_INVALID_ARG)
		printe(error_message);

	_printe(error_message);
	_printe(data->args[1]);
	_printe("\n");

	return (0);
}

/**
 * _printe - Prints a string to the standard error
 *
 * @string: The string to be printed
 *
 * Return: The number of characters printed
 */
int _printe(char *string)
{
	int r = 0;

	while (string && string[r])
		r++;

	return (write(STDERR_FILENO, string, r));
}
