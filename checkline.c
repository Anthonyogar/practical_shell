#include "shell.h"

/**
 * get_input_line - reads one line of the standard input
 * @data: pointer to the struct containing the data of the program
 *
 * Retrun: the line read from the standard input
 */
int get_input_line(shell_data *data)
{
	char buff[BUFFER_SIZE];
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read;
	int i;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
        (array_operators[0] == '|' && errno == 0))
	{
        	for (i = 0; array_commands[i]; i++)
		{
            		free(array_commands[i]);
            		array_commands[i] = NULL;
		}

		bytes_read = read(data->file_descriptor, buff, BUFFER_SIZE - 1);

		if (bytes_read == 0)
		{
			return -1;
		}

		i = 0;

		 do {
			  array_commands[i] = strdup(strtok(i ? NULL : buff, "\n;"));
			  i = check_logical_operators(array_commands, i, array_operators);
		 } while (array_commands[i++]);
	}

	data->input_line = array_commands[0];

	for (i = 0; array_commands[i]; i++)
	{
		 array_commands[i] = array_commands[i + 1];
		 array_operators[i] = array_operators[i + 1];
	}

	return strlen(data->input_line);
}



/**
 * check_logic_operators - split each line for the logical
 * operators if it exists
 * @array_commands: array of commands
 * @i: current position of the array
 * @array_operators: array of logical operators
 *
 * Return: new position of the array_commands
 */
int check_logical_operators(char *array_commands[], int i, char array_operators[])
{
	char *temp;
	int j;

	 for (j = 0; array_commands[i] && array_commands[i][j]; j++)
	 {
		 if (array_commands[i][j] == '&' && array_commands[i][j + 1] == '&')
		 {
			temp = array_commands[i];
            		array_commands[i][j] = '\0';
            		array_commands[i] = strdup(array_commands[i]);
            		array_commands[i + 1] = strdup(temp + j + 2);
            		i++;
            		array_operators[i] = '&';
            		free(temp);
			j = 0;
		 }
		 if (array_commands[i][j] == '|' && array_commands[i][j + 1] == '|')
		 {
			temp = array_commands[i];
           		array_commands[i][j] = '\0';
            		array_commands[i] = strdup(array_commands[i]);
            		array_commands[i + 1] = strdup(temp + j + 2);
            		i++;
            		array_operators[i] = '|';
            		free(temp);
            		j = 0;
		 }
	 }

	 return i;return i;
}
