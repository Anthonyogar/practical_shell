#include "shell.h"

/**
 * execute - execute a command with its entire path variables.
 * @data: a pointer to the shell's data
 * Return: If success returns zero, otherwise, return -1.
 */
int execute(shell_data *data)
{
    int retval = 0, status;
    pid_t pid;

    /* check if program is a built-in command */
    retval = check_builtins(data);
    if (retval != -1) /* if program is a built-in command */
        return (retval);

    /* check if program exists in file system */
    retval = find_program(data);
    if (retval) /* if program not found */
        return (retval);
    else /* if program found */
    {
        pid = fork(); /* create a child process */
        if (pid == -1)
        { /* if the fork call failed */
            perror(data->tokens[0]);
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        { /* I am the child process, I execute the program*/
            retval = execve(data->program_path, data->tokens, data->env);
            if (retval == -1) /* if error when execve*/
            {
                perror(data->tokens[0]);
                exit(EXIT_FAILURE);
            }
        }
        else
        { /* I am the parent process, I wait and check the exit status of the child */
            wait(&status);
            if (WIFEXITED(status))
                errno = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                errno = 128 + WTERMSIG(status);
        }
    }
    return (0);
}
