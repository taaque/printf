#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @p: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *p)
{
	int curr_int = *p + 1;
	int size = 0;

	if (format[curr_int] == 'l')
		size = S_LONG;
	else if (format[curr_int] == 'h')
		size = S_SHORT;

	if (size == 0)
		*p = curr_int - 1;
	else
		*p = curr_int;

	return (size);
}
