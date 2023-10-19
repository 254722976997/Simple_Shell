#include "shell.h"

/**
 * print_current_environment - Prints the current environment
 * @info: Structure containing potential arguments
 *
 * This function prints the contents of the current environment.
 *
 * Return: Always 0.
 */
int print_current_environment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_environment_value - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Functn retrieves the val of a specific envnt var based on its name.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *get_environment_value(info_t *info, const char *name)
{
	list_t *current_node = info->env;
	char *value;

	while (current_node)
	{
		value = starts_with(current_node->str, name);
		if (value && *value)
			return (value);
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * set_or_update_environment - Inits a new envnt variable or modify.
 * @info: Structure containing potential arguments.
 *
 * Functn either inits a new envnt var or modifies an existing one.
 *
 * Return: 0 on success, 1 on failure.
 */
int set_or_update_environment(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
	return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * remove_environment_variable - Removes an environment variable.
 * @info: Structure containing potential arguments.
 *
 * This function removes an environment variable.
 *
 * Return: 0 on success, 1 on failure.
 */
int remove_environment_variable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{_eputs("Too few arguments.\n");
		return (1);
	}

	for (i = 1; i < info->argc; i++)
	_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_environment_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 *
 * Function populates the environment linked list with environment var.
 *
 * Return: Always 0.
 */
int populate_environment_list(info_t *info)
{
	list_t *current_node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	add_node_end(&current_node, environ[i], i);

	info->env = current_node;
	return (0);
}

