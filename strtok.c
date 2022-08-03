#include "shell.h"

/**
 * _strtok - This function breaks a string into a sequence of zero or more
 * nonempty tokens
 * @str: Pointer to a string
 * @delim: String of delimeters
 *
 * Return: Pointer to the next token or NULL if theres no more tokens
 */
char *_strtok(char *str, const char *delim)
{
	static char *tokn;

	if (str == NULL)
	{
		str = tokn;
		if (str == NULL)
			return (NULL);
	}

	str += strspn(str, delim);
	if (*str == '\0')
	{
		tokn = NULL;
		return (tokn);
	}

	tokn = str + strcspn(str, delim);
	if (tokn[0] != '\0')
	{
		tokn[0] = '\0';
		tokn++;
	}
	else
		tokn = NULL;

	return (str);
}
