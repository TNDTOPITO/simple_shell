#include "shell.h"

/**
 * str_to_arr - This function converts a string int an array of strings
 * @str: String to convert
 *
 * Return: Pointer to the array of words
 */
char **str_to_arr(char *str)
{
	char **arrStr;
	int i, len = 0;
	char *token, *delim = " \t\n";

	for (i = 0; str[i]; i++)
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			len++;
	}
	arrStr = malloc(sizeof(char *) * len + 1);
	if (arrStr == NULL)
		return (NULL);
	token = strtok(str, delim);
	for (i = 0; token != NULL; i++)
	{
		arrStr[i] = token;
		token = strtok(NULL, delim);
	}
	arrStr[i] = token;
	return (arrStr);
}

