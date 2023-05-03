#include "shell.h"

/**
 * env_get_key - Gets the value of an environment variable
 *
 * @name: The name of the environment variable to get
 * @data: A pointer to the data_of_program struct
 *
 * Return: The value of the environment variable,
 * or NULL if it does not exist
 */
char *env_get_key(char *name, data_of_program *data)
{
	size_t len;
	int a;

	if (!name || !date)
		return (NULL);

	len = str_length(name);

	for (a = 0; data->environ[a] != NULL; a++)
	{
		if (str_compare(data->environ[a], name, len) == 0
				&& data->environ[a][len] == '=')
		{
			return (data->environ[a] + len + 1);
		}
	}
	return (NULL);
}

/**
 * env_set_key - Overwrite the value of the environment variable
 *
 * @key: The name of the environment variable to set
 * @value: The new value for the environment variable
 * @data: A pointer to the data_of_program struct
 *
 * Return: 0 on success, or -1 if the key does
 * not exist or could not be set
 */
int env_set_key(char *key, char *value, data_of_program *data)
{
	size_t key_len, value_len;
	int b;
	char *new_env;

	if (!key || !value || !data)
		return (-1);

	key_len = str_length(key);
	value_len = str_length(value);

	for (b = 0; data->environ[a] != NULL; b++)
	{
		if (str_compare(data->environ[b], key, key_len) == 0 &&
				data->environ[i][key_len] == '=')
		{
			new_env = str_concat(str_concat(key, "="), value);

			if (new_env == NULL)
				return (-1);

			free(data->environ[i]);
			data->environ[i] = new_env;

			return (0);
		}
	}

	return (-1);
}

/**
 * env_remove_key - Remove a key from the environment
 *
 * @key: The name of the environment variable to remove
 * @data: A pointer to the data_of_program struct
 *
 * Return: 0 on success, or -1 if the key does not
 * exist or could not be removed
 */
int env_remove_key(char *key, data_of_program *data)
{
	size_t key_len;
	int j, i;

	if (!key || !data)
		return (-1);

	key_len = str_length(key);

	for (j = 0; data->environ[j] != NULL; j++)
	{
		if (str_compare(data->environ[j], key, key_len) == 0 &&
				data->environ[j][key_len] == '=')
		{
			free(data->environ[j]);

			for (i = j; data->environ[i] != NULL; i++)
			{
				data->environ[i] = data->environ[i + 1];
			}

			return (0);
		}
	}

	return (-1);
}

/**
 * print_environ - prints the current environ
 *
 * @data: A pointer to the data_of_program struct
 */
void print_environ(data_of_program *data)
{
	int v;

	if (!data)
		return;

	for (v = 0; data->environ[v]; v++)
		printf("%s\n", data->environ[v]);
}
