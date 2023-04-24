#include "shell.h"
/**
 * expand_variables - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno
 */
/* expand variables */
void expand_variables(data_of_program *data)
{
	char *dollar_sign, *variables_value, *variable_name;
	char *command = data->line;
	char *expand_command = NULL;
	int new_size, expansion_length, index, i;

	/* find first occurrence of $ */
	dollar_sign = strchr(command, '$');
	while (dollar_sign != NULL)
	{
		/* check if $ is escaped */
		if (dollar_sign != command && *(dollar_sign - 1) == '\\')
		{
			dollar_sign = strchr(dollar_sign + 1, '$');
			continue;
		}

		/* get variable name */
		index = dollar_sign - command;
		variable_name = dollar_sign + 1;
		while (*variable_nmae != '\0' && *variable_name != ' ' && *variable_name != '\t')
		{
			variable_name++;
		}
		*variable_name = '\0';

		/* expand variable */
		variable_value = getenv(dollar_sign + 1);
		expansion_length = strlen(variable_value);
		new_size = strlen(command) + expansion_length - strlen(dollar_sign);
		expanded_command = malloc(new_size + 1);
		if (expanded_command == NULL)
		{
			perror("malloc error");
			exit(EXIT_FAILURE);
		}

		/* copy command before the variable */
		strncpy(expanded_command,  command, index);
		expanded_command[index] = '\0';

		/* copy variable value */
		strcat(expanded_command, variable_value);

		/* copy rest of command after variable */
		strcat(expanded_command, dollar_sign + strlen(variable_value) + 1);

		/* update command and free memory */
		free(command);
		command = expanded_command;

		/* update index and find next variable */
		index += expansion_length;
		dollar_sign = strchr(command + index, '$');
	}

	data->line = command;
}

/**
 * expand_alias - expans aliases
 * @data: a pointer to a struct of the programs's data
 *
 * Return: nothing, but sets errno
 */
/* expand aliases */
void expand_alias(data_of_program *data)
{
	char *alias_value;
	char *command = data->line;
	char *expanded_command = NULL;
	char *alias_name = strtok(command, " \t\n");
	int new_size;


	/* find alias */
	if (alias_name != NULL)
	{
		alias_value = search_alias(alias_name, data->aliases);
		if (alias_value != NULL)
		{
			/* expand alias */
			new_size = strlen(alias_value) + strlen(command) - strlen(alias_name);
			expand_command = malloc(new_size + 1);
			if (expanded_command == NULL)
			{
				perror("malloc error");
				exit(EXIT_FAILURE);
			}
			strcpy(expanded_command, alias_value);
			strcat(expanded_command, command + strlen(alias_name));
			free(command);
			command = expanded_command;
		}
	}

	data->line = command;
}

/**
 * buffer_add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno
 */
/* append the string to the end of the buffer */
int buffer_add(char *buffer, char *str_to_add)
{
	int buffer_len = strlen(buffer);
	int str_len = strlen(str_to_add);
	if (buffer_len + str_len >= BUFFER_SIZE - 1)
	{
		fprintf(stderr, "Error: buffer overeflow\n");
		return (-1);
	}

	strcat(buffer, str_to_add);
	return (buffer_len + str_len);
}
