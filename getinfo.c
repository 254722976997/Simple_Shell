#include "shell.h"

/**
 * initialize_info - Initializes the info_t struct.
 * @info: Address of the struct.
 */
void initialize_info(info_t *info)
{
	info->arguments = NULL;
	info->arguments_count = 0;
	info->command_path = NULL;
}

/**
 * configure_info - Configures the info_t struct.
 * @info: Address of the struct.
 * @args: Argument vector.
 */
void configure_info(info_t *info, char **args)
{
	int i = 0;

	info->program_name = args[0];
	if (info->arguments)
	{
		info->arguments = tokenize_arguments(info->arguments_str, " \t");
		if (!info->arguments)
		{
			info->arguments = malloc(sizeof(char *) * 2);
			if (info->arguments)
			{
				info->arguments[0] = _strdup(info->arguments_str);
				info->arguments[1] = NULL;
			}
		}
		for (i = 0; info->arguments && info->arguments[i]; i++)
			;
		info->arguments_count = i;

		replace_aliases(info);
		replace_variables(info);
	}
}

/**
 * release_info - Frees memory associated with the info_t struct
 * @info: Address of the struct
 * @free_all: true if freeing all fields
 */
void release_info(info_t *info, int free_all)
{
	free(info->arguments);
	info->arguments = NULL;
	info->command_path = NULL;
	if (free_all)
	{
	if (!info->command_buffer)
		free(info->arguments_str);
	if (info->env)
		free_list(&(info->env));
	if (info->history)
		free_list(&(info->history));
	if (info->alias)
		free_list(&(info->alias));
	if (info->environ)
	{
		ffree(info->environ);
		info->environ = NULL;
	}
	bfree((void **)info->command_buffer);
	if (info->read_fd > 2)
		close(info->read_fd);
	_putchar(BUF_FLUSH);

}
