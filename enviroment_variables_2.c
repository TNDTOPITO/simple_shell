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

	size = sizeof(char) * (_strlen(argv[1]) + 1);
	size += sizeof(char) * _strlen(argv[2]);
	var = malloc(size);
	if (!var)
	{
		perror("failed to allocate memory");
		return;
	}
	var = _strcat(var, argv[1]);
	var = _strcat(var, "=");
	var = _strcat(var, argv[2]);
	size = sizeof(char *) * (i + 2);
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
	size = sizeof(char) * (_strlen(argv[1]) + 1);
	size += sizeof(char) * _strlen(argv[2]);
	var = malloc(size);
	if (!var)
	{
		perror("failed to allocate memory");
		return;
	}
	var = _strcat(var, argv[1]);
	var = _strcat(var, "=");
	var = _strcat(var, argv[2]);
	printf("var: %s\n", var);
	printf("argv[1]: %s\n", argv[1]);
	enviroment[i] = var;
	printf("%s\n", enviroment[i]);
}
