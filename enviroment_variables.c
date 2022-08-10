#include "shell.h"

/**
 * print_env - This function prints enviroment variables
 */
void print_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		_printf("%s\n", environ[i]);
}

/**
 * creat_var - This function creates a new environment variable
 * @argv: Arguments
 */
void creat_var(char **argv)
{
	int i;
	char *var = NULL;
	size_t size;

	while (environ[i])
		i++;

	size = sizeof(char) * (_strlen(argv[1]) + 2);
	size += sizeof(char) * (_strlen(argv[2]) + 2);
	var = malloc(size);
	if (!var)
	{
		perror("failed to allocate memory");
		return;
	}
	var = _strcpy(var, argv[1]);
	var = _strcat(var, "=");
	var = _strcat(var, argv[2]);
	i = putenv(var);
	if (i != 0)
		perror("failed to set variable");
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
		perror("variable name can't be NULL or length of 0");
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
	creat_var(argv);
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
		perror("variable name can't be NULL or length of 0");
		return;
	}

	index = find_var(argv[1]);
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
