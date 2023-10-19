#include "shell.h"

/**
 * bfree - Frees a pointer and sets it to NULL.
 * @ptr: Pointer to free and set to NULL.
 *
 * Return: 1 if freed, 0 if ptr is NULL.
 */
int bfree(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
	free(*ptr);
	*ptr
	return (1);
	}
	return (0);
}
