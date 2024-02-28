#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for buffer size/flush */
#define BUF_SIZE 1024
#define BUF_FLUSH -1


/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, 0, 0, NULL, 0}

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains arguements to pass into a function,
 *@args: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@env_changed: on if environ was changed
 *@status: the return status of the last executed command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@readfd: the fd from which to read line input
 */
typedef struct passinfo
{
	char *args;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; /* pointer to cmd */
	int readfd;
} info_t;


/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* main.c */
int shell(info_t *, char **);
int if_interactive(info_t *);

/* built_in.c */
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);

/* errors.c */
void err_puts(char *);
int err_putchar(char);
int err_atoi(char *);
void print_error(info_t *, char *);
int puts_d(int input, int fd);

/* strings_1.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);

/* strings_2.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
int _atoi(char *);
char **strtow(char *, char *);

/* output.c */
void _puts(char *);
int _putchar(char);

/* memory.c */
int bfree(void **);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
void free_list(list_t **);

/* tools.c */
char *dup_chars(char *, int, int);
int is_delim(char, char *);
char *starts_with(const char *, const char *);
char *dup_chars(char *, int, int);
char *convert_number(long int, int, int);


/* builtin.c */
int my_exit(info_t *);
int my_cd(info_t *);
int my_env(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);


/* input.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);

/* get_info.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environ.c */
char **get_environ(info_t *);
char *_getenv(info_t *, const char *);
int new_env_list(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* lists_1.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_at_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);

/* lists_2.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

#endif
