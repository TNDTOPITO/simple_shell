#include "shell.h"


/**
 * or - This function handles the "||" logical operator
 * @path_list: linked list path
 * @str: String
 *
 * Return: exit code
 *
int or(path_t *path_list, char *str)
{
	int code;
	char *temp, *token;

	token = _strtok3(str, "|\n");
	while (token != NULL)
	{
		temp = malloc(sizeof(char) * (_strlen(token) + 2));
		temp = _strcpy(temp, token);
		code = command_sep(path_list, temp);
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

**
 * and - This function handles the "&&" logical operator
 * @path_list: linked list path
 * @str: String
 *
 * Return: exit code
 *
int and(path_t *path_list, char *str)
{
	int code;
	char *temp, *token;

	token = _strtok2(str, "&\n");
	while (token != NULL)
	{
		temp = malloc(sizeof(char) * (_strlen(token) + 2));
		temp = _strcpy(temp, token);
		code = command_sep(path_list, temp);
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

**
 * special_circ - This function handles ";", "&&" and "||"
 * @path_list: linked list path
 * @str: String
 *
 * Return: 0 if found 1 if not found
 *
int special_circ(path_t *path_list, char *str)
{
	int i, code;
	int exec = 1;
	char *token;
	char *temp;

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
		return (-5);
	if (exec == 1)
	{
		token = _strtok1(str, ";\n");
		while (token != NULL)
		{
			temp = malloc(sizeof(char) * (_strlen(token) + 2));
			temp = _strcpy(temp, token);
			code = command_sep(path_list, temp);
			token = _strtok1(NULL, ";\n");
			free(temp);
		}
	}
	if (exec == 2)
	{
		printf("herr1\n");
		code = and(path_list, str);
	}
	if (exec == 3)
	{
		code = or(path_list, str);
	}
	return (code);
}

*/
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
