#include "shell.h"

/**
 * exit_shell - exits the shell
 * helen&martin
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(data_shell *datash)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (datash->args[1] != NULL)
	{
		ustatus = _atoi(datash->args[1]);
		is_digit = _isdigit(datash->args[1]);
		str_len = _strlen(datash->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustatus % 256);
	}
	return (0);
} @property: the string environment variable to remove
 * Return: 1 if deleted, 0 otherwise
 */
int _removeenv(info_t *info, char *property)
{
	list_t *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !property)
		return (0);

	while (node)
	{
		p = starts_with(node->str, property);
		if (p && *p == '=')
		{
			info->env_modified = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_modified);
}

/**
 * _setenvironment - Init a new envnt var or modify an existing one
 * @info: Structure containing potential arguments.
 * @property: the string environment variable property
 * @value: the string environment variable value
 * Return: 0 on success, 1 on failure
 */
int _setenvironment(info_t *info, char *property, char *value, list_t *node)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!property || !value)
		return (0);

	buffer = malloc(_strlen(property) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, property);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		p = starts_with(const char *str, const char *property);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_modified = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_modified = 1;
	return (0);
}
