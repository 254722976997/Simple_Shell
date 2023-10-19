#include "shell.h"

/**
 * exit_shell - Function to handle exit command
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0 if info->argv[0] != "exit")
 */
int exit_shell(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
	exit_status = _erratoi(info->argv[1]);
	if (exit_status == -1)
	{
		info->status = 2;
	print_error(info, "Illegal number: ");
		_eputs(info->argv[1]);
		_eputchar('\n');
		return (1);
	}
	info->err_num = exit_status;
	return (-2);
	}

	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - Function to handle changing the current directory
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int change_directory(info_t *info)
{
	char *dir;
	char buffer[1024];
	int chdir_ret;

	char *current_dir = getcwd(buffer, 1024);

	if
		(!current_dir)
	_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
	dir = _getenv(info, "HOME=");
	if (!dir)
		chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
	else
		chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
	if (!_getenv(info, "OLDPWD="))
	{
	_puts(current_dir);
	_putchar('\n');
	return (1);
	}
	_puts(_getenv(info, "OLDPWD="));
	_putchar('\n');
	chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
		else
	{
	chdir_ret = chdir(info->argv[1]);
	}

	if (chdir_ret == -1)
	{
	print_error(info, "can't cd to ");
	_eputs(info->argv[1]);
	_eputchar('\n');
	}
		else
		{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
		}

	return (0);
}

/**
 * display_help - Function to display help information
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int display_help(info_t *info)
{
	_puts("help call works. Function not yet implemented \n");
	return (0);
}

