#include "shell.h"

/**
 * main - Entry point
 * @ac: Number of argumenents
 * @av: Arguments
 *
 * Description: Simple shell project
 *
 * Return: Always 0
 */
int main(int ac, char **av)
{
	char **argv, *str = NULL;
	int res, execFlag, w_len;
	size_t num = 0;

	if (ac == 2)
		simple_shell(av[1]);
	cpyEnviron();
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
		execFlag = special_circ(str);
		if (execFlag == -1)
		{
			w_len = count_input(str);
			if (str[0] != '\n' && w_len > 0)
			{
				argv = tokenize(str, " \t", w_len);
				execFlag = builtin_functions(argv, str);
				if (!execFlag)
				{
					argv[0] = find(argv[0]);
					if (argv[0] && access(argv[0], X_OK) == 0)
						execute(argv[0], argv);
					else
						perror("./hsh");
				}
				frees_tokens(argv);
			}
		}
	}
	free(str);
	free_env();
	frees_tokens(aliase);
	return (exit_status);
}
