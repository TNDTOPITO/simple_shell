#ifndef SHELL_H
#define SHELL_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>

/**
 * struct path_s - singly linked list
 * @path: Path to directory
 * @next: Pointer to the next node
 *
 * Description - This struct contains all of the directories in the PATH
(* variable
 */
typedef struct path_s
{
	char *path;
	struct path_s *next;
} path_t;

extern char **environ;


int _printf(const char *format, ...);

char **str_to_arr(char *str);

path_t *path(void);

path_t *creat_list(char *path);

void free_list(path_t *head);

size_t _strlen(char *str);

char *_strcat(char *dest, char *src);

char *_strcpy(char *dest, char *src);

char  *path_finder(char **argv, path_t *path_list);

char *get_node(path_t *path_list, char *cmd);

char *_realloc(char *ptr, unsigned int old_size, unsigned int new_size);

#endif /* SHELL_H */
