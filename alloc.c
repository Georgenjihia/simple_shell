#include "shell.h"

/**
 * *_memset - fills memory with constant byte
 *
 * @s: pointer to memory area
 *
 * @b: bytes
 *
 * @n: amount of bytes
 *
 * Return: pointer to the memory
 *
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees a string of strings
 *
 * @pp: string of strings
 *
 * Return: no return
 *
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates memory
 *
 * @ptr: pointer to previous allocated memory
 *
 * @old_size: size of previous memory block
 *
 * @new_size: size of new memory block
 *
 * Return: pointer to new allocated memory
 *
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
