#include "shell.h"
/**
 * print_alias - prints the list of aliases or a specific alias
 * @data: A pointer to the data_of_program struct
 *
 * @alias: The name of the alias to print.
 * If NULL, all aliases are printed
 *
 * Return: 0 on success, 1 on failure
 */
int print_alias(data_of_program *data, char *alias)
{
	alias_t *tmp;

	if (!data)
		return (0);

	tmp = data->alias;

	if (alias == NULL)
	{
		while (tmp != NULL)
		{
			_print(tmp->alias_name);
			_print("='");
			_print(tmp->alias_cmd);
			_print("'\n");
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp != NULL)
		{
			if (_strcmp(tmp->alias_name, alias) == 0)
			{
				_print(tmp->alias_cmd);
				_print("\n");
				return (0);
			}
			tmp = tmp->next;
		}
		return (1);
	}
	return (0);
}

/**
 * get_alias - gets the value of an alias
 *
 * @data: A pointer to the data_of_program struct
 * @alias: The name of the alias to retrieve
 *
 * Return: A pointer to the alias command string,
 * NULL if not found
 */
char *get_alias(data_of_program *data, char *alias)
{
	alias_t *tmp;

	if (!date || !alias)
		return (NULL);

	tmp = data->alias;

	while (tmp != NULL)
	{
		if (_strcmp(tmp->alias_name, alias) == 0)
			return (tmp->alias_cmd);
		tmp = tmp->next;
	}

	return (NULL);
}

/**
 * set_alias - adds or updates an alias
 *
 * @alias_string: The string containing the
 * alias name and command
 *
 * @data: A pointer to the data_of_program struct
 *
 * Return: 0 on success, 1 on failure
 */
int set_alias(char *alias_string, data_of_program *data)
{
	char *alias_name, *alias_cmd;
	alias_t *tmp, *new_alias;

	if (!alias_string || !data)
		return (1);

	alias_name = strtok(alias_string, "=");

	if (!alias_name)
		return (1);

	alias_cmd = strtok(NULL, "=");

	if (alias_cmd)
		return (1);

	tmp = data->alias;

	while (tmp != NULL)
	{
		if (_strcmp(tmp->alias_name, alias_name) == 0)
		{
			free(tmp->alias_cmd);
			temp->alais_cmd = _strdup(alias_cmd);
			return (0);
		}
		tmp = tmp->next;
	}
	new_alias = malloc(sizeof(alias_t));

	if (!new_alias)
		return (1);
	new_alias->alias_name = _strdup(alias_name);
	if (!new_alias->alias_name)
		return (1);
	new_alias->alias_cmd = strdup(alias_cmd);
	if (!new_alias->alias_cmd)
		return (1);

	new_alias->next = data->alias;
	data->alias = new_alias;

	return (0);
}
