#include "shell.h"

/**
 * buffer_input - buffers input commands.
 * @info: parameter struct.
 * @buffer: address of the buffer.
 * @len: address of len var.
 *
 * Return: bytes read
 */
ssize_t buffer_input(info_t *info, char **buffer, size_t *len)
{
	ssize_t bytesRead = 0;
	size_t len_p = 0;

	if (!*len) /* if buffer is empty, read input */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, blockCtrlC);
#if USE_GETLINE
		bytesRead = getline(buffer, &len_p, stdin);
#else
		bytesRead = custom_getline(info, buffer, &len_p);
#endif
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
		}
	}
	return (bytesRead);
}

/**
 * get_user_input - gets user input without newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_user_input(info_t *info)
{
	static char *buffer; /* command buffer */
	static size_t bufIndex, bufLength;
	ssize_t bytesRead = 0;
	char **buffer_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytesRead = buffer_input(info, &buffer, &bufLength);

	if (bytesRead == -1) /* EOF */
		return (-1);

	if (bufLength) /* buffer has remaining commands */
	{
		size_t newIndex = bufIndex;

		p = buffer + bufIndex; /* get pointer for return */

		check_command_chain(info, buffer, &newIndex, bufIndex, bufLength);
		while (newIndex < bufLength) /* iterate to semicolon or end */
		{
			if (is_command_chain(info, buffer, &newIndex))
				break;
			newIndex++;
		}

		bufIndex = newIndex + 1; /* increment past nulled ';'' */
		if (bufIndex >= bufLength) /* reached end of buffer? */
		{
			bufIndex = bufLength = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORMAL;
		}

		*buffer_p = p; /* pass back pointer to current command position */
		return ((int)(p - buffer)); /* return length of current command */
	}

	*buffer_p = buffer; /* not a chain, pass back buffer */
	return (bytesRead);
}

/**
 * read_buffer - reads into a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: bytesRead
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *i)
{
	ssize_t bytesRead = 0;

	if (*i)
		return (0);

	bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytesRead >= 0)
		*i = bytesRead;

	return (bytesRead);
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: bytes read
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t bufIndex, bufLength;
	size_t k;
	ssize_t bytesRead = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		bytesRead = *length;

	if (bufIndex == bufLength)
		bufIndex = bufLength = 0;

	bytesRead = read_buffer(info, buffer, &bufLength);
	if (bytesRead == -1 || (bytesRead == 0 && bufLength == 0))
		return (-1);

	c = custom_strchr(buffer + bufIndex, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : bufLength;
	new_p = custom_realloc(p, bytesRead, bytesRead ? bytesRead + k : k + 1);

	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (bytesRead)
		custom_strncat(new_p, buffer + bufIndex, k - bufIndex);
	else
		custom_strncpy(new_p, buffer + bufIndex, k - bufIndex + 1);

	bytesRead += k - bufIndex;
	bufIndex = k;
	p = new_p;

	if (length)
		*length = bytesRead;

	*ptr = p;
	return (bytesRead);
}

/**
 * blockCtrlC - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void blockCtrlC(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
