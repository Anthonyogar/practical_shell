#include "shell.h"
/**
 * tokenize - separate the string in tokens using a designed delimiter
 * @data: struct for the program's data
 */
void tokenize(data_of_program *data)
{
	char *token;

	/* allocate memory for the token array */
	data->tokens = malloc(sizeof(char *) * (data->tokens_size + 1));

	/* check if allocation succeed */
	if (!data->tokens)
	{
		perror("malloc");
		exit(errno);
	}

	/* call strktok to get the first token */
	token = _strtok(data->line, TOK_DELIM);

	/* loop through the rest of the tokens */
	while (token != NULL)
	{
		/* add the token to  the token array */
		data->tokens[data->tokens_count++] = token;

		/* check if we need to allocate more memory for the token array */
		if (data->tokens_count >= data->tokens_size)
		{
			data->tokens_size += TOK_BUFFSIZE;
			data->tokens = realloc(data->tokens, sizeof(char *) * (data->tokens_size + 1));

			/* check if allocation succeeded */
			if (!data->tokens)
			{
				perror("realloc");
				exit(errno);
			}
		}

		/* call strtok again to get the nxt token */
		token = _strtok(NULL, TOK_DELIM);

	}

	/* set the last token to NULL */
	data->tokens[data->tokens_count] = NULL;
}
