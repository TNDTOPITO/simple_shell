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
	path = malloc(sizeof(char) * (_strlen(environ[i]) + 2));
	path = _strcpy(path, environ[i]);
	temp = path;
	for (i = 0; *path != '='; i++)
		path++;
	path++;
	allpath = malloc(sizeof(char) * (_strlen(path) + 2));
	allpath = _strcpy(allpath, path);
	free(temp);
	return (allpath);
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
		path = malloc(sizeof(char) * _strlen(argv[1]) + 2);
		path = _strcpy(path, argv[1]);
	}
	i = chdir(path);
	if (i == -1)
	{
		_printf("cd: can't cd to %s\n", argv[1]);
		return;
	}
	oldpwd = fnd_path("PWD");
	setenv("PWD", path, 1);
	free(path);
	setenv("OLDPWD", oldpwd, 1);
	free(oldpwd);
}
