#include "minishell.h"

void	exit_shell(char *message, int exit_code)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(message, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    exit(exit_code);
}