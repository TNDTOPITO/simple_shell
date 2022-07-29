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
	char *str = NULL;
	pid_t pro;
	int res;
	size_t num = 0;
	struct stat st;

	while (1)
	{
		printf("$ ");
		res = getline(&str, &num, stdin);
		if (res == -1)
			break;
		argv = str_to_arr(str);
		res = stat(argv[0], &st);
		if (res == 0)
		{
			pro = fork();
			if (pro == 0)
			{
				execve(argv[0], argv, environ);
			}
			else
			{
				wait(NULL);
			}
		}
		else
		{
			printf("%s: Command not found\n", argv[0]);
		}
		free(argv);
	}
	free(str);
	return (0);
}
