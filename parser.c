#include "shell.h"

/**
 * check_command - Check if a file is an executable command
 * @info: Information structure
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise.
 */
int check_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (!path || stat(path, &st))
	return (0);

	if (st.st_mode & S_IFREG)
		return (1);

	return (0);
}

/**
 * duplicate_chars - Duplicate characters from pathstr
 * @pathstr: The PATH string
 * @start: Starting index
 * @end: Ending index
 *
 * Return: Pointer to new buffer
 */
char *duplicate_chars(char *pathstr, int start, int end)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (i = start; i < end; i++)
		if (pathstr[i] != ':')
			buffer[k++] = pathstr[i];

	buffer[k] = '\0';
	return (buffer);
}

/**
 * find_command_path - Find the command in the PATH string
 * @info: Information structure
 * @pathstr: The PATH string
 * @cmd: The command to find
 *
 * Return: Full path of command if found, otherwise NULL
 */
char *find_command_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, current_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
	if (check_command(info, cmd))
	return (cmd);
	}

	while (1)
	{
	if (!pathstr[i] || pathstr[i] == ':')
	{
	path = duplicate_chars(pathstr, current_pos, i);
		if (!*path)
			_strcat(path, cmd);

		else
		{
			_strcat(path, "/");
			_strcat(path, cmd);
		}
		if (check_command(info, path))
			return (path);

		if (!pathstr[i])
		break;

		current_pos = i;
	}
	i++;
	}
	return (NULL);
}

