#include "_printf.h"

/**
 * specifier - This function selects a function according data type
 * @c: Conversion specifier
 *
 *
 * Return: Address of function
 */
int (*specifier(char c))(va_list list, ...)
{
	data_t type[] = {
		{'c', print_char},
		{'s', print_str},
		{'%', print_per},
		{'d', print_num},
		{'i', print_num},
		{'\0', NULL}
	};
	int i = 0;

	while (type[i].f != NULL)
	{
		if (type[i].c == c)
			return (type[i].f);

		i++;
	}
	return (NULL);
}
