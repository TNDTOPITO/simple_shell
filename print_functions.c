#include "_printf.h"

/**
 * print_char - This function prints a character
 * @list: Arguments
 *
 * Return: 1 on sucess
 */
int print_char(va_list list, ...)
{
	return (_putchar(va_arg(list, int)));
}

/**
 * print_per - This function prints %
 * @list: Arguments
 *
 * Return: 1 on sucess
 */
int print_per(va_list list, ...)
{
	va_arg(list, int);
	return (_putchar('%'));
}

/**
 * print_str - This function print string
 * @list: List of arguments
 *
 * Return: Number of characters printed
 */
int print_str(va_list list, ...)
{
	int numChar = 0;
	char *str1 = "(null)";
	char *str = va_arg(list, char *);

	if (str)
	{
		while (*str)
		{
			numChar += _putchar(*str);
			str++;
		}
	}
	else
	{
		while (*str1)
		{
			numChar += _putchar(*str1);
			str1++;
		}
	}
	return (numChar);
}

/**
 * print_num - this function print integers
 * @list: list of arguments
 *
 * Return: number of numbers printed
 */
int print_num(va_list list, ...)
{
	int k = 1, num, l, numInt = 0;
	va_list ap;

	va_start(ap, list);
	num = va_arg(list, int);
	l = num;
	if (num < 0)
	{
		k = k * -1;
		numInt += _putchar('-');
	}
	while (l > 9 || l < -9)
	{
		l = l / 10;
		k = k * 10;
	}

	while (k > 9 || k < -9)
	{
		numInt += _putchar((num / k) % 10 + '0');
		k = k / 10;
	}
	if (num < 0)
		numInt += _putchar((num % 10)  * -1 + '0');
	else
		numInt += _putchar((num % 10) + '0');
	return (numInt);
}
