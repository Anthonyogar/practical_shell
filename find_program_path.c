#include "shell.h"

int check_file(char *full_path);

/**
 * find_shell_command - find a shell command in PATH
 * @shell_data: a pointer to the shell data
 * Return: 0 if success, error code otherwise
 */
int find_shell_command(shell_data *data)
{
    int i = 0, ret_code = 0;
    char **directories;

    if (!data->command)
        return (2);

    /**if it's a full path or an executable in the same path */
    if (data->command[0] == '/' || data->command[0] == '.')
        return (check_file(data->command));

    free(data->argv[0]);
    data->argv[0] = str_concat(str_duplicate("/"), data->command);
    if (!data->argv[0])
        return (2);

    directories = tokenize_path(data); /* search in the PATH */

    if (!directories || !directories[0])
    {
        errno = 127;
        return (127);
    }

    for (i = 0; directories[i]; i++)
    {   /* append the command to path */
        directories[i] = str_concat(directories[i], data->argv[0]);
        ret_code = check_file(directories[i]);

        if (ret_code == 0 || ret_code == 126)
        {   /* the file was found, is not a directory and has execute permisions */
            errno = 0;
            free(data->argv[0]);
            data->argv[0] = str_duplicate(directories[i]);
            free_array_of_pointers(directories);
            return (ret_code);
        }
    }

    free(data->argv[0]);
    data->argv[0] = NULL;
    free_array_of_pointers(directories);
    return (ret_code);
}

/**
 * tokenize_path - tokenize the PATH in directories
 * @shell_data: a pointer to the shell data
 * Return: array of directories in PATH
 */
char **tokenize_path(shell_data *data)
{
    int i = 0;
    int counter_directories = 2;
    char **tokens = NULL;
    char *PATH;

    /* get the PATH value */
    PATH = env_get_key("PATH", data);
    if ((PATH == NULL) || PATH[0] == '\0')
    {   /* PATH not found */
        return (NULL);
    }

    PATH = str_duplicate(PATH);

    /* find the number of directories in the PATH */
    for (i = 0; PATH[i]; i++)
    {
        if (PATH[i] == ':')
            counter_directories++;
    }

    /* reserve space for the array of pointers */
    tokens = malloc(sizeof(char *) * counter_directories);

    /* tokenize and duplicate each token of PATH */
    i = 0;
    tokens[i] = str_duplicate(_strtok(PATH, ":"));
    while (tokens[i++])
    {
        tokens[i] = str_duplicate(_strtok(NULL, ":"));
    }

    free(PATH);
    PATH = NULL;
    return (tokens);
}

/**
 * check_file - checks if a file exists, is not a directory,
 * and has execution permissions.
 *
 * @path: the path to the file
 * Return: 0 if the file exists and has execution permissions,
 * or an error code otherwise
 */
int check_file(char *path)
{
	struct stat sb;

	if (stat(path, &sb) == -1) {
		/* If the file does not exist */
		errno = ENOENT;
		return -1;
	}

	if (S_ISDIR(sb.st_mode) || (sb.st_mode & S_IXUSR) == 0) {
		/* If the file is a directory or does not have execute permission */
		errno = EACCES;
		return -1;
	}

	return 0;
}
