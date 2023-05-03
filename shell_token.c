#include "shell.h"

/**
 * tokenize - splits the input string into tokens using a specified delimiter
 * @shell_data: a pointer to the shell's data
 */
void tokenize(shell_data *data)
{
	char *delim = " \t";
	int i, j, num_tokens = 2, input_len;

	input_len = str_length(shell_data->input_line);
	if (input_len > 0 && shell_data->input_line[input_len - 1] == '\n')
	{
		shell_data->input_line[input_len - 1] = '\0';
	}

	for (i = 0; shell_data->input_line[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (shell_data->input_line[i] == delim[j])
				num_tokens++;
		}
	}

	shell_data->tokens = malloc(num_tokens * sizeof(char *));
	if (shell_data->tokens == NULL)
	{
		perror("malloc");
		exit(errno);
	}

	i = 0;
	shell_data->tokens[i] = str_duplicate(_strtok(shell_data->input_line, delim));
	shell_data->command_name = str_duplicate(shell_data->tokens[0]);

	while (shell_data->tokens[i++])
	{
		shell_data->tokens[i] = str_duplicate(_strtok(NULL, delim));
	}
}
