#include "shell.h"

/**
 * list_length - calculates the length of a linked list.
 * @head: pointer to the first node.
 *
 * Return: length of the list.
 */
size_t list_length(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
	head = head->next;
	count++;
	}
	return (count);
}

/**
 * list_to_array - converts a linked list to an array of strings.
 * @head: pointer to the first node.
 *
 * Return: array of strings.
 */
char **list_to_array(list_t *head)
{
	size_t length = list_length(head);
	char **str_array = NULL;
	char *str;

	if (!head || length == 0)
	return (NULL);

	str_array = malloc(sizeof(char *) * (length + 1));
	if (!str_array)
	return (NULL);

	for (size_t i = 0; head; head = head->next, i++)
	{
	str = _strdup(head->str);
	if (!str)
	{
		for (size_t j = 0; j < i; j++)
		free(str_array[j]);
		free(str_array);
	return (NULL);
	}
	str_array[i] = str;
	}
	str_array[length] = NULL;

	return (str_array);
}

/**
 * print_list_elements - prints all elements of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: length of the list
 */
size_t print_list_elements(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
	_puts(convert_number(head->num, 10, 0));
	_putchar(':');
	_putchar(' ');
	_puts(head->str ? head->str : "(nil)");
	_puts("\n");
	head = head->next;
	count++;
	}
	return (count);
}

/**
 * find_node_starts_with - finds a node whose string starts with a prefix
 * @head: pointer to the list head
 * @prefix: string to match
 * @next_char: the next character after the prefix to match
 *
 * Return: the matching node or NULL
 */
list_t *find_node_starts_with(list_t *head, char *prefix, char next_char)
{
	char *p = NULL;

	while (head)
	{
	p = starts_with(head->str, prefix);
	if (p && ((next_char == -1) || (*p == next_char)))
	return (head);
	head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
	if (head == node)
		return (index);
	head = head->next;
	index++;
	}
	return (-1);
}


