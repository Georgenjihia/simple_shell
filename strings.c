#include "shell.h"

/**
 * _strlen - determines the length of a string
 *
 * @s: string whose length is to be
 * determined
 *
 * Return: length of a string
 *
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - compares 2 strings
 *
 * @string1: first string
 *
 * @string2: second string
 *
 * Return: 0 if the string are the same
 *
 */
int _strcmp(char *string1, char *string2)
{
	while (string1 && string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * startString - checks if needle starts with haystack
 *
 * @haystack: string to be searched
 *
 * @needle: the string to be searched
 *
 * Return: NULL
 *
 */
char *startString(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates 2 strings
 *
 * @destination: the destinaton buffer
 *
 * @source: source buffer
 *
 * Return: pointer to destination buffer
 *
 */
char *_strcat(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*src)
		*destination++ = *source++;
	return (ret);
}
