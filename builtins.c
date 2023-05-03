#include "shell.h"

/**
 * Terminate the shell program with the given status.
 * @shell_data: The data structure containing information about the shell.
 * Return: 0 on success, or another number if specified in the arguments.
 */
int builtin_exit(shell_data *data)
{
    int i;
    if (data->tokens[1] != NULL) {
        /* Check if the argument for exit is a number */
        for (i = 0; data->tokens[1][i]; i++) {
            if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
                && data->tokens[1][i] != '+') {
                /* If the argument is not a number */
                errno = 2;
                return 2;
            }
        }
        errno = _atoi(data->tokens[1]);
    }
    free_all_data(data);
    exit(errno);
}

/**
 * Change the current working directory.
 * @shell_data: The data structure containing information about the shell.
 * Return: 0 on success, or another number if specified in the arguments.
 */
int builtin_cd(shell_data *data)
{
    char *dir_home = env_get_key("HOME", data), *dir_old = NULL;
    char old_dir[128] = {0};
    int error_code = 0;
    if (data->tokens[1]) {
        if (str_compare(data->tokens[1], "-", 0)) {
            dir_old = env_get_key("OLDPWD", data);
            if (dir_old)
                error_code = set_work_directory(data, dir_old);
            _print(env_get_key("PWD", data));
            _print("\n");
            return error_code;
        }
        else {
            return set_work_directory(data, data->tokens[1]);
        }
    }
    else {
        if (!dir_home)
            dir_home = getcwd(old_dir, 128);
        return set_work_directory(data, dir_home);
    }
    return 0;
}

/**
 * Set the current working directory.
 * @shell_data: The data structure containing information about the shell.
 * @new_dir: The path to be set as the new working directory.
 * Return: 0 on success, or another number if specified in the arguments.
 */
int set_work_directory(shell_data *data, char *new_dir)
{
    char old_dir[128] = {0};
    int err_code = 0;
    getcwd(old_dir, 128);
    if (!str_compare(old_dir, new_dir, 0)) {
        err_code = chdir(new_dir);
        if (err_code == -1) {
            errno = 2;
            return 3;
        }
        env_set_key("PWD", new_dir, data);
    }
    env_set_key("OLDPWD", old_dir, data);
    return 0;
}

/**
 * Display information about the shell environment.
 * @shell_data: The data structure containing information about the shell.
 * Return: 0 on success, or another number if specified in the arguments.
 */
int builtin_help(shell_data *data)
{
    int i, length = 0;
    char *messages[6] = {NULL};
    messages[0] = HELP_MSG;

    /* Validate arguments */
    if (data->tokens[1] == NULL) {
        _print(messages[0] + 6);
        return 1;
    }
    if (data->tokens[2] != NULL) {
        errno = E2BIG;
        perror(data->command_name);
        return 5;
    }

    	/* Set up the help messages */
	messages[1] = CD_HELP_MSG;
	messages[2] = HELP_HELP_MSG;
	messages[3] = EXIT_HELP_MSG;
	messages[4] = ENV_HELP_MSG;
	messages[5] = ALIAS_HELP_MSG;

	/* Check if a specific command was requested */
	for (i = 1; i <= 5; i++)
	{
    		if (str_compare(data->tokens[1], COMMANDS[i-1], 0) == 0)
		{
        		_print(messages[i]);
        		return 0;
    		}
	}

	/* If the requested command was not found, print the default message */
	_print(messages[0] + 6);
	return 1;

}

/**
 * builtin_alias - Add, remove or show aliases.
 * @shell_data: The data structure containing information about the shell.
 * Return: 0 on success, or another number if specified in the arguments.
 */
int builtin_alias(shell_data *data)
{
    int i = 0;

    /* If there are no arguments, print all aliases */
    if (data->tokens[1] == NULL) {
        return print_alias(data, NULL);
    }

    /* If there are arguments, set or print each alias */
    while (data->tokens[++i]) {
        if (count_characters(data->tokens[i], "=")) {
            set_alias(data->tokens[i], data);
        } else {
            print_alias(data, data->tokens[i]);
        }
    }

    return 0;
}
