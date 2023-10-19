#include "shell.h"

/**
 * print_to_stderr - Prints an input string to stderr.
 *
 * @str: The string to be printed.
 */
void print_to_stderr(char *str)
{
	int i = 0;

	if (!str)

	return;

	while (str[i] != '\0')
	{
	print_char_to_stderr(str[i]);
	i++;
	}
}

/**
 * print_char_to_stderr - Writes the character c to stderr.
 *
 * @c: The character to print.
 * Return: On success, returns 1. On error, -1 is returned, and errno is set.
 */
int print_char_to_stderr(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
	write(2, buf, i);
	i = 0;
	}

	if (c != BUF_FLUSH)
	buf[i++] = c;

	return (1);
}

/**
 * print_char_to_fd - Writes the character c to the given file descriptor.
 *
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 * Return: On success, returns 1. On error, -1 is returned, and errno is set.
 */
int print_char_to_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
	write(fd, buf, i);
	i = 0;
	}

	if (c != BUF_FLUSH)
	buf[i++] = c;

	return (1);
}

/**
 * print_to_fd - Prints an input string to the given file descriptor.
 *
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters put.
 */
int print_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
	return (0);

	while (*str)
	{
	i += print_char_to_fd(*str++, fd);
	}

	return (i);
}
