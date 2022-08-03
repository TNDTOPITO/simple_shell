#include "shell.h"

/**
 * _getline - This function reads line from a stream
 * @lineptr: Buffer to store string
 * @n: Size of buffer
 * @stream: File pointer
 *
 * Return: Number of lines read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char buffer[128];

	if (lineptr == NULL || n == NULL || stream == NULL)
	{
		perror("Bad arguments");
		return (-1);
	}
	if (*lineptr == NULL)
	{
		*n = sizeof(buffer);
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
		{
			perror("Unable to allocate memory");
			return (-1);
		}
	}
	(*lineptr)[0] = '\0';
	while ((fgets(buffer, sizeof(buffer), stream)) != NULL)
	{
		if (*n - _strlen(*lineptr) < sizeof(buffer))
		{
			*lineptr = _realloc(*lineptr, *n, *n * 2);
			*n *= 2;
			if (*lineptr == NULL)
			{
				perror("Failed to allocate memory");
				free(*lineptr);
				return (-1);
			}
		}
		_strcat(*lineptr, buffer);
		if ((*lineptr)[_strlen(*lineptr) - 1] == '\n')
			return (_strlen(*lineptr));
	}
	return (-1);
}
