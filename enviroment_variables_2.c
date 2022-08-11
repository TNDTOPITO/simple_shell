#include "shell.h"

/**
 * creat_var - This function creates a new environment variable
 * @argv: Arguments
 */
void creat_var(char **argv)
{
	int i = 0;
	char *var = NULL;
	size_t size = 0;
	char **tempEnv = NULL;

	while (enviroment[i])
		i++;

	size = sizeof(char) * (_strlen(argv[1]) + 2);
	size += sizeof(char) * (_strlen(argv[2]) + 8);
	var = malloc(size);
	if (!var)
	{
		perror("failed to allocate memory");
		return;
	}
	var[0] = '\0';
	var = strcpy(var, argv[1]);
	var = strcat(var, "=");
	var = strcat(var, argv[2]);
	size = sizeof(char *) * (i + 8);
	tempEnv = malloc(size);
	if (!tempEnv)
	{
		perror("failed to allocate memory");
		return;
	}
	tempEnv[0] = NULL;
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
	int size = 0;

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
	var[0] = '\0';
	var = _strcpy(var, argv[1]);
	var = _strcat(var, "=");
	var = _strcat(var, argv[2]);
	enviroment[i] = var;
}
