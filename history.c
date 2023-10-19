#include "shell.h"

/**
 * get_history_file - gets the history file.
 * @info: parameter struct.
 *
 * Return: allocated string containing history file.
 */
char *get_history_file(info_t *info)
{
	char *dir = _getenv(info, "HOME=");

	if (!dir)

	return (NULL);

	char *buf;

	asprintf(&buf, "%s/%s", dir, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	char *filename = get_history_file(info);

	if (!filename)
	return (-1);

	FILE *file = fopen(filename, "w");

	if (!file)
	{
	free(filename);
	return (-1);
	}

	list_t *node = info->history;

	while (node)
	{
	fprintf(file, "%s\n", node->str);
	node = node->next;
	}

	fclose(file);
	free(filename);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	char *filename = get_history_file(info);

	if (!filename)
	return (0);

	FILE *file = fopen(filename, "r");

	free(filename);
	if (!file)
	return (0);

	char *line = NULL;
	size_t len = 0;
	int linecount = 0;

	while (getline(&line, &len, file) != -1)
	{
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';

	build_history_list(info, line, linecount++);
	}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)

	list_t *node = info->history;
	int i = 0;

	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}
