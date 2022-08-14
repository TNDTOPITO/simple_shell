#include "shell.h"
/**
 * frees_get_env - ...
 * @env_path: The environment variable to frees
 *
 * Return: Nothing to returns
 **/
void frees_get_env(char *env_path)
{
	int i;

	for (i = 4; i >= 0; i--)
		env_path--;

	free(env_path);
}
/**
  * frees_tokens - ...
  * @tokns: ...
  *
  * Return: Nothing to returns
  */
void frees_tokens(char **tokns)
{
	char **temp = tokns;

	if (tokns)
	{
		while (*tokns)
			free(*tokns++);

		free(temp);
	}
}

/**
  * find - Verify if a command is found in the system
  * @cname: The command name to find in the system
  *
  * Return: The path name of the command found or NULL if failed
  */
char *find(char *cname)
{
	char *env_path = NULL, **p_tokns = NULL;
	int i = 0, num_del = 0;
	struct stat sb;

	if (cname)
	{
		if (stat(cname, &sb) != 0 && cname[0] != '/')
		{
			env_path = _getenv("PATH");
			num_del = count_delims(env_path, ":") + 1;
			p_tokns = tokenize(env_path, ":", num_del);

			while (p_tokns[i])
			{
				p_tokns[i] = concat_path(p_tokns[i], cname);

				if (stat(p_tokns[i], &sb) == 0)
				{
					free(cname);
					cname = strdup(p_tokns[i]);
					frees_get_env(env_path);
					frees_tokens(p_tokns);
					return (cname);
				}

				i++;
			}

			frees_get_env(env_path);
			frees_tokens(p_tokns);
		}

		if (stat(cname, &sb) == 0)
			return (cname);
	}

	free(cname);
	return (NULL);
}

/**
  * count_input - Counts the words typed by the user
  * @str: The string that contains the words
  *
  * Return: The number of words found in the string
  */
int count_input(char *str)
{
	int i = 0, cw = 0, state = 0;

	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			state = 0;
		else if (state == 0)
		{
			state = 1;
			cw++;
		}

		i++;
	}

	return (cw + 3);
}
/**
  * tokenize - Extract tokens from string
  * @str: The string to tokenize
  * @del: The delimiter of tokenization
  * @len: Tokens number
  *
  * Return: An array of tokens of the string
  */
char **tokenize(char *str, char *del, int len)
{
	char **tokens = NULL, *token = NULL, *temp = NULL;
	int i = 0;

	tokens = malloc(sizeof(char *) * (len + 3));
	if (!tokens)
		return (NULL);

	str = remove_new_line(str);
	temp = strdup(str);
	token = strtok(temp, del);
	
	while (token)
	{
		tokens[i] = strdup(token);
		tokens[i] = chk_str(tokens[i]);
		token = strtok(NULL, del);
		i++;
	}

	tokens[i] = NULL;
	free(temp);
	return (tokens);
}
