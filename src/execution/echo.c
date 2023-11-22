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

int	execute_echo(char *args[], int fd_out)
{
	int		no_newline;
	int		i;

	i = 1;

	no_newline = 0;
	echo_handle_option(&args, &no_newline);
	while (args[i] && args[i][0] != '\0')
	{
		if (i == 1)
			ft_putstr_fd(args[i], fd_out);
		else
		{
			ft_putstr_fd(" ", fd_out);
			ft_putstr_fd(args[i], fd_out);
		}
		i++;
	}
	if (!no_newline)
		ft_putstr_fd("\n", fd_out);
	return (0);
}