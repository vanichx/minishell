#include "minishell.h"

void	exit_shell(char *message, int exit_code, t_data *data)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(message, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
	free_data(data);
    exit(exit_code);
}