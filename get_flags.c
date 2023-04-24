#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @p: take a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *p)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int k, curr_int;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_int = *p + 1; format[curr_int] != '\0'; curr_int++)
	{
		for (k = 0; FLAGS_CH[k] != '\0'; k++)
			if (format[curr_int] == FLAGS_CH[k])
			{
				flags |= FLAGS_ARR[k];
				break;
			}

		if (FLAGS_CH[k] == 0)
			break;
	}

	*p = curr_int - 1;

	return (flags);
}
