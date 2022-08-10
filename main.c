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
	int res;
	size_t num = 0;
	path_t *path_list;
	int exit_status;

	cpyEnviron();
	path_list = path();
	while (1)
	{
		signal(SIGINT, signal_handler);
		if (isatty(STDIN_FILENO))
			_printf("$ ");
		res = getline(&str, &num, stdin);
		if (res == -1)
		{
			 if (isatty(STDIN_FILENO))
				_printf("\n");
			break;
		}
		exit_status = special_circ(path_list, str);
		if (exit_status == -5)
		{
			argv = str_to_arr(str);
			cmd = path_finder(argv, path_list, str);
			if (cmd != NULL && access(cmd, X_OK) == 0)
				exit_status = execute(cmd, argv);
			else if (argv[0] != NULL && !(check_builtin(argv)))
				perror("./hsh");
			free_ac(cmd, argv);
		}
	}
	free_sl(str, path_list);
	return (0);
}
