#include "shell.h"

/**
 * fnd_path - This function returns path
 * @str: Variable name
 *
 * Return: Value stored in a variable
 */
char *fnd_path(char *str)
{
	int i;
	char *path = NULL;
	char *temp = NULL;
	char *allpath = NULL;

	i = find_var(str);
	if (i == -1)
		return (NULL);
	path = malloc(sizeof(char) * _strlen(enviroment[i]));
	path = _strcpy(path, enviroment[i]);
	temp = path;
	for (i = 0; *path != '='; i++)
		path++;
	path++;
	allpath = malloc(sizeof(char) * _strlen(path));
	allpath = _strcpy(allpath, path);
	free(temp);
	return (allpath);
}

/**
 * update_var - This function updates enviroment variables
 * @name: variable name
 * @str: Value
 */
void update_var(char *name, char *str)
{
	char **pwd = NULL;
	int i;

	pwd = malloc(sizeof(char *) * 4);
	pwd[0] = malloc(sizeof(char) * 3);
	pwd[1] = malloc(sizeof(char) * _strlen(name));
	pwd[2] = malloc(sizeof(char) * _strlen(str));
	pwd[0] = _strcpy(pwd[0], "cd");
	pwd[1] = _strcpy(pwd[1], name);
	pwd[2] = _strcpy(pwd[2], str);
	pwd[3] = NULL;
	_setenv(pwd);
	for (i = 0; pwd[i]; i++)
		free(pwd[i]);
	free(pwd);
}

/**
 * cd - Change current working directory
 * @argv: Arguments
 */
void cd(char **argv)
{
	int i;
	char *path = NULL;
	char *oldpwd = NULL;

	if (argv[1] == NULL)
		path = fnd_path("HOME");
	else if (argv[1][0] == '-')
	{
		path = fnd_path("OLDPWD");
		if (path == NULL)
			path = fnd_path("PWD");
	}
	else
	{
		path = malloc(sizeof(char) * _strlen(argv[1]));
		path = _strcpy(path, argv[1]);
	}
	i = chdir(path);
	if (i == -1)
	{
		_printf("cd: can't cd to %s\n", argv[1]);
		return;
	}
	oldpwd = fnd_path("PWD");
	update_var("PWD", path);
	free(path);
	update_var("OLDPWD", oldpwd);
	free(oldpwd);
}
