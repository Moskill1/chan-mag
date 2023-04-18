#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_NUM_ARGUMENTS 64

	int main(void)
	{
	char input[MAX_COMMAND_LENGTH];
	char *args[MAX_NUM_ARGUMENTS];

	while (1)
	{
	printf("Enter a command: ");
	fgets(input, MAX_COMMAND_LENGTH, stdin);

	/* Remove trailing newline character*/
	if (input[strlen(input) - 1] == '\n')
	{
	input[strlen(input) - 1] = '\0';
	}

	/* Tokenize input into arguments*/
	char *token = strtok(input, " ");
	int i = 0;
	while (token != NULL)
	{
	args[i++] = token;
	token = strtok(NULL, " ");
	}
	args[i] = NULL;

	/* Fork a child process*/
	pid_t pid = fork();

	if (pid == 0)
	{
	/* Child process*/

	xecvp(args[0], args);
	perror("execvp");
	exit(1);
	}
	else if (pid < 0)
	{
	/* Error forking*/
	perror("fork");
	exit(1);
	}
	else
	{
	/* Parent process*/
	int status;
	waitpid(pid, &status, 0);
	}
	}
	return (0);
}
