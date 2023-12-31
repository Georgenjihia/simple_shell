#include "shell.h"

/**
 * isChain - a function which checks if the current char
 * in buffer is a delimeter
 *
 * @info: parameter struct
 *
 * @buf: buffer
 *
 * @p: address of current position in the buffer memory
 *
 * Return: 1 on success(if chain delimeter)
 *
 */
int isChain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * checkChain - checks we should continue chaining
 * based on last status
 *
 * @info: parameter struct
 *
 * @buf: buffer
 *
 * @p: address of current position in buffer
 *
 * @i: start position of the buffer
 *
 * @len: length of the buffer
 *
 * Return: no return
 *
 */
void checkChain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replaceAlias - replaces aliases in a tokenized
 * string
 *
 * @info: parameter struct
 *
 * Return: 1 on success
 *
 */
int replaceAlias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replaceVars - replaces vars in a tokenized string
 *
 * @info: parameter struct
 *
 * Return: 1 on success
 *
 */
int replaceVars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			replaceString(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}

		if (!_strcmp(info->argv[i], "$$"))
		{
			replaceString(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceString(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->argv[i], _strdup(" "));
	}
	return (0);
}

/**
 * replaceString - a  function which replaces a string
 *
 * @old: old string
 *
 * @new: new string
 *
 * Return: 1 if replaced
 *
 */
int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
