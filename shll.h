Part1 
#ifndef _SHELL_H_
#define _SHELL_H_

// Header files
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

// Constants
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

// External variables
extern char **environ;

// Structures
typedef struct liststr {
    int num;
    char *str;
    struct liststr *next;
} list_t;

typedef struct passinfo {
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int env_changed;
    int status;
    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} info_t;

typedef struct builtin {
    char *type;
    int (*func)(info_t *);
} builtin_table;

// Function prototypes
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

// Macro definition
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
        0, 0, 0}

#endif /* _SHELL_H_ */
Part2
/* toem_parser.h */
#ifndef TOEM_PARSER_H
#define TOEM_PARSER_H

#include "toem_types.h"

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

#endif

/* loophsh.h */
#ifndef LOOPHSH_H
#define LOOPHSH_H

int loophsh(char **);

#endif

/* toem_errors.h */
#ifndef TOEM_ERRORS_H
#define TOEM_ERRORS_H

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

#endif

/* toem_string.h */
#ifndef TOEM_STRING_H
#define TOEM_STRING_H

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

#endif

/* toem_string1.h */
#ifndef TOEM_STRING1_H
#define TOEM_STRING1_H

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

#endif

/* toem_exits.h */
#ifndef TOEM_EXITS_H
#define TOEM_EXITS_H

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

#endif

/* toem_tokenizer.h */
#ifndef TOEM_TOKENIZER_H
#define TOEM_TOKENIZER_H

char **strtow(char *, char *);
char **strtow2(char *, char);

#endif

/* toem_realloc.h */
#ifndef TOEM_REALLOC_H
#define TOEM_REALLOC_H

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

#endif

/* toem_memory.h */
#ifndef TOEM_MEMORY_H
#define TOEM_MEMORY_H

int bfree(void **);

#endif

/* toem_atoi.h */
#ifndef TOEM_ATOI_H
#define TOEM_ATOI_H

int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

#endif

/* toem_errors1.h */
#ifndef TOEM_ERRORS1_H
#define TOEM_ERRORS1_H

int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

#endif

/* toem_builtin.h */
#ifndef TOEM_BUILTIN_H
#define TOEM_BUILTIN_H

int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

#endif

/* toem_builtin1.h */
#ifndef TOEM_BUILTIN1_H
#define TOEM_BUILTIN1_H

int _myhistory(info_t *);
int _myalias(info_t *);

#endif

/*toem_getline.h */
#ifndef TOEM_GETLINE_H
#define TOEM_GETLINE_H

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

#endif

/* toem_getinfo.h */
#ifndef TOEM_GETINFO_H
#define TOEM_GETINFO_H

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

#endif

/* toem_environ.h */
#ifndef TOEM_ENVIRON_H
#define TOEM_ENVIRON_H

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

#endif

/* toem_getenv

