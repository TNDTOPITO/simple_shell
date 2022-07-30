#include "shell.h"

/**
 * _strcmp - This function compares two strings
 * @s1: 1st string to compare
 * @s2: 2nd string to compare
 *
 * Return: 1 if match, 0 i doesn't match
 */
int _strcmp(char *s1, char *s2)
{
	int index = 0;

	while (s1[index] && s2[index])
	{
		if (s1[index] != s2[index])
			return (0);
		index++;
	}
	return (1);
}

/**
 * _realloc - function that reallocates a memory
 * @ptr: memory to resize
 * @old_size: old size of the array
 * @new_size: new size of the array
 *
 * Return: Pointer to the new array
 */
char *_realloc(char *ptr, unsigned int old_size, unsigned int new_size)
{
	char *tempArr;
	unsigned int i;

	if (old_size == new_size)
		return (ptr);
	if (ptr == NULL)
	{
		tempArr = malloc(new_size);
		return (tempArr);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	tempArr = malloc(new_size);
	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			tempArr[i] = ((char *)ptr)[i];
	}
	else
	{
		for (i = 0; i < new_size; i++)
			tempArr[i] = ((char *)ptr)[i];
	}

	free(ptr);
	return (tempArr);
}
/**
 * _strcat - This function concatenates two strings
 * @dest: The base
 * @src: Pointer to a string to be added to dest
 *
 * Return: Pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	int lenDest = _strlen(dest);
	int index = 0;

	while (src[index] != '\0')
	{
		dest[lenDest] = src[index];
		lenDest++;
		index++;
	}
	dest[lenDest] = src[index];
	return (dest);
}

/**
 * _strlen - This function counts the number of characters
 * @str: Pointer to a string
 *
 * Return: Length of the string
 */
size_t _strlen(char *str)
{
	size_t i = 0;

	while (str[i])
		i++;
	return (i);
}

/**
 * _strcpy - This function copies string
 * @dest: Address of where to copy the string
 * @src: String to be coppied
 *
 * Return: The address of dest
 */
char *_strcpy(char *dest, char *src)
{
	int index = 0;

	while (1)
	{
		dest[index] = src[index];
		if (src[index] == '\0')
			break;
		index++;
	}
	return (dest);
}
