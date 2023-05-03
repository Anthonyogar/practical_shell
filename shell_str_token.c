#include "shell.h"

/**
 * custom_strtok - a function that separates strings with delimiters
 * @str: pointer to the string to be tokenized
 * @delim: pointer to the delimiter characters
 *
 * Return: a pointer to the next token found, or NULL if there are no more tokens
 */
char *custom_strtok(char *str, const char *delim)
{
	static char *token_start;
	char *token_end;

	if (str != NULL)
		token_start = str;

	if (*token_start == '\0')
		return (NULL);

	/* skip leading delimiter characters */
	while (*token_start && strchr(delim, *token_start))
		token_start++;

	/* no more tokens left */
	if (*token_start == '\0')
		return (NULL);

	token_end = token_start;

	/* find the end of the token */
	while (*token_end && !strchr(delim, *token_end))
		token_end++;

	/* mark the end of the token and move the pointer to the next character */
	if (*token_end)
		*token_end++ = '\0';

	return token_start;
}
