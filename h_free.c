#include "shell.h"

/**
 * free_recurrent_data - frees the fields needed for each loop iteration
 * @data: struct of the shell's data
 * Return: void
 */
void free_recurrent_data(shell_data *data)
{
	if (data->tokens) {
		free_array_of_pointers(data->tokens);
		data->tokens = NULL;
	}
	if (data->input_line) {
		free(data->input_line);
		data->input_line = NULL;
	}
	if (data->command_name) {
		free(data->command_name);
		data->command_name = NULL;
	}
}

/**
 * free_all_data - frees all fields of the shell's data
 * @data: struct of the shell's data
 * Return: void
 */
void free_all_data(shell_data *data)
{
	if (data->file_descriptor != 0) {
		if (close(data->file_descriptor)) {
			perror(data->program_name);
		}
	}

	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - frees each pointer of an array of pointers and the
 * array itself
 * @array: array of pointers
 * Return: void
 */
void free_array_of_pointers(char **array)
{
	int i;

	if (array != NULL) {
		for (i = 0; array[i] != NULL; i++) {
			free(array[i]);
			array[i] = NULL;
		}
		free(array);
		array = NULL;
	}
}
