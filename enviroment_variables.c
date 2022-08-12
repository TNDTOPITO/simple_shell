#include "shell.h"

/**
 * cpyEnviron - This function copies enviroment variables from environ
 * to a dynamically allocated array
 */
void cpyEnviron(void)
{
	int i = 0, len;

	while (environ[i])
		i++;
	len = i + 2;
	enviroment = malloc(sizeof(char *) * len);
	enviroment[0] = NULL;
	for (i = 0; environ[i]; i++)
	{
		len = _strlen(environ[i]) + 2;
		enviroment[i] = malloc(sizeof(char) * len);
		if (!enviroment)
		{
			perror("failed to allocate memory");
			exit(98);
		}
		enviroment[i][0] = '\0';
		enviroment[i] = _strcpy(enviroment[i], environ[i]);
	}
	enviroment[i] = NULL;
}

/**
 * print_env - This function prints enviroment variables
 */
void print_env(void)
{
	int i;

	for (i = 0; enviroment[i]; i++)
		_printf("%s\n", enviroment[i]);
}

/**
 * _setenv - This function changes or adds an environment variable
 * @argv: Arguments
 */
void _setenv(char **argv)
{
	int i = 0;

	if (!argv[1] || argv[1][0] == '\0')
	{
		return;
	}
	if (!argv[2])
	{
		perror("value required");
		return;
	}
	while (argv[1][i])
	{
		if (argv[1][i] == '=')
		{
			perror("variable name can't contain =");
			return;
		}
		i++;
	}
	i = find_var(argv[1], enviroment);
	if (i == -1)
		creat_var(argv);
	else
		modify_var(argv, i);
}

/**
 * _unsetenv - This function removes
 * @argv: Arguments
 */
void _unsetenv(char **argv)
{
	int i;
	int index;

	if (!argv[1] || argv[1][0] == '\0')
	{
		print_env();
		return;
	}

	index = find_var(argv[1], enviroment);
	if (index == -1)
	{
		perror("name not found proof");
		return;
	}
	free(enviroment[index]);
	for (i = index; enviroment[i + 1]; i++)
		enviroment[i] = enviroment[i + 1];
	enviroment[i] = NULL;
}
