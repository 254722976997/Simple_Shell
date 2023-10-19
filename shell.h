#ifndef  _SHELL_H_
#define  _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>


#define BUFSIZE 1024
#define TOK_DELIM " \t\r\n\a"
#define TOK_BUFSIZE 128


/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	int status;
char **args;
	char *pid;
	int counter;
	char **_environ;
	
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/* lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_line_list(line_list **head);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);


/* lists2.c */
void free_rvar_list(r_var **head);
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);


/* str functions */
char *_strcat(char *dest, const char *src);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);

/* mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* str3.c */
void rev_string(char *s);


/* str2.c */
char *_strdup(const char *s);
int _isdigit(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _strlen(const char *s);


/* check_syntax_error.c */
int repeated_char(char *input, int i);
int first_char(char *input, int *i);
int check_syntax_error(data_shell *datash, char *input);
int error_sep_op(char *input, int i, char last);
void print_syntax_error(data_shell *datash, char *input, int i, int bool);


/* shell_loop.c */
void shell_loop(data_shell *datash);
char *without_comment(char *in);


/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_char(char *input, int bool);
char **split_line(char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
int split_commands(data_shell *datash, char *input);


/* rep_var.c */
void check_env(r_var **h, char *in, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *rep_var(char *input, data_shell *datash);

/* get_line.c */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);


/* exec_line */
int exec_line(data_shell *datash);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
int cmd_exec(data_shell *datash);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *datash);
int check_error_cmd(char *dir, data_shell *datash);


/* env1.c */
int _env(data_shell *datash);
char *_getenv(const char *name, char **_environ);


/* env2.c */
int _unsetenv(data_shell *datash);
void set_env(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
char *copy_info(char *name, char *value);

/* cd.c */
void cd_previous(data_shell *datash);
void cd_dot(data_shell *datash);
void cd_to(data_shell *datash);
void cd_to_home(data_shell *datash);

/* cd_shell.c */
int cd_shell(data_shell *datash);

/* get_builtin */
int (*get_builtin(char *cmd))(data_shell *datash);

/* _exit.c */
int exit_shell(data_shell *datash);

/* stdlib.c */
int get_len(int n);
int _atoi(char *s);
char *aux_itoa(int n);


/* error1.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_exit_shell(data_shell *datash);
char *error_get_cd(data_shell *datash);
char *error_not_found(data_shell *datash);


/* error2.c */
char *error_path_126(data_shell *datash);
char *error_env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_get_alias(char **args);


/* get_error.c */
int get_error(data_shell *datash, int eval);

/* get_sigint.c */
void get_sigint(int sig);

/* help.c */
void aux_help_unsetenv(void);
void aux_help_env(void);
void aux_help_exit(void);
void aux_help_setenv(void);
void aux_help_general(void);


/* help2.c */
void aux_help(void);
void aux_help_cd(void);
void aux_help_alias(void);


/* get_help.c */
int get_help(data_shell *datash);

#endif

