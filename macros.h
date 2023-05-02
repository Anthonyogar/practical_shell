#ifndef HELPERS_H
#define HELPERS_H

/* String prompt for shell */
#define PROMPT_MSG "$"

/* Macro for unused attributes */
#define UNUSED __attribute__((unused))

/* Buffer size for _getline */
#define BUFFER_SIZE 1024

/* Formatted help messages for built-in commands */
#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change the working directory.\n\n"\
"	With no arguments, change to the user's home directory.\n"
"	With the argument '-', change to the previous directory.\n\n"


#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit the shell.\n\n"\
"	Exit the shell with a status of N. If N is omitted, the exit status\n"\
"	is that of the last command executed.\n\n"

#define HELP_ENV_MSG "env=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	Delete a variable from the environment.\n\n"\
"	When there are not correct numbers of arguments, print an error message.\n\n"


#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Display information about built-in commands.\n\n"\
"	Displays brief summaries of built-in commands. If BUILTIN_NAME is\n"\
"	specified, gives detailed help on all commands matching BUILTIN_NAME,\n"\
"	otherwise, prints the list of built-in commands.\n\n"\
"	BUILTIN_NAME specifies a built-in command:\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"



#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	Delete a variable from the environment.\n\n"\
"	When there are not correct numbers of arguments, print an error message.\n\n"

#endif
