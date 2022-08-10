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
	i = find_var(argv[1]);
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
