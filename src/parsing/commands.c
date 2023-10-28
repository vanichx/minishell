#include "minishell.h"

void	print_cmdexe(void *cmdexe_node)
{
    t_cmdexe	*cmdexe = (t_cmdexe *)cmdexe_node;

    printf("path: %s\n cmd: %s\n", cmdexe->path, cmdexe->cmd);
}

void   add_cmd(t_cmdexe **head, t_cmdexe *new)
{
	printf("add_cmd\n");//Debug
	t_cmdexe *tmp;

	if (!new || !head)
		return ;
	new->cmd = trim_newlines(new->cmd);
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
		*head = new;
}

void	clear_cmd_list(t_cmdexe **cmd, void (*del)(void*))
{
	t_cmdexe	*tmp;
	t_cmdexe	*tmp2;
	t_token		*args;
	t_token		*args2;

	if (!cmd || !del)
		return ;
	tmp = *cmd;
	while (tmp)
	{
		clear_cmd(tmp);
		args = tmp->args;
		while (args)
		{
			ft_strdel(&args->word);
			args2 = args->next;
			del(args);
			args = args2;
		}
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*cmd = NULL;
}

void	clear_cmd(t_cmdexe *cmd)
{
	ft_strdel(&cmd->cmd);
	ft_strdel(&cmd->path);
	free_2darray(cmd->args_array);
	ft_lstclear(&cmd->env_list, free);
}