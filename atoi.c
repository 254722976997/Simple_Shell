#include "shell.h"

/**
 * is_interactive_shell - Checks if the shell is running in interactive mode
 * @info: Struct address.
 *
 * Return: 1 if interactive mode, 0 otherwise.
 */
int is_interactive_shell(info_t *info)
{

	return ((isatty(STDIN_FILENO) && info->readfd<= 2));
}
/**
 * is_special_character - Checks if a character is a special delimiter
 * @c: The character to check.
 * @special_chars: The special characters string.
 *
 * Return: 1 if true, 0 if false
 */
int is_special_character(char c, char *special_chars)
{
	while (*special_chars)
	{
		if (*special_chars++ == c)
			return (1);
	}
	return (0);
}

/**
 * is_alpha_character - Checks if a character is an alphabetic character
 * @c: The character to check.
 *
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int is_alpha_character(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
/**
 * parse_integer - Parses an integer from a string
 * @s: The string to parse
 *
 * Return: 0 if no numbers in string, parsed number otherwise
 */
int parse_integer(char *s)
{
	int i, sign = 1, flag = 0, parsed_integer = 0;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		parsed_integer = -result;
	else
		parsed_integer = result;

	return (parsed_integer);
}
