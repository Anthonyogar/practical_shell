#include "shell.h"
/**
 * _getenv - function that gets the value of an enviroment
 * @name: the name of the enviroment variable
 *
 * Return: a pointer to the value of the enviroment variable,
 *  or NULL if it does not exist
 */
char *_getenv(const char *name)
{
	char **env = environ;
	size_t name_len = strlen(name);

	while (*env != NULL)
	{
		if (_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			return &(*env)[name_len + 1];
		}
		env++;
	}

	return NULL;
}
/**
 * _strcat - function that concatenates two strings
 * @dest: the destination string
 * @src: the source string
 *
 * Return: a pointer to the resulting string
 */
char *_strcat(char *dest, const char *src)
{
	char *p = dest + _strlen(dest);

	while (*src != '\0')
	{
		*p++ *src++;
	}

	*p = '\0';

	return (dest);
}
