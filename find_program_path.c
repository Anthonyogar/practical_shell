#include "shell.h"

int check_file(char *full_path);

/**
 * tokenize_path - tokenize PATH  varaible and store each
 *                 directory in a array
 * @data:pointer to the data struct
 *
 * Return: array of directories in PATH variable or NULL
 * on failure
 */
char **tokenize_path(data_of_program *data)
{
	char *path_env *path_cpy, *dir, **path_dirs;
	int num_dirs = 0, i;

	path_env = _getenv("PATH", data->env);
	if (!path_env)
		return (NULL);

	path_cpy = strdup(path_env);
	if (!path_cpy)
		return (NULL);

	/* count number of directories in PATH */
	for (i = 0; path_cpy[i]; i++)
	{
		if (path_cpy[i] == ':')
			num_dirs++;
	}

	num_dirs++; /* add one for last directory */

	path_dirs = malloc(sizeof(char *) * num_dirs);
	if (!path_dirs)
	{
		free(path_cpy);
		return (NULL);
	}

	dir = _strtok(path_cpy, ":");
	for (i = 0; dir; i++)
	{
		path_dirs[i] = dir;
		dir = _strtok(NULL, ":");
	}
	/* terminate array with NULL */
	path_dirs[i] = NULL;

	free(path_cpy);
	return (path_dirs);
}

/**
 * find_program - search for a program in each directory of PATH variable
 * @data: pointer to the data struct
 *
 * Return: 0 on success, 1 if program not found, -1 on failure
 */
int find_program(data_of_program *data)
{
	char **path_dirs, *program_path;
	int i, program_found = 0;

	path_dirs = tokenize_path(data);
	if (!path_dirs)
		return (-1);

	for (i = 0; path_dirs[i]; i++)
	{
		program_path = str_concat(path_dirs[i], "/", data->command_name);
		if (!program_path)
			goto cleanup;

		if (access(program_path, X_OK) == 0)
		{
			data->program_path = program_path;
			proggram_found = 1;
			break;
		}
		free(program_path);
	}

cleanup:
	free_str_array(path_dirs);

	if (!program_found)
	{
		/* program not found in PATH */
		print_error(data, "%s: command not found\n", data->command_name);
		return (1);
	}
	else if (!data->program_path)
	{
		/* error occurred */
		print_error(data, NULL);
		return (-1);
	}

	return (0);
}

/**
 * check_file - checks if a file exists
 * @full_path: the full path to file
 *
 * Return: 1  if the file exist, 0 otherwise
 */
int check_file(char *full_path)
{
	if (access(full_path, F_OK) != -1)
		return (1);
	return (0);
}
