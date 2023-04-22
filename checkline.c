#include "shell.h"

/**
 * _getline - reads one line of the standard input
 * @data: pointer to the struct containing the data of the program
 *
 * Retrun: the line read from the standard input
 */
int _getline(data_of_program *data)
{
	char *line = NULL;
	size_t len = 0;

	data->line_read = getline(&line, &len, stdin);

	if (data->line_read == 1)
		return (data->line_read);

	/* remove trailing newline */
	line[data->line_read - 1] = '\0';

	data->line = line;

	return (data->line_read);
}

/**
 * check_logic_ops - split each line for the logical
 * operators if it exists
 * @array_commands: array of commands
 * @i: current position of the array
 * @array_operators: array of logical operators
 *
 * Return: new position of the array_commands
 */
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	int k, j, len;
	char *p, *temp;

	p = array_commands[i];
	len = _strlen(p);

	for (j = 0; array_operators[j]; j++)
	{
		temp = array_operators + j;
		k = _strlen(temp);

		if (len > k && !_strncmp(p + len - k, temp, k))
		{
			array_commands[i] = strndup(p, len - k);
			array_commands[i + 1] = _strndup(p + len - k + 1);

			if (!array_commands[i] || !array_commands[i + 1])
			{
				perror("check_logic_ops: malloc failed");
				exit(EXIT_FAILURE);
			}

			free(p);
			return (i + 1);
		}
	}

	return (i);
}
