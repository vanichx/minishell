#include "minishell.h"

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!new || !head)
		return ;
	if (*head)
	{
		tmp = *head;
		while (tmp->next)
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
	{
		*head = new;
		new->prev = NULL;
		new->next = NULL;
	}
}

// for what we need also this ?
t_token  *last_token(t_token *lst)

{
  t_token  *node;

  node = lst;
  if (node != NULL)
  {
    while (node->next != NULL)
      node = node->next;
  }
  return (node);
}

// adds a token in the front of the list
void	add_token_front(t_token **head, t_token *new)
{
	printf("add_token_front\n");
	if (*head)
	{
		new->next = *head;
		(*head)->prev = new;
		*head = new;
	}
	else
		*head = new;
}

// caunts the len of the tokens list
int	tokens_len(t_token **head)
{
	printf("tokens_len\n");
	t_token *tmp;
	int		i;

	i = 0;
	tmp = *head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

// for what we need this when we hav ft_lstadd_back
void  ft_listadd_back(t_token **lst, t_token *next)
{
  if (!lst)
    return ;
  if (lst)
  {
    if (*lst)
    {
    	last_token(*lst)->next = next;
    	return ;
    }
  }
  *lst = next;
}
