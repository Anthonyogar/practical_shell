#include "shell.h"

/**
 * _strtok - creates a pointer to a part of a string
 * @line: the string to be parsed
 * @delim: the delimiter used to separate the string
 *
 * Return: a pointer to the first character of the next token
 */
char *_strtok(char *line, char *delim)
{
	static char *last_token; /* The last token returned by _strtok */
	char *token; /* The token to be returned */
	char *delim_ptr; /* Pointer to the delimiter in the string */

	/* If line is not NULL, set last_token to line */
	if (line)
		last_token = line;

	/* If last_token is NULL, return NULL */
	if (!last_token)
		return (NULL);

	/* Set token to last_token */
	token = last_token;

	/* Find the next occurrence of the delimiter */
	delim_ptr = _strpbrk(token, delim);

	/* If the delimiter was found, replace it with a null character */
	if (delim_ptr)
	{
		*delim_ptr = '\0';
		last_token = delim_ptr + 1;
	}
	else /* If the delimiter was not found, set last_token to NULL */
	{
		last_token = NULL;
	}

	/* Return the token */
	return (token);
}
