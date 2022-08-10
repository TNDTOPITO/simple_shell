#ifndef PRINTF_H
#define PRINTF_H

#include <stdlib.h>
#include <stdarg.h>
/**
 * struct t - Struct t
 *
 * @c: Character
 * @f: Function associated
 */
typedef struct t
{
	char c;
	int (*f)(va_list list, ...);
} data_t;

int _printf(const char *format, ...);

int _putchar(char c);

int (*specifier(char c))(va_list list, ...);

int print_char(va_list list, ...);

int print_per(va_list list, ...);

int print_str(va_list list, ...);

int print_num(va_list list, ...);

#endif /* PRINTF_H */
