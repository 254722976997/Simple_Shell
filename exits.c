#include "shell.h"

/**
 * custom_strncpy - Custom impl of strncpy, copies a string up to n characters.
 *
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 * Return: The concatenated string.
 */
char *custom_strncpy(char *dest, char *src, int n)
{
	int i;
	char *result = dest;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
	dest[i] = src[i];
	}

	for (; i < n; i++)
	{
	dest[i] = '\0';
	}

	return (result);
}

/**
 * custom_strncat - Custom impl of strncat, concats two strings up to n chars.
 *
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of characters to concatenate.
 * Return: The concatenated string.
 */
char *custom_strncat(char *dest, char *src, int n)
{
	int i = 0;
	int dest_length = 0;

	while (dest[dest_length] != '\0')
	{
	dest_length++;
	}

	while (i < n && src[i] != '\0')
	{
	dest[dest_length] = src[i];
	i++;
	dest_length++;
	}

	dest[dest_length] = '\0';

	return (dest);
}

/**
 * custom_strchr - Custom impl of strchr, locates a character in a string.
 *
 * @str: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the memory area in str.
 */
char *custom_strchr(char *str, char c)
{
	while (*str != '\0')
	{
	if (*str == c)
	{
	return (str);
	}
	str++;
	}

	return (NULL);
}

