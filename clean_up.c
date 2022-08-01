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
	free(str);
	free_list(path_list);
	_putchar('\n');
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
	free(cmd);
	free(argv);
	free(str);
	free_list(path_list);
	exit(0);
}
