#include "shell.h"

/**
 * simple_shell - This function executes a commands from file
 * @str: Name of file
 */
void simple_shell(char *string)
{
	FILE *fp;
	struct stat sb;
	char **argv, *str;
	int res, execFlag, w_len;
	size_t num = 0;

	if (!string)
		return;
	if (stat(string, &sb) != 0)
		return;
	while (1)
	{
		fp = fopen(string, "r");
		if (fp == NULL)
			return;
		res = getline(&str, &num, fp);
		if (res == -1)
			break;
		execFlag = special_circ(str);
		if (execFlag == -1)
		{
			w_len = count_input(str);
			if (str[0] != '\n' && w_len > 0)
			{
				argv = tokenize(str, " \t", w_len);
				execFlag = builtin_functions(argv, str);
				if (!execFlag)
				{
					argv[0] = find(argv[0]);
					if (argv[0] && access(argv[0], X_OK) == 0)
						execute(argv[0], argv);
					else
						perror("./hsh");
				}
				frees_tokens(argv);
			}
		}
	}
	free(str);
}
