#include "shell.h"

/**
 * builtins_list - checks if the command matches a built-in
 *                 and excutes it
 * @data: struct containing the program's data
 *
 * Return: the return value of the executed built-in function
 * if there is a match, otherwise returns -1
 */
int builtins_list(data_of_program *data)
{
	int i;
	builtins options[] =
	{
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtins_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env}
		{NULL, NULL}
	};

	/* check if the command matches a built-in */
	for (i = 0; options[i].builtin != NULL; i++)
	{
		if (str_compare(options[i].builtin, data->command_name, 0))
		{
			/* execute the built-in and return its return value */
			return (options[i].functions(data));
		}
	}

	/* no match found */
	return (-1);
}
