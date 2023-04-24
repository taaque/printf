#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @indx: index.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *indx, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int k, unknwn_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (k = 0; fmt_types[k].fmt != '\0'; k++)
		if (fmt[*indx] == fmt_types[k].fmt)
			return (fmt_types[k].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[k].fmt == '\0')
	{
		if (fmt[*indx] == '\0')
			return (-1);
		unknwn_len += write(1, "%%", 1);
		if (fmt[*indx - 1] == ' ')
			unknwn_len += write(1, " ", 1);
		else if (width)
		{
			--(*indx);
			while (fmt[*indx] != ' ' && fmt[*indx] != '%')
				--(*indx);
			if (fmt[*indx] == ' ')
				--(*indx);
			return (1);
		}
		unknwn_len += write(1, &fmt[*indx], 1);
		return (unknwn_len);
	}
	return (printed_chars);
}
