#include "shell.h"


/**
 * or - This function handles the "||" logical operator
 * @str: String
 *
 * Return: exit code
 */
int or(char *str)
{
	int code = 0;
	char *temp, *token;

	token = _strtok3(str, "|\n");
	while (token != NULL)
	{
		temp = malloc(sizeof(char) * (_strlen(token) + 2));
		temp = _strcpy(temp, token);
		if (code == 0)
		{
			free(temp);
			break;
		}
		token = _strtok3(NULL, "|\n");
		free(temp);
	}
	return (code);
}

/**
 * and - This function handles the "&&" logical operator
 * @str: String
 *
 * Return: exit code
 */
int and(char *str)
{
	int code = 0;
	char *temp, *token;

	token = _strtok2(str, "&\n");
	while (token != NULL)
	{
		temp = malloc(sizeof(char) * (_strlen(token) + 2));
		temp = _strcpy(temp, token);
		if (code != 0)
		{
			free(temp);
			break;
		}
		token = _strtok2(NULL, "&\n");
		free(temp);
	}
	return (code);
}

/**
 * special_circ - This function handles ";", "&&" and "||"
 * @path_list: linked list path
 * @str: String
 *
 * Return: 0 if found 1 if not found
 */
int special_circ(char *str)
{
	int i, code, w_len, execFlag;
	int exec = 0;
	char *token;
	char **argv;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == ';')
			exec = 1;
		if (str[i] == '&' && str[i + 1] == '&')
			exec = 2;
		if (str[i] == '|' && str[i + 1] == '|')
		{
			exec = 3;
		}
	}
	if (exec == 0)
		return (-1);
	if (exec == 1)
	{
		token = _strtok1(str, ";\n");
		while (token != NULL)
		{
			w_len = count_input(token);
			if (token[0] != '\n' && w_len > 0)
			{
				argv = tokenize(token, " \t\0", w_len);
				execFlag = builtin_functions(argv, token); 
				if (!execFlag)
				{
					argv[0] = find(argv[0]);
					if (argv[0] && access(argv[0], X_OK) == 0)
						code = execute(argv[0], argv);
					else
						perror("./hsh");
				}
				frees_tokens(argv);
			}
			token = _strtok1(NULL, ";\n");
		}
	}
	if (exec == 2)
	{
		code = and(str);
	}
	if (exec == 3)
	{
		code = or(str);
	}
	return (code);
}

/**
 * execute - This function executes the program
 * @cmd: Command
 * @argv: Arguments
 *
 * Return: exit code
 */
int execute(char *cmd, char **argv)
{
	pid_t pro;

	int wstatus;
	int statusCode;

	pro = fork();
	if (pro == -1)
		perror("fork failed");
	else if (pro == 0)
		execve(cmd, argv, environ);
	else
	{
		do {
			waitpid(pro, &wstatus, WUNTRACED);
		} while (WIFEXITED(wstatus) == 0 && WIFSIGNALED(wstatus) == 0);
	}
	statusCode = WEXITSTATUS(wstatus);
	return (statusCode);
}
