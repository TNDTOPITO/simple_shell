#include "shell.h"

/**
 * find_var - This function searches for an environment variable
 * @var_name: Name of the variable to search for
 *
 * Return: Index on match, -1 if no match was found
 */
int find_var(char *var_name)
{
	char **env = environ;
	int i, y = 0, match;

	for (i = 0; env[i]; i++)
	{
		while (env[i][y] != '=')
		{
			if (var_name[y] == env[i][y])
				match = 1;
			else
			{
				match = 0;
				break;
			}
			y++;
		}
		if (match)
			return (i);
		y = 0;
	}
	return (-1);
}

/**
 * builtin_functions - This function handles the shell builtin functions
 * @argv: Arguments
 *
 * Return: 0 if builtin function is found, 1 if it's not found
 */
int builtin_functions(char **argv, char * str)
{

	if (_strcmp(argv[0], "exit"))
	{
		__exit(argv, str);
		return (1);
	}
	if (_strcmp(argv[0], "setenv"))
	{
		_setenv(argv);
		return (1);
	}
	if (_strcmp(argv[0], "unsetenv"))
	{
		_unsetenv(argv);
		return (1);
	}
	if (_strcmp(argv[0], "env"))
	{
		print_env();
		return (1);
	}
	if (_strcmp(argv[0], "cd"))
	{
		cd(argv);
		return (1);
	}
	return (0);
}

