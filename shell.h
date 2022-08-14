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

char **aliase;

void alias(char **argv);

void free_env(void);

void cpyEnviron(void);

int exit_status;

void signal_handler(int sig_id);

int _putchar(char c);

int _printf(const char *format, ...);

size_t _strlen(char *str);

char *_strcat(char *dest, char *src);

char *_strcpy(char *dest, char *src);

int _strcmp(char *s1, char *s2);

char *_realloc(char *ptr, unsigned int old_size, unsigned int new_size);

void __exit(char **argv, char *str);

void print_env(void);

char *chk_str(char *token);

/*int find_var1(char *var_name);*/

int find_var1(void);

int find_var(char *var_name, char **arr);

void _setenv(char **argv);

void creat_var(char **argv);

void modify_var(char **argv, int i);

void _unsetenv(char **argv);

void cd(char **argv);

int check_builtin(char **argv);

int execute(char *cmd, char **argv);

int command_sep(path_t *path_list, char *str);

int special_circ(char *str);

void simple_shell(char *string);

char *_strtok1(char *str, const char *delim);

char *_strtok2(char *str, const char *delim);

char *_strtok3(char *str, const char *delim);

void frees_tokens(char **tokns);

char *find(char *cname);

char **tokenize(char *str, char *del, int len);

int count_input(char *str);

char *concat_path(char *pathname, char *progname);

int count_delims(char *str, char *del);

char *_getenv(char *name);

int _strncmp(const char *s1, const char *s2, size_t len);

char *remove_new_line(char *str);

int builtin_functions(char **argv, char *str);

char *fnd_path(char *str);

#endif /* SHELL_H */
