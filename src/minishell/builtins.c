#include "minishell.h"

void builtin_echo(char *args[])
{
	int i;
	int no_newline;

	i = 1;
	no_newline = 0;

	if (args[i] != '\0' && ft_strncmp(args[i], "-n", 2) == 0)
	{
		no_newline = 1;
		i++;
	}

	while (args[i] != '\0')
	{
		printf("%s", args[i]);
		i++;
		if (args[i] != '\0')
			printf(" ");
	}
	if (!no_newline)
		printf("\n");
}

void	builtin_cd(char *args[])
{
	if (args[1] != NULL)
	{
		if (chdir(args[1]) != 0)
			perror("cd");
		else
			chdir(getenv("HOME"));
	}
}

void	builtin_pwd()
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}



void builtin_unset(char *args[]) {
    // Implement the logic to unset environment variables
}

void builtin_env()
{
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

void builtin_exit()
{
    // Optionally, handle cleanup tasks here
    exit(0);
}


