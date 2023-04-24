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

/**
 * _strtok - creates a pointer to a part of a string
 * @line: the string to be parsed
 * @delim: the delimiter used to separate the string
 *
 * Return: a pointer to the first character of the next token
 */
char *_strtok(char *line, char *delim)
{
	/* the last token returned by _strtok */
	static char *last_token;
	/* the token to be returned */
	char *token;
	/* pointer to the delimiter in the string */
	char *delim_ptr;

	*last_token = NULL;

	/* if line is not NULL, set last_token to line */
	if (line)
		last_token = line;

	/* if last_token is NULL, return NULL */
	if (!last_token)
		return (NULL);

	/* set token to last_token */
	token = last_token;

	/* find the next occurences of the delimiter */
	delim_ptr = _strpbrk(token, delim);

	/* if the delimiter was found, replace it with a null character */
	if (delim_ptr)
	{
		*delim_ptr = '\0';
		last_token = delim_ptr + 1;
	}
	/* if the delimiter was not found, set last_token to NULL */
	else
	{
		last_token = NULL;
	}

	/* return the token */
	return (token);
}
