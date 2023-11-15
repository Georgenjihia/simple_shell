#include "shell.h"
/**
 * listLength - gets the length of a singly
 * linked list
 *
 * @h: pointer to the head node
 *
 * Return: length of the linked list
 *
 */
size_t listLength(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * listStrings - returns an array of strings of the
 * linked list
 *
 * @head: contains the address of the head node
 *
 * Return: array of strings
 *
 */
char **listStrings(list_t *head)
{
	list_t *node = head;
	size_t i = listLength(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * printList - print all components of list_t linked list
 *
 * @h: contains address of the first node
 *
 * Return: all components of a list
 *
 */
size_t printList(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string starts with
 *
 * @node: pointer to he head node
 *
 * @prefix: string to match
 *
 * @c: character
 *
 * Return: node whose string starts with prefix
 *
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getIndexnode - gets the index of a node
 *
 * @head: pointer to head node
 *
 * @node: node whose index is to be determined
 *
 * Return: index of the node
 *
 */
ssize_t getIndexnode(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
