#include "shell.h"
/**
 * builtin_exit - closes the shell
 * @data: struct for the program's data
 * Return: always returns 0.
 */
int builtin_exit(data_of_program *data)
{
	free_all_data(data);
	exit(EXIT_SUCCESS);
}

/**
 * builtin_cd - changes the current directory
 * @data: struct for the program's data
 * return: returns 0 on success, -1 on error.
 */
int builtin_cd(data_of_program *data)
{
	char *new_dir;

	if (data->arguments[1] == NULL)
	{
		new_dir = search_env(data->env, "HOME");
		if (new_dir == NULL)
		{
			print_error(data->program_name, NULL, "cd", ERR_NOHOME);
			return (-1);
		}
	}
	else if (_strcmp(data->arguments[1], "-") == 0)
	{
		new_dir = search_env(data->env, "OLDPWD");
		if (new_dir == NULL)
		{
			print_error(data->program_name, NULL, "-", ERR_NOPWD);
			return (-1);
		}
		write(STDOUT_FILENO, new_dir, _strlen(new_dir));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		new_dir = strdup(data->arguments[1]);
		if (new_dir == NULL)
		{
			print_error(data->program_name, NULL, data->arguments[1], ERR_MALLOC);
			return (-1);
		}
	}

	if (set_work_directory(data, new_dir) == -1)
	{
		free(new_dir);
		return (-1);
	}
}

/**
 * set_work_directory - set  the work directory
 * @data: struct for the program's data
 * @new_dir: the new directory to change to
 *
 * Return: returns 0 on success, -1 on error
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char *current_dir;

	if (chdir(new_dir) == -1)
	{
		print_error(data->program_name, NULL, new_dir, ERR_NOENT);
		return (-1);
	}

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		print_error(data->program_name, NULL, NULL, ERR_GETCWD);
		return (-1);
	}

	if (set_env(data->env, "OLDPWD", search_env(data->env, "PWD")) == -1 ||
	    set_env(data->env, "PWD", current_dir) == -1)
	{
		print_error(data->program_name, NULL, NULL, ERR_SETENV);
		return (-1);
	}

	free(current_dir);
	return (0);
}

/**
 * builtin_help - shows help information
 * @data: struct for the program's data
 * Return: always return 0
 */
int builtin_help(data_of_program *data)
{
	write(STDOUT_FILENO, HELP_MSG, _strlen(HELP_MSG));
	return (0);
}

/**
 * builtin_alias - create, unset or show aliases
 * @data: data structure with information
 *
 * Return: 0 on success, 1 on failure
 */
int builtin_alias(data_of_program *data)
{
	alias_t *alias = data->aliases;

	if (data->arguments[1] == NULL)
	{
		print_alias(alias);
		return (0);
	}

	if (_strcmp(data->arguments[1], "-d") == 0)
	{
		if (data->arguments[2] == NULL)
			return (_puterror(data, "Usage: unalias NAME\N", 1));

		delete_alias(alias, data->arguments[2]);
		return (0);
	}

	if (data->arguments[2] == NULL)
	{
		add_alias(alias, data->arguments[1], "");
		return (0);
	}

	if (add_alias(alias, data->arguments[1], data->arguments[2]
