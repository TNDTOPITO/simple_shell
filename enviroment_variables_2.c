#include "shell.h"

/**
 * creat_var - This function creates a new environment variable
 * @argv: Arguments
 */
void creat_var(char **argv)
{
	int i;
	char *var = NULL;
	size_t size;
	char **tempEnv = NULL;

	while (enviroment[i])
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
	size = sizeof(char *) * (i + 4);
	tempEnv = malloc(size);
	if (!tempEnv)
	{
		perror("failed to allocate memory");
		return;
	}
	for (i = 0; enviroment[i]; i++)
		tempEnv[i] = enviroment[i];
	tempEnv[i] = var;
	tempEnv[i + 1] = NULL;
	free(enviroment);
	enviroment = tempEnv;
}

/**
 * modify_var - This function modifies an existing enviroment variable
 * @argv: Arguments
 * @i: Index of the variable
 */
void modify_var(char **argv, int i)
{
	char *var = NULL;
	int size;

	free(enviroment[i]);
	enviroment[i] = NULL;
	size = sizeof(char) * (_strlen(argv[1]) + 3);
	size += sizeof(char) * (_strlen(argv[2]) + 3);
	var = malloc(size);
	if (!var)
	{
		perror("failed to allocate memory");
		return;
	}
	var = _strcpy(var, argv[1]);
	var = _strcat(var, "=");
	var = _strcat(var, argv[2]);
	enviroment[i] = var;
}

/**
 * check_builtin - This function handles the shell builtin functions
 * @argv: Arguments
 *
 * Return: 0 if builtin function is found, 1 if it's not found
 */
int check_builtin(char **argv)
{

	if (_strcmp(argv[0], "setenv"))
		return (1);
	if (_strcmp(argv[0], "unsetenv"))
		return (1);
	if (_strcmp(argv[0], "env"))
		return (1);
	if (_strcmp(argv[0], "cd"))
		return (1);
	return (0);
}
