#include "shell.h"

/**
 * long_to_string - Casts a long number to a string
 *
 * @number: Number to cast
 * @string: Destination buffer for the string representation
 * @base: Base of the number (e.g. 10 for decimal)
 *
 * Description: The resulting string is stored in the given buffer.
 * The buffer must be big enough to store the resulting string,
 * including the null byte. The function supports casting
 * to different number bases, from base 2 to 36.
 */
void long_to_string(long number, char *string, int base)
{
	char *ptr = string, *ptr1 = string, tmp_char;
	long tmp_value;

	if (base < 2 || base > 36)
	{
		*string = '\0';
		return;
	}

	do {
		tmp_value = number;
		number /= base;
		*ptr++ =
		"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"
		[35 + (tmp_value - number * base)];
	} while (number);

	if (tmp_value < 0)
		*ptr++ = '-';
	*ptr-- = '\0';

	while (prt1 < ptr)
	{
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_chr;
	}
}

/**
 * count_characters - Counts the number of times
 * a character appears in a string
 *
 * @string: The string to search
 * @character: The character to count
 *
 * Return: The number of times the character appears in the string
 *
 * Description: Counts the number of times
 * a given character appears in a string.
 * The function is case-sensitive.
 */
int count_characters(char *string, char character)
{
	int count = 0;

	if (string == NULL)
		return (0);

	for (; *string != '\0'; string++)
		count += (*string == character);

	return (count);
}

/**
 * _atoi - Converts a string to an integer
 * @s: The string to convert
 *
 * Return: The integer value of the string
 *
 * Description: Skips leading white space
 * characters and supports the + and -
 * signs. Stops conversion when a
 * non-numeric character is found.
 */
int _atoi(char *s);
{
	int sgn = 1;
	int rslt = 0;

	while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
		s++;

	if (*s == '+' || *s == '-')
	{
		sgn  = (*s == '+') ? 1 : -1;
		s++;
	}

	while (*s >= '0' && *s <= '9')
	{
		rslt = rslt * 10 + (*s - '0');
		s++;
	}

	return (sgn * rslt);
}
