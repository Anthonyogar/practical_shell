#include "shell.h"
/**
 * str_length - Counts the number of characters of a string
 *
 * @string: The string to count
 *
 * Return: The length of the string
 */
int str_length(char *string);
{
	int length = 0;

	while (string[length])
		length++;

	return (length);
}

/**
 * str_duplicate - Duplicates an string
 *
 * @string: The string to duplicate
 *
 * Return: The duplicated string
 */
char *str_duplicate(char *string)
{
	int length = str_length(string);
	char *duplicate = malloc(sizeof(char) * (length + 1));

	if (!duplicate)
		return (NULL);

	int g;

	for (g = 0; g < length; g++)
		duplicate[g] = string[g];

	duplicate[length] = '\0';

	return (duplicate);
}

/**
 * str_concat - Concatenates two strings
 *
 * @string1: The first string
 * @string2: The second string
 *
 * Return: A new string that is the result of
 * the concatenation of the two strings
 */
char *str_concat(char *string1, char *string2)
{
	int length1 = str_length(string1);
	int length2 = str_length(string2);
	int k, m;
	char *concat = malloc(sizeof(char) * (length + length2 + 1));

	if (!concat)
		return (NULL);

	for (k = 0; k < length1; k++)
		concat[k] = string[k];

	for (m = 0; m < length2; m++)
		concat[k + m] = string2[m];

	concat[k + m] = '\0';

	return (concat);
}

/**
 * str_compare - Compares two strings
 *
 * @string1: The first string to compare
 * @string2: The second string to compare
 * @number: The number of characters to compare
 *
 * Return: 1 if the strings are equal, 0 otherwise
 */
int str_compare(char *string1, char *string2, int number)
{
	int d;

	for (d = 0; d < number; d++)
	{
		if (string[d] != string2[d])
			return (0);
	}

	return (1);
}

/**
 * str_reverse - Reverse a string
 *
 * @string: The string to reverse
 */
void str_reverse(char *string)
{
	int h = 0;
	int b = str_length(string) - 1;

	while (h < b)
	{
		char temp = string[h];

		string[h] = string[b];
		string[b] = temp;

		h++;
		b++;
	}
}
