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
 * add_node - This function adds a new node at the beginning of a linked list
 * @head: Address of linked list
 * @str: String to add
 *
 * Return: Appended list
 */
path_t *add_node(path_t **head, char *str)
{
	path_t *new;
	char *temp;

	new = malloc(sizeof(path_t));
	temp = malloc(sizeof(char) * _strlen(str) + 2);
	temp = _strcpy(temp, str);
	temp = _strcat(temp, "/");
	new->path = temp;
	new->next = *head;
	*head = new;

	return (*head);
}

/**
 * creat_list - This function creates a linked list
 * @path: pointer to a string with directories
 *
 * Return: Pointer to the head of the list
 */
path_t *creat_list(char *path)
{
	path_t *head;
	char *token;

	head = NULL;
	token = strtok(path, ":");
	while (token != NULL)
	{
		head = add_node(&head, token);
		token = strtok(NULL, ":\0");
	}
	return (head);
}

/**
 * get_node - This function locates a function in the PATH variable
 * @path_list: Linked list with the directories
 * @cmd: Command to search for
 *
 * Return: Pointer to the node with the correct directory, NULL on failure
 */
char *get_node(path_t *path_list, char *cmd)
{
	char *full_path;
	path_t *h;
	struct stat st;
	int size, new_size;

	h = path_list;
	size = sizeof(char) * (_strlen(h->path) + _strlen(cmd));
	full_path = malloc(size);
	while (h)
	{
		new_size = (sizeof(char) * _strlen(h->path)) + (sizeof(char) * _strlen(cmd));
		if (size <=  new_size)
		{
			full_path = _realloc(full_path, size, new_size + 1);
			size = new_size + 1;
		}
		_strcpy(full_path, h->path);
		_strcat(full_path, cmd);
		if ((stat(full_path, &st) == 0))
		{
			return (full_path);
		}
		h = h->next;
	}
	return (NULL);
}
