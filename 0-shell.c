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

		/* execute command */
		if (execute_commmand(args) == -1)
		{
			printf("Failed to execute command\n");
		}
	}

	return (0);
}
