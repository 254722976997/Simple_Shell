#include "shell.h"

/**
 * custom_strlen - Returns the length of a str.
 * @str: The string whose length to check
 *
 * Return: Int. length of the str.
 */
int custom_strlen(char *str)
{
	int length = 0;

	if (!str)
	return (0);

	while (*str++)
		length++;

	return (length);
}

/**
 * custom_strcmp - Performs lexicographic comparison of two strings
 * @str1: The first string
 * @str2: The second string
 *
 * Return: Neg -ve if str1 < str2, pos +ve if str1 > str2, zero if str1 == str2
 */
int custom_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
	if (*str1 != *str2)
		return (*str1 - *str2);
	str1++;
	str2++;
	}

	if (*str1 == *str2)
	return (0);
	else
	return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with_custom - Checks if needle starts with haystack
 * @haystack: String to search
 * @needle: The substring to find
 *
 * Return: Address of next character of haystack or NULL
 */
char *starts_with_custom(const char *haystack, const char *needle)
{
	while (*needle)
	{
	if (*needle++ != *haystack++)
		return (NULL);
	}

	return ((char *)haystack);
}

/**
 * custom_strcat - Concatenates two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: Pointer to destination buffer
 */
char *custom_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
	dest++;

	while (*src)
	*dest++ = *src++;

	*dest = *src;

	return (result);
}


