#include "shell.h"

/**
 * path - This function stores directories in the path variable on linked list
 *
 * Return: The address of the head
 */
path_t *path(void)
{
	char **env = environ;
	size_t i;
	size_t y = 0;
	char *var_name = "PATH", *path;
	size_t match = 0;
	path_t *head;

	for (i = 0; env[i] != NULL; i++)
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
		{
			path = env[i];
			break;
		}
		y = 0;
	}
	while (*path != '=')
		path++;
	path++;
	head = creat_list(path);
	return (head);
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
		__exit(cmd, argv, str, path_list);
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

