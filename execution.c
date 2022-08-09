#include "shell.h"

/**
 * special_circ - This function handles ";", "&&" and "||"
 * @path_list: linked list path
 * @str: String
 *
 * Return: 0 if found 1 if not found
 */
int special_circ(path_t *path_list, char *str)
{
	int i, code;
	int exec = 1;
	char *token;
	char *temp;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == ';')
			exec = 0;
	}
	if (exec)
		return (-5);
	token = _strtok1(str, ";\n");
	while (token != NULL)
	{
		temp = malloc(sizeof(char) * (_strlen(token) + 2));
		temp = _strcpy(temp, token);
		code = command_sep(path_list, temp);
		token = _strtok1(NULL, ";\n");
		free(temp);
	}
	return (code);
}

/**
 * command_sep - This function handles command separator
 * @path_list: linked list path
 * @str: String
 *
 * Return: exit code
 */
int command_sep(path_t *path_list, char *str)
{
	int exit_status;
	char *cmd = NULL;
	char **argv;

	argv = str_to_arr(str);
	cmd = path_finder(argv, path_list, str);
	if (cmd != NULL)
		exit_status = execute(cmd, argv);
	else if (argv[0] != NULL && !(check_builtin(argv)))
		_printf("%s: command not found\n", argv[0]);
	free(cmd);
	free(argv);

	return (exit_status);
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
	if (pro == 0)
		execve(cmd, argv, enviroment);
	else
		wait(&wstatus);
	statusCode = WEXITSTATUS(wstatus);
	return (statusCode);
}
