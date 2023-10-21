#include "minishell.h"

void	print_cmdexe(void *cmdexe_node)
{
    t_cmdexe	*cmdexe = (t_cmdexe *)cmdexe_node;

    printf("path: %s\n cmd: %s\n", cmdexe->path, cmdexe->cmd);
}