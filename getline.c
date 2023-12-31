#include "shell.h"

/**
 * input_buf - buffers chained command
 *
 * @info: parameter struct
 *
 * @buf: buffer
 *
 *
 * @len: length
 *
 * Return: bytes read
 *
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)/* if nothing left in the buffer, fill it */
	{
		/* bfree((void **)info->cmd_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';/* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			removeComments(*buf);
			buildHlist(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd buf = buf;
			}
		}
	}
	return (r);
}

/**
 * getInput - gets the input
 *
 * @info: parameter struct
 *
 * Return: bytes read
 *
 */
ssize_t getInput(info_t *info)
{
	static char *buf;/* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)/* EOF */
		return (-1);
	if (len) /* we have commands in the chain buffer */
	{
		j = i;/* int new iterator to current buf position */
		p = buf + i;/* get pointer for return */

		checkChain(info, buf, &j, i, len);
		while (j < len)/* iterate to semicolon */
		{
			if (isChain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;/* increment past nulled ';' */
		if (i >= len)/* reached end of buffer */
		{
			i = len = 0;/* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;/* pass back pointer to current command position */
		return (_strlen(p));/* return length of current command */
	}
	*buf_p = buf;/* else not a chain pass back buffer from _getline() */
	return (r); /* return length of a buffer */
}

/**
 * readBuf - reads a buffer
 *
 * @info: parameter struct
 *
 * @buf: buffer
 *
 * @i: size
 *
 * Return: r(number of bytes read)
 *
 */
ssize_t readBuf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 *
 * @info: parameter struct
 *
 * @ptr: address of pointer
 *
 * @length: size of preallocated buffer ptr
 *
 * Return: s(line in the standard input)
 *
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)/* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks control C
 *
 * @sig_num: signal number
 *
 * Return: no return
 *
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$");
	_putchar(BUF_FLUSH);
}
