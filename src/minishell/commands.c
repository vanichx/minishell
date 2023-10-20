#include "minishell.h"

void	print_cmdexe_list(t_cmdexe *cmdexe_list)
{
    ft_cmditer(cmdexe_list, &print_cmdexe);
}

void	print_cmdexe(void *cmdexe_node)
{
    t_cmdexe	*cmdexe = (t_cmdexe *)cmdexe_node;

    printf("path: %s\n cmd: %s\n idx: %d\n", cmdexe->path, cmdexe->cmd, cmdexe->idx);
}