#include "shell.h"

/**
 * add_node - adds a node to the start of the list.
 * @head: address of pointer to head node.
 * @str: str field of node.
 * @num: node index used by history.
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)

	return (NULL);

	new_node->num = num;
	new_node->str = str ? _strdup(str) : NULL;
	new_node->next = *head;

	*head = new_node;

	return (new_node);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{

	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)

	return (NULL);

	new_node->num = num;
	new_node->str = str ? _strdup(str) : NULL;
	new_node->next = NULL

	if (!*head)
	{
	*head = new_node;
	return (new_node);
	}

	list_t *temp = *head;

	while (temp->next)
	temp = temp->next;

	temp->next = new_node;

	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
	_puts(h->str ? h->str : "(nil)");
	_puts("\n");
	h = h->next;
	count++;
	}

	return (count);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
	return (0);

	if (index == 0)
	{
	list_t *temp = *head;
	*head = (*head)->next;
	free(temp->str);
	free(temp);
	return (1);
	}

	list_t *prev_node = NULL;
	list_t *current_node = *head;

	while (index > 0 && current_node)
	{
	prev_node = current_node;
	current_node = current_node->next;
	index--;
	}

	if (index != 0 || !current_node)
	return (0);

	prev_node->next = current_node->next;

	free(current_node->str);
	free(current_node);

	return (1);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	if (!head_ptr || !*head_ptr)
	return;

	list_t *current_node = *head_ptr;

	while (current_node)

	{
	list_t *temp = current_node;

	current_node = current_node->next;
	free(temp->str);
	free(temp);
	}
	*head_ptr = NULL;
}

