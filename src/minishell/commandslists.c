#include "minishell.h"

void	ft_cmdadd_back(t_cmdexe **lst, t_cmdexe *new)
{
    t_cmdexe	*tmp;

    if (!*lst)
        *lst = new;
    else
    {
        tmp = ft_cmdlast(*lst);
		if (tmp)
		{
        	tmp->next = new;
        	new->prev = tmp;
		}
		else
			ft_cmdadd_front(lst, new);
    }
}

void	ft_cmdadd_front(t_cmdexe **lst, t_cmdexe *new)
{
    new->next = *lst;
    if (*lst != NULL)
        (*lst)->prev = new;
    *lst = new;
}

void	ft_cmdclear(t_cmdexe **lst, void (*del)(void *))
{
    t_cmdexe	*buffer;

    if (!lst || !*lst || !del)
        return ;
    while (*lst)
    {
        buffer = (*lst)->next;
        ft_cmddelone(*lst, del);
        *lst = buffer;
    }
}

void	ft_cmddelone(t_cmdexe *lst, void (*del)(void *))
{
    if (!lst || !del)
        return ;
    if (lst->path)
        free(lst->path);
    if (lst->cmd)
        free(lst->cmd);
    if (lst->flags)
        free(lst->flags);
    free(lst);
}

void	ft_cmditer(t_cmdexe *lst, void (*f)(void *))
{
    if (!f)
        return ;
    while (lst)
    {
        f(lst);
        lst = lst->next;
    }
}

t_cmdexe	*ft_cmdlast(t_cmdexe *lst)
{
    t_cmdexe	*node;
	
	node = lst;
    while (node != NULL)
	{
		while (node->next != NULL)
			node = node->next;
	}
    return (node);
}

t_cmdexe	*ft_cmdnew(char *path, char *cmd, t_flags *flags, int idx)
{
    t_cmdexe	*head;

    head = malloc(sizeof(t_cmdexe));
    if (!head)
        return (NULL);
    head->path = path;
    head->cmd = cmd;
    head->flags = flags;
    head->idx = idx;
    head->next = NULL;
    head->prev = NULL;
    return (head);
}

int	ft_cmdsize(t_cmdexe *lst)
{
    int	size;

    size = 0;
    while (lst)
    {
        size++;
        lst = lst->next;
    }
    return (size);
}