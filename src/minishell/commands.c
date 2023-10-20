#include "minishell.h"

void	ft_lstadd_back_cmd(t_list **lst, t_cmdexe *cmd)
{
	t_list *new;
	t_list *tmp;

	if (!lst || !cmd)
		return ;
	new = ft_lstnew(cmd);
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void print_cmdexe_list(t_list *lst)
{
    t_list *tmp = lst;

    int i = 0;
    while (tmp) {
        t_cmdexe *cmd = (t_cmdexe *)tmp->content;
        printf("Command %d:\n", i);
        printf("  path: %s\n", cmd->path);
        printf("  cmd: %s\n", cmd->cmd);
        printf("  idx: %d\n", cmd->idx);
        tmp = tmp->next;
        i++;
    }
	
}