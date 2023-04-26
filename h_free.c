#include "shell.h"
/**
 * free_array_of_pointers - frees the memory for an array of pointers
 * @directories: the array of pointers to free
 *
 * Return: nothing
 */
void free_array_of_pointers(char **directories)
{
	unsigned int i;

	/* loop theough each pointer in the array */
	for (i = 0; directories[i] != NULL; i++)
	{
		/* free the memory pointed in the array */
		free(directories[i]);
	}

	/* free the memory allocated for the array */
	free(directories);
}

/**
 * free_recurrent_data - frees the fields needed each loop
 * @data: the program's data structure
 *
 * Return: nothing
 */
void free_recurrent_data(data_of_program *data)
{
	/* free the command name string */
	free(data->command_name = NULL);

	/* reset the pointers for the next loop interation */
	data->command_name = NULL;
	data->args = NULL;
}

/**
 * free_all_data - frees all fields of the data structure
 * @data: the program's data structure
 *
 * Return: nothing
 */
void free_all_data(data_of_program *data)
{
	unsigned int i;

	/* free the command name string */
	free(data->command_name);

	/* free each string in the args array */
	for (i = 0; data->args[i] != NULL; i++)
	{
		free(data->args[i]);
	}

	/* free the memory allocated for the args array */
	free(data->args);

	/* free the alias list */
	free_alias_list(data->alias_list);

	/* free the memory allocated for the program's data structure */
	free(data);
}
