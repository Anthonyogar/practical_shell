#include "shell.h"

/**
 * find_builtin - searches for a match between the given command and a builtin
 * @data: pointer to a struct containing the program's data
 *
 * Return: a pointer to the matched builtin function or NULL if there's no match
 **/
int (*find_builtin(shell_data *data))(shell_data *)
{
	int i;
	builtin_t builtins[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; builtins[i].name != NULL; i++)
	{
		if (str_compare(data->command_name, builtins[i].name, 0))
			return (builtins[i].function);
	}
	return (NULL);
}

/**
 * run_builtin - executes the matched builtin function
 * @data: pointer to a struct containing the program's data
 *
 * Return: the return value of the executed function or -1 if there's no match
 **/
int run_builtin(shell_data *data)
{
	int (*builtin)(shell_data *);

	builtin = find_builtin(data);
	if (builtin != NULL)
		return (builtin(data));
	return (-1);
}
