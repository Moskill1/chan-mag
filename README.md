#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM    0
#define CMD_OR      1
#define CMD_AND     2
#define CMD_CHAIN   3

#define CONVERT_LOWERCASE   1
#define CONVERT_UNSIGNED    2

#define USE_GETLINE 0
#define USE_STRTOK  0

#define HIST_FILE   ".my_shell_history"
#define HIST_MAX    4096

extern char **environ;

typedef struct liststr list_t;
struct liststr {
    int num;
    char *str;
    struct liststr *next;
};

typedef struct passinfo info_t;
struct passinfo {
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
};

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
        0, 0, 0}

typedef struct builtin builtin_table;
struct builtin {
    char *type;
    int (*func)(info_t *);
};

int my_shell(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int my_shell_loop(char **);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int bfree(void **);

/* my_shell.h */

#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <stddef.h>
#include <unistd.h>

#define MAX_ARGS 128
#define MAX_BUFFER 1024

typedef struct {
    char *input_buffer;
    char **args;
    int num_args;
} Command;

int execute_command(Command *cmd);
void free_command(Command *cmd);

#endif

/* my_shell.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "my_shell.h"

int main(int argc, char **argv) {
    char input_buffer[MAX_BUFFER];
    int status = 0;

    while (1) {
        printf("my_shell> ");
        fflush(stdout);

        if (fgets(input_buffer, MAX_BUFFER, stdin) == NULL) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        Command *cmd = malloc(sizeof(Command));
        cmd->input_buffer = strdup(input_buffer);
        cmd->args = malloc(MAX_ARGS * sizeof(char*));
        cmd->num_args = 0;

        char *token = strtok(input_buffer, " \t\n");
        while (token != NULL && cmd->num_args < MAX_ARGS) {
            cmd->args[cmd->num_args++] = strdup(token);
            token = strtok(NULL, " \t\n");
        }

        status = execute_command(cmd);

        free_command(cmd);

        if (status != 0) {
            fprintf(stderr, "Command exited with status %d\n", status);
        }
    }

    return 0;
}

int execute_command(Command *cmd) {
    if (cmd->num_args == 0) {
        return 0;
    }

    if (strcmp(cmd->args[0], "exit") == 0) {
        exit(0);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Error forking process");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        execvp(cmd->args[0], cmd->args);
        perror("Error executing command");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status = 0;
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}

void free_command(Command *cmd) {
    free(cmd->input_buffer);
    for (int i = 0; i < cmd->num_args; i++) {
        free(cmd->args[i]);
    }
    free(cmd->args);
}

#endif
