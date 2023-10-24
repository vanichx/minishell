#include "minishell.h"

void	exit_shell(char *message, int exit_code, t_data *data)
{
	printf("exit_shell function\n");
	free_data(data);
    ft_putstr_fd(message, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    exit(exit_code);
}
