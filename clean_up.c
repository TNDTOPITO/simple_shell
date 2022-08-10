#include "shell.h"

/**
 * free_list - This function frees memory of a linked list
 * @head: Address of list to free
 *
 */
void free_list(path_t *head)
{
	path_t *h;

	while (head)
	{
		h = head->next;
		free(head->path);
		free(head);
		head = h;
	}
}

/**
 * free_ac - This function frees memory that was allocated to cmd and argv
 * @cmd: Pointer to the memory
 * @argv: Pointer to the memory
 */
void free_ac(char *cmd, char **argv)
{
	free(cmd);
	free(argv);
}

/**
 * free_sl - This function frees memory that was allocated to the linked list
 * and str
 * @str: Pointer to the memory
 * @path_list: Pointer to the memory
 */
void free_sl(char *str, path_t *path_list)
{
	int i;

	for (i = 0; enviroment[i]; i++)
	{
		free(enviroment[i]);
	}
	free(enviroment);
	if (str)
		free(str);
	free_list(path_list);
}

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
void __exit(char *cmd, char **argv, char *str, path_t *path_list)
{
	int status;

	if (!argv[1])
		status = 0;
	else
		status = _atoi(argv[1]);
	if (status == -1)
	{
		_printf("sh: 1: exit: Illegal number: %s\n", argv[1]);
		return;
	}
	free_ac(cmd, argv);
	free_sl(str, path_list);
	exit(status);
}
