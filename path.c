#include "shell.h"

/**
 * find_var - This function searches for an environment variable
 * @var_name: Name of the variable to search for
 *
 * Return: Index on match, -1 if no match was found
 */
int find_var(char *var_name)
{
	char **env = enviroment;
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
 * path - This function stores directories in the path variable on linked list
 *
 * Return: The address of the head
 */
path_t *path(void)
{
	char **env = environ;
	char *path;
	int i;
	path_t *head;

	i = find_var("PATH");
	if (i == -1)
	{
		_printf("PATH enviroment variable not found");
		exit(1);
	}
	path = env[i];
	while (*path != '=')
		path++;
	path++;
	head = creat_list(path);
	return (head);
}

/**
 * builtin_functions - This function handles the shell builtin functions
 * @argv: Arguments
 *
 * Return: 0 if builtin function is found, 1 if it's not found
 */
int builtin_functions(char **argv)
{

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

/**
 * str_to_arr - This function converts a string int an array of strings
 * @str: String to convert
 *
 * Return: Pointer to the array of words
 */
char **str_to_arr(char *str)
{
	char **arrStr;
	int i, len = 0;
	char *token, *delim = " \t\n";

	for (i = 0; str[i]; i++)
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			len++;
	}
	arrStr = malloc(sizeof(char *) * (len + 2));
	if (arrStr == NULL)
		return (NULL);
	token = _strtok(str, delim);
	for (i = 0; token; i++)
	{
		arrStr[i] = token;
		token = _strtok(NULL, delim);
	}
	arrStr[i] = token;
	return (arrStr);
}

/**
 * path_finder - This function checks if the command exists
 * @argv: Array of string with the command and arguments
 * @path_list: Linked list
 * @str: str
 *
 * Return: 0 on success, -1 on failure
 */
char *path_finder(char **argv, path_t *path_list, char *str)
{
	char *path;
	char *cmd = NULL;
	struct stat st;

	if (argv[0] == NULL)
		return (NULL);
	if (_strcmp(argv[0], "exit"))
	{
		__exit(cmd, argv, str, path_list);
		return (NULL);
	}
	if (builtin_functions(argv))
		return (NULL);
	if (argv[0][0] != '/')
	{
		cmd = argv[0];
		path = get_node(path_list, cmd);
	}
	else
	{
		if ((stat(argv[0], &st) == 0))
		{
			path = malloc(sizeof(char) * _strlen(argv[0]));
			path = _strcpy(path, argv[0]);
		}
		else
			path = NULL;
	}
	return (path);
}

