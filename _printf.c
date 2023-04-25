#include "main.h"

void print_buffer(char buffer[], int *buff_indx);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int k, printed_chars = 0, printed = 0;
	int flags, width, size, precision, buff_indx = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);
	va_start(list, format);
	for (k = 0; format && format[k] != '\0'; k++)
	{
		if (format[k] != '%')
		{
			buffer[buff_indx++] = format[k];
			if (buff_indx == BUFF_SIZE)
				print_buffer(buffer, &buff_indx);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_indx);
			flags = get_flags(format, &k);
			width = get_width(format, &k, list);
			precision = get_precision(format, &k, list);
			size = get_size(format, &k);
			++k;
			printed = handle_print(format, &k, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_indx);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_indx: Index at which to add next char, reprsnts length.
 */
void print_buffer(char buffer[], int *buff_indx)
{
	if (*buff_indx > 0)
		write(1, &buffer[0], *buff_indx);

	*buff_indx = 0;
}
