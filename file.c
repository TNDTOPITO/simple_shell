#include "shell.h"

/**
  * concat_path - Concatenate a path name and a program name
  * @pathname: The path name to concatenate with the program name
  * @progname: The program name to place in the path name
  *
  * Return: The path name concatenated with the program name
  */
char *concat_path(char *pathname, char *progname)
{
	int prog_len = 0, path_len = 0, new_sz = 0;

	prog_len = _strlen(progname);
	path_len = _strlen(pathname);
	new_sz = sizeof(char) * (path_len + prog_len + 2);
	pathname = _realloc(pathname, (path_len + 1), new_sz);
	if (!pathname)
		return (NULL);

	_strcat(pathname, "/");
	_strcat(pathname, progname);

	return (pathname);
}

/**
  * count_delims - Counts delimiters in a string
  * @str: The string that contains the delimiters
  * @del: The delimiters to will find in the string
  *
  * Return: The number of delimiters in the string
  */
int count_delims(char *str, char *del)
{
	int i = 0, j = 0, cw = 0;

	while (del[i])
	{
		j = 0;
		while (str[j])
		{
			if (str[j] == del[i])
				cw++;
			j++;
		}
		i++;
	}

	return (cw);
}

/**
  * _strncmp - Compares at most the first n bytes of str1 and str2
  * @s1: The first string
  * @s2: The second string
  * @len: The limit bytes of comparison
  *
  * Return: int value
  */
int _strncmp(const char *s1, const char *s2, size_t len)
{
	unsigned int pos = 0;
	int diff = 0;

	while (pos < len)
	{
		if (s1[pos] == s2[pos])
		{
			pos++;
			continue;
		}
		else
		{
			diff = s1[pos] - s2[pos];
			break;
		}

		pos++;
	}

	return (diff);
}

/**
  * _getenv - Gets an environment variable
  * @name: The variable to find in the system environment
  *
  * Return: The content of the environment variable
  */
char *_getenv(char *name)
{
	int i = 0;
	char *env_var = NULL;

	while (enviroment[i])
	{
		if (_strncmp(name, enviroment[i], _strlen(name)) == 0)
		{
			env_var = strdup(enviroment[i]);
			while (*env_var != '=')
				env_var++;

			++env_var;
			return (env_var);
		}
		i++;
	}

	return (NULL);
}

/**
  * remove_new_line - Removes a new line character from string
  * @str: The string
  *
  * Return: The string without a new line character
  */
char *remove_new_line(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}

	return (str);
}
