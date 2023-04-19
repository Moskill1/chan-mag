#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * main - simple shell program
 *
 * Return: Always 0
 */
int main(void)
{
    char *buffer;
    size_t bufsize = 32;
    ssize_t nread;
    char *token;
    const char delim[] = " \n\t";
    pid_t pid;

    buffer = malloc(bufsize * sizeof(char));
    if (buffer == NULL)
    {
        perror("Error: Unable to allocate buffer");
        exit(1);
    }

    while (1)
    {
        printf("$ ");
        nread = getline(&buffer, &bufsize, stdin);
        if (nread == -1)
            break;
        if (strcmp(buffer, "exit\n") == 0)
            break;
        token = strtok(buffer, delim);
        pid = fork();
        if (pid == 0)
        {
            execve(token, &token, NULL);
            perror("Error: execve failed");
            exit(1);
        }
        else
        {
            wait(NULL);
        }
    }
    free(buffer);
    return (0);
}

