#include "main.h"
/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int k = 0;
	char paddd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		paddd = '0';
	buffer[k++] = c;
	buffer[k] = '\0';
	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (k = 0; k < width - 1; k++)
			buffer[BUFF_SIZE - k - 2] = paddd;
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - k - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - k - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}
/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: List of arguments
 * @indx: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int indx, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - indx - 1;
	char paddd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';
	return (write_num(indx, buffer, flags, width, precision,
		len, paddd, extra_ch));
}
/**
 * write_num - Write a number using a bufffer
 * @indx: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @len: Number length
 * @paddd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int indx, char buffer[],
	int flags, int width, int prec,
	int len, char paddd, char extra_c)
{
	int k, paddd_start = 1;

	if (prec == 0 && indx == BUFF_SIZE - 2 && buffer[indx] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && indx == BUFF_SIZE - 2 && buffer[indx] == '0')
		buffer[indx] = paddd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < len)
		paddd = ' ';
	while (prec > len)
		buffer[--indx] = '0', len++;
	if (extra_c != 0)
		len++;
	if (width > len)
	{
		for (k = 1; k < width - len + 1; k++)
			buffer[k] = paddd;
		buffer[k] = '\0';
		if (flags & F_MINUS && paddd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--indx] = extra_c;
			return (write(1, &buffer[indx], len) + write(1, &buffer[1], k - 1));
		}
		else if (!(flags & F_MINUS) && paddd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--indx] = extra_c;
			return (write(1, &buffer[1], k - 1) + write(1, &buffer[indx], len));
		}
		else if (!(flags & F_MINUS) && paddd == '0')/* extra char to left of paddd */
		{
			if (extra_c)
				buffer[--paddd_start] = extra_c;
			return (write(1, &buffer[paddd_start], k - paddd_start) +
				write(1, &buffer[indx], len - (1 - paddd_start)));
		}
	}
	if (extra_c)
		buffer[--indx] = extra_c;
	return (write(1, &buffer[indx], len));
}
/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @indx: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int indx,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int len = BUFF_SIZE - indx - 1, k = 0;
	char paddd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && indx == BUFF_SIZE - 2 && buffer[indx] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */
	if (precision > 0 && precision < len)
		paddd = ' ';
	while (precision > len)
	{
		buffer[--indx] = '0';
		len++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddd = '0';
	if (width > len)
	{
		for (k = 0; k < width - len; k++)
			buffer[k] = paddd;
		buffer[k] = '\0';
		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
			return (write(1, &buffer[indx], len) + write(1, &buffer[0], k));
		else /* Asign extra char to left of padding [padd>buffer]*/
			return (write(1, &buffer[0], k) + write(1, &buffer[indx], len));
	}
	return (write(1, &buffer[indx], len));
}
/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @indx: Index at which the number starts in the buffer
 * @len: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @paddd: Char representing the padding
 * @extra_c: Char representing extra char
 * @paddd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int indx, int len,
	int width, int flags, char paddd, char extra_c, int paddd_start)
{
	int k;

	if (width > len)
	{
		for (k = 3; k < width - len + 3; k++)
			buffer[k] = paddd;
		buffer[k] = '\0';
		if (flags & F_MINUS && paddd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--indx] = 'x';
			buffer[--indx] = '0';
			if (extra_c)
				buffer[--indx] = extra_c;
			return (write(1, &buffer[indx], len) + write(1, &buffer[3], k - 3));
		}
		else if (!(flags & F_MINUS) && paddd == ' ')/* extra char to left of buffer */
		{
			buffer[--indx] = 'x';
			buffer[--indx] = '0';
			if (extra_c)
				buffer[--indx] = extra_c;
			return (write(1, &buffer[3], k - 3) + write(1, &buffer[indx], len));
		}
		else if (!(flags & F_MINUS) && paddd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--paddd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[paddd_start], k - paddd_start) +
				write(1, &buffer[indx], len - (1 - paddd_start) - 2));
		}
	}
	buffer[--indx] = 'x';
	buffer[--indx] = '0';
	if (extra_c)
		buffer[--indx] = extra_c;
	return (write(1, &buffer[indx], BUFF_SIZE - indx - 1));
}
