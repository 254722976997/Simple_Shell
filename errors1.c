#include "shell.h"

/**
 * Convert a string to an integer
 *
 * @param str: The string to be converted.
 * @return: Converted number if successful, -1 on error.
 */
int string_to_int(char *str)
{
    int i = 0;
    unsigned long int result = 0;

    if (*str == '+')
        str++;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            result *= 10;
            result += (str[i] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
            return -1;
    }

    return result;
}

/**
 * Print an error message to stderr.
 *
 * @param info: The parameter and return info struct.
 * @param errorStr: String containing specified error type.
 */
void print_error_message(info_t *info, char *errorStr)
{
    _eputs(info->fname);
    _eputs(": ");
    print_integer(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(errorStr);
}

/**
 * Print a decimal (integer) number (base 10).
 *
 * @param num: The input number.
 * @param fd: The file descriptor to write to.
 * @return: Number of characters printed.
 */
int print_integer(int num, int fd)
{
    int (*printChar)(char) = _putchar;
    int i, count = 0;
    unsigned int absoluteValue, current;

    if (fd == STDERR_FILENO)
        printChar = _eputchar;

    if (num < 0)
    {
        absoluteValue = -num;
        printChar('-');
        count++;
    }
    else
        absoluteValue = num;

    current = absoluteValue;

    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absoluteValue / i)
        {
            printChar('0' + current / i);
            count++;
        }
        current %= i;
    }

    printChar('0' + current);
    count++;

    return count;
}

/**
 * Convert a number to a string.
 *
 * @param num: Number to convert.
 * @param base: Base for conversion.
 * @param flags: Argument flags.
 * @return: Converted string.
 */
char *convert_to_string(long int num, int base, int flags)
{
	static char *charArray;
    	static char stringBuffer[50];
    	char sign = 0;
    	char *pointer;
    	unsigned long value = num;

   	 if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        value = -num;
        sign = '-';
    }

    charArray = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
    pointer = &stringBuffer[49];
    *pointer = '\0';

    do
    {
        *--pointer = charArray[value % base];
        value /= base;
    } while (value != 0);

    if (sign)
        *--pointer = sign;

    return pointer;
}

/**
 * Replace the first instance of '#' with '\0'.
 *
 * @param buffer: Address of the string to modify.
 */
void replace_hash_with_null(char *buffer)
{
    int i;

    for (i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
        {
            buffer[i] = '\0';
            break;
        }
    }
}

