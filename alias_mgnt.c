#include "shell.h"

/**
 * display_aliases - display all aliases or an individual alias
 * @shell_data: struct for the shell's data
 * @alias_name: name of the alias to be displayed
 *
 * Return: 0 on success, -1 on failure
 */
int display_aliases(shell_data *data, char *alias_name)
{
    int i, j, alias_name_len;
    char buffer[250] = {0};

    if (shell_data->aliases)
    {
        alias_name_len = strlen(alias_name);
        for (i = 0; shell_data->aliases[i]; i++)
        {
            if (!alias_name || (strncmp(shell_data->aliases[i], alias_name, alias_name_len) == 0
                && shell_data->aliases[i][alias_name_len] == '='))
            {
                for (j = 0; shell_data->aliases[i][j]; j++)
                {
                    buffer[j] = shell_data->aliases[i][j];
                    if (shell_data->aliases[i][j] == '=')
                        break;
                }
                buffer[j + 1] = '\0';
                buffer_append(buffer, "'");
                buffer_append(buffer, shell_data->aliases[i] + j + 1);
                buffer_append(buffer, "'\n");
                _print(buffer);
            }
        }
    }

    return (0);
}

/**
 * get_alias_value - get the value of an alias
 * @shell_data: struct for the shell's data
 * @alias_name: name of the requested alias
 *
 * Return: value of the alias if found, otherwise NULL
 */
char *get_alias_value(shell_data *data, char *alias_name)
{
    int i, alias_name_len;

    if (alias_name == NULL || shell_data->aliases == NULL)
        return (NULL);

    alias_name_len = strlen(alias_name);

    for (i = 0; shell_data->aliases[i]; i++)
    {
        if (strncmp(alias_name, shell_data->aliases[i], alias_name_len) == 0 &&
            shell_data->aliases[i][alias_name_len] == '=')
        {
            return (shell_data->aliases[i] + alias_name_len + 1);
        }
    }

    return (NULL);
}

int set_alias(char *alias_string, shell_data *shell_data) {
    int i, j;
    char buffer[250] = {0}, *temp = NULL;

    // check for valid arguments
    if (alias_string == NULL || shell_data->aliases == NULL)
        return -1;

    // extract alias name and value
    for (i = 0; alias_string[i] != '\0'; i++) {
        if (alias_string[i] != '=') {
            buffer[i] = alias_string[i];
        } else {
            temp = get_alias_value(shell_data, alias_string + i + 1);
            break;
        }
    }

    // check if alias already exists
    for (j = 0; shell_data->aliases[j] != NULL; j++) {
        if (strncmp(buffer, shell_data->aliases[j], i) == 0 &&
            shell_data->aliases[j][i] == '=') {
            free(shell_data->aliases[j]);
            break;
        }
    }

    // add the alias
    if (temp != NULL) {
        buffer_append(buffer, "=");
        buffer_append(buffer, temp);
        shell_data->aliases[j] = strdup(buffer);
    } else {
        shell_data->aliases[j] = strdup(alias_string);
    }

    return 0;
}
