#include "minishell.h"


void	echo_handle_option(char ***args, int *no_newline)
{
	char *arg;

	if (**args && !ft_strncmp(**args, "-n", 2))
	{
			arg = **args + 1;
			*no_newline = 1;
			while (*arg)
			{
				if (*arg != 'n')
				{
					*no_newline = 0;
					break;
				}
				arg++;
			}
			if (*no_newline)
				(*args)++;
	}
}

int	execute_echo(char *args[])
{
	int		no_newline;

	args++;
	no_newline = 0;
	echo_handle_option(&args, &no_newline);
	while (*args && *args[0] != '\0')
	{
		if (*(args + 1) && *(args + 1)[0] != '\0')
			ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(*args, STDOUT_FILENO);
		args++;
	}
	if (!no_newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}