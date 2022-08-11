#include "shell.h"

/**
 * exec_line - This function executes a line
 * @str: Pointer to string
 */
void exec_line(char *str)
{
	char **argv;
	int execFlag, w_len;

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

/**
 * simple_shell - This function executes a commands from file
 * @string: Name of file
 */
void simple_shell(char *string)
{
	FILE *fp;
	char buffer[128];
	char *lineptr = NULL;
	int n = 20;

	fp = fopen(string, "r");
	if (!fp)
	{
		fprintf(stderr, "./hsh: 0: Can't open %s\n", string);
		exit(127);
	}
	lineptr = malloc(sizeof(char) * 20);
	lineptr[0] = '\0';
	while ((fgets(buffer, sizeof(buffer), fp)) != NULL)
	{
		if (n - _strlen(lineptr) < sizeof(buffer))
		{
			lineptr = _realloc(lineptr, n, n * 2);
			n *= 2;
			if (lineptr == NULL)
			{
				perror("Failed to allocate memory");
				free(lineptr);
				exit(127);
			}
		}
		_strcpy(lineptr, buffer);
		if ((lineptr)[_strlen(lineptr) - 1] == '\n')
			exec_line(lineptr);
	}
	fclose(fp);
	free(lineptr);
	exit(exit_status);
}
