#include "shell.h"
/**
 * execute - execute a command with its entire path
 * @data: struct for the program's data
 *
 * Return: returns 0 on success, 1 on error
 */
int execute(data_of_program *data)
{
	struct stat file_stat;
	int status;

	if (data->command_namea == NULL)
		return (-1);

	if (stat(data-command_name, &file_stat) == 0)
	{
		if ((file_stat.st_mode & S_IFMT) == S_IFDIR)
			return (print_error(data, EISDIR));
		if (access(data->command_name, X_OK) == 0)
			return (execute_command(data));
		else
			return (print_error(data, EACCES));
	}

	if (find_path(data) == NULL)
		return (print_error(data, ENOENT));

	if (access(data->comman_path, X_OK) == 0)
	{
		status = execute_command(data);
		free(data->command_path);
		return (status);
	}
	else
	{
		free(data->command_path);
		return (print_error(data, EACCES));
	}
}
