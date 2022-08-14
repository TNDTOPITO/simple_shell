#include "shell.h"
#include <stdlib.h>

/**
 * find_var_rev - This function searches for an environment variable
 * @var_name: Name of the variable to search for
 * @arr: ...
 *
 * Return: Index on match, -1 if no match was found
 */
int find_var_rev(char *var_name, char **arr)
{
	char **env = NULL;
	int i = 0, y = 0, match = 0, index = 0;

	env = arr;
	if (!env)
		return (-1);
	for (i = 0; env[i]; i++)
	{
		y = strlen(env[i]);
		index = strlen(var_name);
		while (env[i][y] != '=' && y >= 0)
		{
			if (var_name[index] == env[i][y])
				match = 1;
			else
			{
				match = 0;
				break;
			}
			y--;
			index--;
		}
		if (match)
			return (i);
	}
	return (-1);
}

/**
 * add_al - This function adds or modify an aliase
 * @str: Aliase;
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
		aliase = NULL;
		aliase = malloc(sizeof(char *) * 3);
		aliase[0] = string;
		aliase[1] = NULL;
		return;
	}
	cpy = strdup(str);
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
	int i = 0, index = 0;

	if (!aliase)
		return;
	i = find_var_rev(str, aliase);
	if (i == -1)
		i = find_var(str, aliase);
	if (i == -1)
		return;
	for (index = 0; aliase[i][index]; index++)
	{
		if (aliase[i][index] == '=')
		{
			_putchar('=');
			_putchar('\'');
		}
		else
			_putchar(aliase[i][index]);
	}
	_putchar('\'');
	_putchar('\n');
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
		{
			for (index = 0; aliase[i][index]; index++)
			{
				if (aliase[i][index] == '=')
					_printf("=\'");
				else
					_putchar(aliase[i][index]);
			}
		_printf("\'\n");
		}
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
		{
			print_al(argv[i]);
		}
		print_mode = 1;
	}
}

/**
 * chk_str - This function checks for aliases and variables
 * @token: string to check
 *
 * Return: String
 */
char *chk_str(char *token)
{
	int i = 0;
	char *temp = NULL;

	if (token[0] == '$')
	{
		if (token[1] == '?')
		{
			temp = malloc(sizeof(char) * 5);
			temp[0] = '\0';
			sprintf(temp, "%d", exit_status);
			return (temp);
		}
		if (token[1] == '$')
		{
			temp = malloc(sizeof(char) * 1024);
			temp[0] = '\0';
			sprintf(temp,"%d", getpid());
			return (temp);
		}
		temp = token;
		token++;
		token = fnd_path(token);
		free(temp);
		return (token);
	}
	for (i = 0; token[i]; i++)
	{
		if (token[i] == '=')
			return (token);
	}
	i = find_var(token, aliase);
	if (i == -1)
	{
		return (token);
	}
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
