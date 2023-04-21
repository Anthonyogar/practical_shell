#include "shell.h"

/**
 * execute_command - Execute the given command
 * @args: Arrays of command-line arguments
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **args)
{
	char *path, *token;
	char *dirs[1024];
	int i, found = 0;

	if (access(args[0], X_OK) == 0)
	{
		found = 1;
	}
	else
	{
		/* Search for command in PATH */
		path = _getenv("PATH");
		token = strtok(path, ":");
		i = 0;
		while (token)
		{
			dirs[i] = token;
			token = strtok(NULL, ":");
			i++;
		}
		dirs[i] = NULL;

		for (i = 0; dirs[i]; i++)
		{
			path = _strcat(dirs[i], "/");
			path = _strcat(path, args[0]);
			if (access(path, X_OK) == 0)
			{
				args[0] = path;
				found = 1;
				break;
			}
			free(path);
		}
	}

	if (!found)
	{
		perror(args[0]);
		return (-1);
	}


	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, environ) == -1)
		{
			perror("execve");
			return (-1);
		}
	}
	else
	{
		/* Parent process */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (0);
}
