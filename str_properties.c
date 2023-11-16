#include "shell.h"

/**
 * _strncpy - copies a string
 *
 * @destination: the destination
 *
 * @source: source
 *
 * @n: amount of chars to be copied
 *
 * Return: the copied string
 *
 */
char *_strncpy(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * *_strncat - concatenates 2 strings
 *
 * @destination: destination
 *
 * @source: source
 *
 * @n: amount of bytes to be used
 *
 * Return: concatenated string
 *
 */
char *_strncat(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (s);
}

/**
 * _strchr - locates a character in a string
 *
 * @s: string
 *
 * @c: character
 *
 * Return: pointer to the memory area
 *
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

