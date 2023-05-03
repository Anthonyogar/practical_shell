#include "shell.h"

/**
 * convert_long_to_string - converts a long number to a string.
 * @number: number to be converted to a string.
 * @string: buffer to store the resulting string.
 * @base: base to use for the conversion.
 *
 * Return: Nothing.
 */
void convert_long_to_string(long number, char *string, int base)
{
    int index = 0, in_negative = 0;
    long quotient = number;
    char letters[] = "0123456789abcdef";

    if (quotient == 0)
    {
        string[index++] = '0';
    }

    if (string[0] == '-')
    {
        in_negative = 1;
    }

    while (quotient)
    {
        if (quotient < 0)
        {
            string[index++] = letters[-(quotient % base)];
        }
        else
        {
            string[index++] = letters[quotient % base];
        }
        quotient /= base;
    }

    if (in_negative)
    {
        string[index++] = '-';
    }

    string[index] = '\0';
    reverse_string(string);
}

/**
 * convert_string_to_int - converts a string to an integer.
 *
 * @s: pointer to the string to be converted.
 * Return: integer value of the string, or 0 if the string is not a valid integer.
 */
int convert_string_to_int(char *s)
{
    int sign = 1;
    unsigned int number = 0;

    /* Analyze the sign */
    while (!('0' <= *s && *s <= '9') && *s != '\0')
    {
        if (*s == '-')
        {
            sign *= -1;
        }
        if (*s == '+')
        {
            sign *= +1;
        }
        s++;
    }

    /* Extract the number */
    while ('0' <= *s && *s <= '9' && *s != '\0')
    {
        number = (number * 10) + (*s - '0');
        s++;
    }

    return (number * sign);
}

/**
 * count_occurrences - counts the occurrences of a character in a string.
 *
 * @string: pointer to the string to be analyzed.
 * @character: character to be counted.
 * Return: number of occurrences of the character in the string.
 */
int count_occurrences(char *string, char *character)
{
    int i = 0, counter = 0;

    for (; string[i]; i++)
    {
        if (string[i] == character[0])
        {
            counter++;
        }
    }

    return (counter);
}
