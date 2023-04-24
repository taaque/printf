#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @p: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *p, va_list list)
{
	int curr_int = *p + 1;
	int precision = -1;

	if (format[curr_int] != '.')
		return (precision);

	precision = 0;

	for (curr_int += 1; format[curr_int] != '\0'; curr_int++)
	{
		if (is_digit(format[curr_int]))
		{
			precision *= 10;
			precision += format[curr_int] - '0';
		}
		else if (format[curr_int] == '*')
		{
			curr_int++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*p = curr_int - 1;

	return (precision);
}
