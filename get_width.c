#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @p: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *p, va_list list)
{
	int curr_int;
	int width = 0;

	for (curr_int = *p + 1; format[curr_int] != '\0'; curr_int++)
	{
		if (is_digit(format[curr_int]))
		{
			width *= 10;
			width += format[curr_int] - '0';
		}
		else if (format[curr_int] == '*')
		{
			curr_int++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*p = curr_int - 1;

	return (width);
}
