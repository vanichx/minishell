#include "minishell.h"

void	ft_cmdadd_back(t_cmdexe **lst, t_cmdexe *new)
{
	t_cmdexe *head;

	head = (*lst);
	if (!lst)
		return ;
	if (lst)
	{
		if (*lst)
		{
			ft_cmdlast(*lst)->next = new;
			return ;
		}
	}
	*lst = new;
}

t_cmdexe	*ft_cmdlast(t_cmdexe *lst)
{
	t_cmdexe	*node;
	
	node = lst;
	if (node != NULL)
	{
		while (node->next != NULL)
			node = node->next;
	}
	return (node);
}

void	ft_cmdadd_front(t_cmdexe **lst, t_cmdexe *new)
{
	new->next = *lst;
	if (*lst != NULL)
		(*lst)->prev = new;
	*lst = new;
}

// void	ft_cmddelone(t_cmdexe *lst, void (*del)(void *))
// {
// 	if (!lst || !del)
// 		return ;
// 	if (lst->path)
// 		free(lst->path);
// 	if (lst->cmd)
// 		free(lst->cmd);
// 	free(lst);
// }

void  ft_cmdclear(t_cmdexe **cmd_list)

{
  t_cmdexe  *head;

  while (*cmd_list)
  {
    head = (*cmd_list)->next;
	free((*cmd_list)->cmd);
	(*cmd_list)->cmd = NULL;
	free((*cmd_list)->path);
	(*cmd_list)->path = NULL;
    free(*cmd_list);
    (*cmd_list) = head;
  }
}

t_cmdexe	*ft_cmdnew(char *cmd)
{
	t_cmdexe	*head;

	head = (t_cmdexe *)malloc(sizeof(t_cmdexe));
	if (!head)
		return (NULL);
	head->cmd = ft_strdup(cmd);
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