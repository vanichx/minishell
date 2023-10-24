#include "minishell.h"


void	split_tokens(t_data *data, char *str)
{
	int	i;
	t_token *head;

	i = 0;
	head = data->token_list;
	while (str[i])
	{
		if (!parse_tokens(data, str, &i, &head))
			continue ;
		data->count++;
		printf("count: %d\n", data->count);//Debug
		if (is_split_char(i, str, "|;", 2) || is_split_char(i, str, ">", 1)
			|| is_split_char(i, str, "<", 1))
			{
			printf("The problem is here\n");
			add_token(&head, create_token(data, i + 1));
			}
		else if (is_split_char(i, str, ">", 0) || is_split_char(i, str, "<", 0))
		{
			add_token(&head, create_token(data, i + 1));
			i++;
		}
		i++;
	}
	if (i > 0)
	{
		add_token(&data->token_list, create_token(data, i));
		add_token(&data->token_list, create_arg_token(data, "newline", T_NEWLINE));
	}
}
int is_split_char(int i, char *str, char *splt, int sign)
{
    if (sign == 1 && ft_strchr(splt, str[i]) && !ft_strchr(splt, str[i + 1])
        && !inside_paired_quotes(str, i) && !closed_quote(str, i - 1))
		{
		printf("Sign = 1\n");
		printf("> or <\n");
        return (1);
		}
    else if (sign == 0 && ft_strchr(splt, str[i])
        && ft_strchr(splt, str[i + 1]) && !inside_paired_quotes(str, i)
        && !closed_quote(str, i - 1))
		{
		printf("Sign = 0\n");
		printf(">> or <<\n");
        return (1);
		}
    else if (sign == 2 && ft_strchr(splt, str[i]) && i > 0 && ft_strchr(splt, str[i - 1]) 
		&& !inside_paired_quotes(str, i) && !closed_quote(str, i - 1))
		{
		printf("Sign = 2\n");
        return (1);
		}
    else if (sign == 3 && ft_strchr(splt, str[i]) && !inside_paired_quotes(str, i)
        && !closed_quote(str, i - 1))
		{
		printf("Sign = 3\n");
        return (1);
		}
    return (0);
}

int	parse_tokens(t_data *data, char *str, int *i, t_token **head)
{
	if (ft_strchr(" \t", str[*i]) && !inside_paired_quotes(str, *i)
		&& !closed_quote(str, *i - 1))
	{
		add_token(head, create_token(data, *i));
		(*i)++;
		return (0);
	}
	if (ft_strchr("|;<>", str[*i]) && !inside_paired_quotes(str, *i)
		&& !closed_quote(str, *i - 1) && *i > 0 && !ft_strchr("<>", str[*i - 1]))
		add_token(head, create_token(data, *i));
	return (1);
}



t_token	*split_tokens_to_list(char **split, t_data *data)
{
	t_token		*new;
	int			i;
	int			count;
	
	i = 0;
	count = len_2darray(split);
	new = NULL;
	while (i < count)
	{
		add_token(&new, create_arg_token(data, split[i], T_WORD));
		printf("split[%d]: %s\n", i, split[i]);//Debug
		i++;
	}
	return (new);
}

void	token_to_cmd(t_data *data, t_token **tmp)
{
	t_cmdexe *cmd;
	
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
			add_token(&cmd->args, create_arg_token(data, (*tmp)->word, (*tmp)->type));
		*tmp = (*tmp)->next;
	}
	add_cmd(&data->cmd_list, cmd);
}

int	evaluate_tokens(t_data *data, t_token **tmp, t_cmdexe *cmd)
{
	printf("IM IN EVAL TOKEN!!!\n");//Debug
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