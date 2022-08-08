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

char **enviroment;

int _putchar(char c);

int _printf(const char *format, ...);

char **str_to_arr(char *str);

path_t *path(void);

path_t *creat_list(char *path);

void free_list(path_t *head);

size_t _strlen(char *str);

char *_strcat(char *dest, char *src);

char *_strcpy(char *dest, char *src);

char  *path_finder(char **argv, path_t *path_list, char *str);

char *get_node(path_t *path_list, char *cmd);

int _strcmp(char *s1, char *s2);

char *_realloc(char *ptr, unsigned int old_size, unsigned int new_size);

void free_ac(char *cmd, char **argv);

void free_sl(char *str, path_t *path_list);

void __exit(char *cmd, char **argv, char *str, path_t *path_list);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

char *_strtok(char *str, const char *delim);

void cpyEnviron(void);

void print_env(void);

int find_var(char *var_name);

void _setenv(char **argv);

void creat_var(char **argv);

void modify_var(char **argv, int i);

void _unsetenv(char **argv);

void cd(char **argv);

#endif /* SHELL_H */
