#include "shell.h"

/**
 * add_al - This function adds or modify an aliase
 *
 */
void add_al(char *str)
{
	int i = 0, index = 0;
	char *string = NULL;
	char *cpy = NULL;
	char **tempStr = NULL;

	string = malloc(sizeof(char) * _strlen(str) + 2);
	string[0] = '\0';
	string = _strcpy(string, str);
	if (!aliase)
	{
		aliase = malloc(sizeof(char *) * 3);
		aliase[0] = string;
		aliase[1] = NULL;
		return;
	}
	while (str[i] != '=')
		i++;
	cpy = malloc(sizeof(char) * (i + 2));
	cpy[0] = '\0';
	cpy = strncpy(cpy, str, i - 1);
	cpy[i] = '\0';
	i = find_var(cpy, aliase);
	free(cpy);
	if (i != -1)
	{
		free(aliase[i]);
		aliase[i] = string;
	}
	else
	{
		while (aliase[index])
			index++;
		tempStr = malloc(sizeof(char *) * (index + 2));
		for (i = 0; aliase[i]; i++)
			tempStr[i] = aliase[i];
		tempStr[i] = string;
		tempStr[i + 1] = NULL;
		free(aliase);
		aliase = tempStr;
	}
}

/**
 * print_al - This function prints selected aliases
 * @str: Name of aliase
 */
void print_al(char *str)
{
	int i = 0;

	i = find_var(str, aliase);
	_printf("%s print\n", aliase[i]);
}

/**
 * alias - This function handles aliase functionality
 * @argv: Arguments
 */
void alias(char **argv)
{
	int i = 0;
	int index = 0;
	int print_mode = 1;

	if (!argv[1])
	{
		for (i = 0; aliase[i]; i++)
			_printf("%s\n", aliase[i]);
		return;
	}
	for (i = 1; argv[i]; i++)
	{
		for (index = 0; argv[i][index]; index++)
		{
			if (argv[i][index] == '=')
			{
				add_al(argv[i]);
				print_mode = 0;
				break;
			}
		}
		if (print_mode)
			print_al(argv[i]);
		print_mode = 1;
	}
}

/**
 * chk_str - This function checks for aliases and variables
 * @str: string to check
 *
 * Return: String
 */
char *chk_str(char *token)
{
	int i = 0;
	char *temp = NULL;

	i = find_var(token, aliase);
	if (i == -1)
		return (token);
	while (i != -1)
	{
		temp = aliase[i];
		while (*temp != '=')
			temp++;
		temp += 1;
		free(token);
		token = strdup(temp);
		i = find_var(token, aliase);
	}
	return (token);
}
