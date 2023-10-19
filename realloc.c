#include "shell.h"

/**
 * custom_memset - Fills memory with a specified byte.
 * @dest: Pointer to the memory area.
 * @byte: The byte to fill dest with.
 * @n: The number of bytes to be filled.
 *
 * Return: A pointer to the memory area dest.
 */
char *custom_memset(char *dest, char byte, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	dest[i] = byte;
	return (dest);
}

/**
 * free_strings - Frees an array of strings.
 * @str_array: Array of strings.
 */
void free_strings(char **str_array)
{
	char **temp = str_array;

	if (!str_array)
	return;

	while (*str_array)
	free(*str_array++);
	free(temp);
}

/**
 * custom_realloc - Reallocates a block of memory
 * @prev_ptr: Pointer to the previous block
 * @prev_size: Byte size of the previous block
 * @new_size: Byte size of the new block
 *
 * Return: Pointer to the reallocated block
 */
void *custom_realloc(void *prev_ptr, unsigned int prev_size, unsigned int new_size)
{
	char *new_ptr;

	if (!prev_ptr)
	return (malloc(new_size));

	if (!new_size)
	return (free(prev_ptr), NULL);

	if (new_size == prev_size)
	return (prev_ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
	return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
	new_ptr[prev_size] = ((char *)prev_ptr)[prev_size];

	free(prev_ptr);
	return (new_ptr);
}

