#include "shell.h"

/**
 * main - entry point
 *
 * Return: 0 on success, non-zero on failure
 */
int main(void)
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("$ ");

		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL )
		{
			if (feof(stdin))
			{
				exit(0);
			}
			else
			{
				perror("fgets");
				exit(1);
			}
		}

		/* Remove newline character */
		buffer[strcspnz(buffer, "\n")] = '\0';

		/* chacks if command is an executable file */
		if (access(buffer, X_OK) == -1)
		{
			printf("%s: command not found\n", buffer);
			continue;
		}

		/* Fork child process */
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			/* Child process */
			if (execve(buffer, NULL, environ) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		else
		{
			/* Parent process */
			wait(NULL);
		}
	}

	return (0);
}
