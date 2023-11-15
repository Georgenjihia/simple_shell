#include "shell.h"

/**
 * bfree - frees the address
 *
 * @ptr: addres of the pointer
 *
 * Return: 1 on success
 *
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
