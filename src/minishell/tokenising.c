#include "minishell.h"


void	tokenise(t_data *data, char *str)
{
	printf("tokenising\n");//Debug
	int	i;
	t_token **head;

	i = 0;
	head = &data->token_list;
	while (str[i])
	{
		if (find_tokens(data, str, &i, head) == 0)
		{
			printf("I entered here first\n");
			continue ;
		}
		if (is_split_char(i, str, "|", 2) || is_split_char(i, str, ">", 1)
			|| is_split_char(i, str, "<", 1))
		{
			add_token(head, create_token(data, i + 1));
		}
		else if (is_split_char(i, str, ">", 0) || is_split_char(i, str, "<", 0))
		{
			add_token(head, create_token(data, i + 1));
			i++;
		}
		data->count++;
		i++;
	}
	if (i > 0)
	{
		printf("I am the first creation\n");
		add_token(head, create_token(data, i));
		add_token(head, create_arg_token(data, "newline", T_NEWLINE));
	}
	printf("WORD ADDRESS= %s\n", data->token_list->word);
}

int	find_tokens(t_data *data, char *str, int *i, t_token **head)
{
	printf("find_tokens\n");//Debug
	t_token *tmp;

	if (ft_strchr(" \t", str[*i]))
	{
		printf("I am the second creation\n");
		tmp = create_token(data, *i);
		add_token(head, tmp);
		(*i)++;
		return (0);
	}
	if (ft_strchr("|;<>", str[*i]) && *i > 0 && !ft_strchr("<>", str[*i - 1]))
	{
		printf("I AM STUPID\n");
		tmp = create_token(data, *i);
		add_token(head, tmp);
		(*i)++;
		return (0);
	}
	return (1);
}

int is_split_char(int i, char *str, char *splt, int sign)
{
	// printf("is_split_char\n");//Debug
	if (sign == 1 && ft_strchr(splt, str[i]) && !ft_strchr(splt, str[i + 1]))
		{
			printf("> or <\n");
			return (1);
		}
	else if (sign == 0 && ft_strchr(splt, str[i] && ft_strchr(splt, str[i + 1]))
		&& ft_strchr(splt, str[i + 1]))
		{
			printf(">> or <<\n");
			return (1);
		}
	else if (sign == 2 && ft_strchr(splt, str[i]) && i > 0 && ft_strchr(splt, str[i - 1]))
		{
			return (1);
		}
	else if (sign == 3 && ft_strchr(splt, str[i]))
		{
			return (1);
		}
	return (0);
}




t_token	*split_tokens_to_list(char **split, t_data *data)
{
	printf("split_tokens_to_list\n");
	t_token		*new;
	t_token		*tmp;
	int			i;
	int			count;
	
	i = 0;
	count = len_2darray(split);
	new = NULL;
	while (i < count)
	{
		tmp = create_arg_token(data, split[i], T_WORD);
		add_token(&new, tmp);
		i++;
	}
	return (new);
}

void	token_to_cmd(t_data *data, t_token **tmp)
{
	printf("token_to_cmd\n");
	t_cmdexe *cmd;
	t_token *head;
	
	if ((*tmp)->type == T_NEWLINE)
	{
		*tmp = (*tmp)->next;
		return ;
	}
	if (!(cmd = ft_calloc(1, sizeof(t_cmdexe))))
		return ;
	while (*tmp)
	{
		if (!evaluate_tokens(data, tmp, cmd))
			break ;
		if ((*tmp)->type == T_ENV && cmd->cmd)
		{
			head = create_arg_token(data, (*tmp)->word, (*tmp)->type);
			add_token(&cmd->args, head);
		}
		*tmp = (*tmp)->next;
	}
	add_cmd(&data->cmd_list, cmd);
}

int	evaluate_tokens(t_data *data, t_token **tmp, t_cmdexe *cmd)
{
	printf("evaluete tokens\n");//Debug
	if ((*tmp)->type == T_WORD && (cmd->cmd || ((*tmp)->prev && (*tmp)->prev->type == T_REDIRECT)))
		add_token(&cmd->args, create_arg_token(data, (*tmp)->word, (*tmp)->type));
	if ((*tmp)->type == T_WORD && !cmd->cmd && (((*tmp)->prev && (*tmp)->prev->type != T_REDIRECT) || !(*tmp)->prev))
		cmd->cmd = ft_strdup((*tmp)->word);
	if ((*tmp)->type == T_REDIRECT)
		add_token(&cmd->args, create_arg_token(data, (*tmp)->word, (*tmp)->type));
	if ((*tmp)->type == T_ENV && !cmd->cmd)
		ft_lstadd_back(&cmd->env_list, ft_lstnew(ft_strdup((*tmp)->word)));
	if ((*tmp)->type == T_PIPE)
	{
		cmd->cmd_type = T_PIPE;
		*tmp = (*tmp)->next;
		return (0);
	}
	if ((*tmp)->type == T_SEP)
	{
		cmd->cmd_type = T_SEP;
		*tmp = (*tmp)->next;
		return (0);
	}
	return (1);
}