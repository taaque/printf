#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, paddd = ' ';
	int indx = BUFF_SIZE - 2, len = 2, paddd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrss;
	char map_to[] = "0123456789abcdef";
	void *addrss = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrss == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrss = (unsigned long)addrss;

	while (num_addrss > 0)
	{
		buffer[indx--] = map_to[num_addrss % 16];
		num_addrss /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddd = '0';
	if (flags & F_PLUS)
		extra_c = '+', len++;
	else if (flags & F_SPACE)
		extra_c = ' ', len++;

	indx++;

	/*return (write(1, &buffer[k], BUFF_SIZE - k - 1));*/
	return (write_pointer(buffer, indx, len,
		width, flags, paddd, extra_c, paddd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int offset = 0, k = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[k] != '\0')
	{
		if (is_printable(str[k]))
			buffer[k + offset] = str[k];
		else
			offset += append_hexa_code(str[k], buffer, k + offset);

		k++;
	}

	buffer[k + offset] = '\0';

	return (write(1, buffer, k + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int k, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (k = 0; str[k]; k++)
		;

	for (k = k - 1; k >= 0; k--)
	{
		char y = str[k];

		write(1, &y, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char y;
	char *str;
	unsigned int k, m;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (k = 0; str[k]; k++)
	{
		for (m = 0; in[m]; m++)
		{
			if (in[m] == str[k])
			{
				y = out[m];
				write(1, &y, 1);
				count++;
				break;
			}
		}
		if (!in[m])
		{
			y = str[k];
			write(1, &y, 1);
			count++;
		}
	}
	return (count);
}
