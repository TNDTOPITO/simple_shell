#include "shell.h"

/**
 * main - Entry point
 *
 * Description: Simple shell project
 *
 * Return: Always 0
 */
int main(void)
{
	char **argv;
	char *str = NULL, *cmd;
	pid_t pro;
	int res;
	size_t num = 0;
	path_t *path_list;

	path_list = path();
	while (1)
	{
		_printf("$ ");
		res = getline(&str, &num, stdin);
		if (res == -1)
			break;
		argv = str_to_arr(str);
		cmd = path_finder(argv, path_list);
		if (cmd != NULL)
		{
			pro = fork();
			if (pro == 0)
				execve(cmd, argv, environ);
			else
				wait(NULL);
		}
		else if (argv[0] != NULL)
			_printf("%s: Command not found\n", argv[0]);
		free(cmd);
		free(argv);
	}
	_printf("\n");
	free(str);
	free_list(path_list);
	return (0);
}
