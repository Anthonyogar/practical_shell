#include "shell.h"

/**
 * get_env_var - gets the value of an environment variable
 * @var_name: the name of the environment variable
 * @shell_data: struct containing shell data
 * Return: pointer to value of the variable or NULL if it doesn't exist
 */
char *get_env_var(char *var_name, shell_data *data)
{
	int i, var_len = 0;

	/* check for valid arguments */
	if (var_name == NULL || data->env == NULL)
		return (NULL);

	/* calculate length of variable name */
	var_len = str_length(var_name);

	for (i = 0; data->env[i]; i++)
	{/* iterate through env and check for matching variable name */
		if (str_compare(var_name, data->env[i], var_len) &&
		 data->env[i][var_len] == '=')
		{/* return value of variable when found */
			return (data->env[i] + var_len + 1);
		}
	}
	/* return NULL if variable not found */
	return (NULL);
}

/**
 * set_env_var - set the value of an environment variable
 * or create it if it does not exist
 * @var_name: name of the variable to set
 * @var_value: new value
 * @shell_data: struct containing shell data
 * Return: 1 if the parameters are NULL, 2 if there is an error, or 0 if success
 */
int set_env_var(char *var_name, char *var_value, shell_data *data)
{
	int i, var_len = 0, is_new_var = 1;

	/* check for valid arguments */
	if (var_name == NULL || var_value == NULL || data->env == NULL)
		return (1);

	/* calculate length of variable name */
	var_len = str_length(var_name);

	for (i = 0; data->env[i]; i++)
	{/* iterate through env and check for matching variable name */
		if (str_compare(var_name, data->env[i], var_len) &&
		 data->env[i][var_len] == '=')
		{/* if variable already exists, overwrite it */
			is_new_var = 0;
			/* free the entire variable and create it again */
			free(data->env[i]);
			break;
		}
	}
	/* create a string of the form key=value */
	data->env[i] = str_concat(str_duplicate(var_name), "=");
	data->env[i] = str_concat(data->env[i], var_value);

	if (is_new_var)
	{/* if the variable is new, create it at the end of the list and add a NULL terminator */
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * unset_env_var - remove an environment variable
 * @var_name: the name of the variable to remove
 * @shell_data: struct containing shell data
 * Return: 1 if the variable was removed, 0 if the variable does not exist
 */
int unset_env_var(char *var_name, shell_data *data)
{
	int i, var_len = 0;

	/* check for valid arguments */
	if (var_name == NULL || data->env == NULL)
		return (0);

	/* calculate length of variable name */
	var_len = str_length(var_name);

	for (i = 0; data->env[i]; i++)
	{/* iterate through env and check for matching variable name */
		if (str_compare(var_name, data->env[i], var_len) &&
		 data->env[i][var_len] == '=')
		{/* if variable exists, free its memory and shift the other variables down in the array */
			free(data->env[i]);
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			data->env[i - 1] = NULL;
			return (1);
		}
	}	

	/* if variable does not exist, return 0 */
	return (0);
}

/**
 * print_environ - prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */
void print_environ(data_of_program *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
