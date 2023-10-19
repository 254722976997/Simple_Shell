#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: number field
 * @str: string
 * @next: points to th next node
 * Description: structure for builtin commands and their associated functions
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;

} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * struct info_s - general parameters and return struct
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:argument vector
 * @path: path of executable
 * @argc: number of arguments
 * @line_count: command line
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @argv0: program name
 * @env: environment
 * @environ: custom modified copy of environ from LL env
 * @history: linked list of history
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	char **env;
	int argc;
	char *line;
	char *argv0;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	int _setenv;
	int _unsetenv;
	int puts;	
	char *fname;
	list_t *environment;
	list_t *list;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_modified;
	int env_changed;
	int cmd_buf_type;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int command_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int shell_loop(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* toem_parser.c */
int check_command(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_command_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void print_to_stderr(char *);
int print_char_to_stderr(char);
int print_char_to_fd(char c, int fd);
int print_to_fd(char *str, int fd);

/* toem_string.c */
int custom_strlen(char *);
int custom_strcmp(char *, char *);
char *starts_with_custom(const char *, const char *);
char *custom_strcat(char *, char *);

/* toem_string1.c */
char *copy_string(char *, char *);
char *duplicate_string(const char *);
void print_string(char *);
int write_character(char);

/* toem_exits.c */
char *custom_strncpy(char *, char *, int);
char *custom_strncat(char *, char *, int);
char *custom_strchr(char *, char);

/* toem_tokenizer.c */
char **split_string(char *, char *);
char **split_string2(char *, char);

/* toem_realloc.c */
char *custom_memset(char *, char, unsigned int);
void free_strings(char **);
void *custom_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int is_interactive_shell(info_t *);
int is_special_character(char, char *);
int is_alpha_character(int);
int parse_integer(char *);

/* toem_errors1.c */
int string_to_int(char *);
void print_error_message(info_t *, char *);
int print_integer(int, int);
char *convert_to_string(long int, int, int);
void replace_hash_with_null(char *);

/* toem_builtin.c */
int exit_shell(info_t *);
int change_directory(info_t *);
int display_help(info_t *);

/* toem_builtin1.c */
int displayHistory(info_t *,list_t *);
int aliasCommand(info_t *);

/*toem_getline.c */
ssize_t buffer_input(info_t *, char **, size_t *);
ssize_t get_user_input(info_t *);
ssize_t read_buffer(info_t *, char **, size_t *);
int custom_getline(info_t *, char **, size_t *);
void blockCtrlC(int);

/* toem_getinfo.c */
void initialize_info(info_t *);
void configure_info(info_t *, char **);
void release_info(info_t *, int);

/* toem_environ.c */
char *get_environment_value(info_t *, const char *);
int print_current_environment(info_t *);
int set_or_update_environment(info_t *);
int remove_environment_variable(info_t *);
int populate_environment_list(info_t *);


/* toem_getenv.c */
char **retrieve_environment(info_t *);
char **list_to_strings(list_t *);
char *starts_with(const char *, const char *);
size_t _strlen(const char *);
char *_strcpy(char *, const char *);
char *_strcat(char *, const char *);
int _removeenv(info_t *, char *, list_t *);
int _setenvironment(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_length(const list_t *);
char **list_to_array(list_t *);
size_t print_list_elements(const list_t *);
list_t *find_node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain_delim(info_t *, char *, size_t *);
void check_chain_continuation(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

