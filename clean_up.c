#include "shell.h"

/**
 * _atoi - This function converts string to integer
 * @s: String to be converted
 *
 * Return: an integer
 */
int _atoi(char *s)
{
	int noElements = _strlen(s), i;
	int num = 0;

	for (i = 0; i < noElements; i++)
	{
		if (!(s[i] >= 48 && s[i] <= 57))
			return (-1);
		num = (num * 10) + (s[i] - 48);
	}
	return (num);
}

/**
 * __exit - This function exits the program and frees all allocated memory
 * @cmd: Pointer to string
 * @argv: Pointer to string
 * @str: Pointer to string
 * @path_list: Pointer to a linked list
 */
void __exit(char **argv, char *str)
{
	int status;

	if (!argv[1])
		status = exit_status;
	else
		status = _atoi(argv[1]);
	if (status == -1)
	{
		fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", argv[1]);
		exit_status = 2;
		return;
	}
	free(str);
	frees_tokens(argv);
	exit(status);
}
