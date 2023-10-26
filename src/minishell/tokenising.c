#include "minishell.h"

void	tokenise(t_data *data, char *str)
{
	printf("tokenise\n");//Debug
	int	i;
	t_token **head;

	i = 0;
	head = &data->token_list;
	data->count = 0;
	while (str[i])
	{
		if (!find_token(data, str, &i, head))
			continue ;
		data->count++;
		if (find_token2(i, str, "|", 3) || 
			find_token2(i, str, ">", 1) ||
			find_token2(i, str, ">", 0) ||
			find_token2(i, str, "<", 1) ||
			find_token2(i, str, "<", 0))
			add_token(head, create_token(data, i + 1));
		i++;
	}
	if (i > 0)
	{
		add_token(head, create_token(data, i));
		add_token(head, create_arg_token(data, "newline", T_NEWLINE));
	}
	// printf("WORD ADDRESS= %s\n", data->token_list->word);
}

int	find_token(t_data *data, char *str, int *i, t_token **head)
{
	if (is_chr_str(str[*i], " \t") && !in_bracket(str, *i)
		&& !is_escaped(str, *i - 1))
	{
		add_token(head, create_token(data, *i));
		(*i)++;
		return (0);
	}
	if (is_chr_str(str[*i], "|<>") && !in_bracket(str, *i)
		&& !is_escaped(str, *i - 1) && *i > 0
		&& !is_chr_str(str[*i - 1], "<>"))
		add_token(head, create_token(data, *i));
	return (1);
}

int		find_token2(int i, char *str, char *splt, int sign)
{
	if (sign == 1 && is_chr_str(str[i], splt) && !is_chr_str(str[i + 1], splt)
		&& !in_bracket(str, i) && !is_escaped(str, i - 1))
		return (1);
	else if (!sign && is_chr_str(str[i], splt) && i > 0
		&& is_chr_str(str[i - 1], splt) && !in_bracket(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	else if (sign == 2 && is_chr_str(str[i], splt)
		&& i > 0 && is_chr_str(str[i - 1], splt) && !in_bracket(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	else if (sign == 3 && is_chr_str(str[i], splt) && !in_bracket(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	return (0);
}

int	ft_is_in_stri(char c, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		is_chr_str(char c, char *str)
{
	if (ft_is_in_stri(c, str) >= 0)
		return (1);
	return (0);
}





int		is_escaped(char *s, int pos)
{
	int n;

	n = 0;
	while (pos >= 0 && s[pos] == '\\')
	{
		n++;
		pos--;
	}
	return (n % 2);
}

int		in_bracket(char *s, int pos)
{
	int	bracket1;
	int	bracket2;
	int	i;

	bracket1 = 0;
	bracket2 = 0;
	i = 0;
	while (i <= pos)
	{
		if (s[i] == 34 && (i == 0 || !is_escaped(s, i - 1))
			&& bracket2 % 2 == 0)
			bracket1++;
		if (s[i] == 39 && (i == 0 || bracket2 % 2 != 0 || !is_escaped(s, i - 1))
			&& bracket1 % 2 == 0)
			bracket2++;
		i++;
	}
	if (bracket1 % 2 != 0 || bracket2 % 2 != 0)
		return (1);
	return (0);
}


// t_token	*split_tokens_to_list(char **split, t_data *data)
// {
// 	printf("split_tokens_to_list\n");
// 	t_token		*new;
// 	t_token		*tmp;
// 	int			i;
// 	int			count;
	
// 	i = 0;
// 	count = len_2darray(split);
// 	new = NULL;
// 	while (i < count)
// 	{
// 		tmp = create_arg_token(data, split[i], T_WORD);
// 		add_token(&new, tmp);
// 		i++;
// 	}
// 	return (new);
// }

// void	token_to_cmd(t_data *data, t_token **tmp)
// {
// 	printf("token_to_cmd\n");
// 	t_cmdexe *cmd;
// 	t_token *head;
	
// 	if ((*tmp)->type == T_NEWLINE)
// 	{
// 		*tmp = (*tmp)->next;
// 		return ;
// 	}
// 	if (!(cmd = ft_calloc(1, sizeof(t_cmdexe))))
// 		return ;
// 	while (*tmp)
// 	{
// 		if (!evaluate_tokens(data, tmp, cmd))
// 			break ;
// 		if ((*tmp)->type == T_ENV && cmd->cmd)
// 		{
// 			head = create_arg_token(data, (*tmp)->word, (*tmp)->type);
// 			add_token(&cmd->args, head);
// 		}
// 		*tmp = (*tmp)->next;
// 	}
// 	add_cmd(&data->cmd_list, cmd);
// }

// int	evaluate_tokens(t_data *data, t_token **tmp, t_cmdexe *cmd)
// {
// 	printf("evaluete tokens\n");//Debug
// 	if ((*tmp)->type == T_WORD && (cmd->cmd || ((*tmp)->prev && (*tmp)->prev->type == T_REDIRECT)))
// 		add_token(&cmd->args, create_arg_token(data, (*tmp)->word, (*tmp)->type));
// 	if ((*tmp)->type == T_WORD && !cmd->cmd && (((*tmp)->prev && (*tmp)->prev->type != T_REDIRECT) || !(*tmp)->prev))
// 		cmd->cmd = ft_strdup((*tmp)->word);
// 	if ((*tmp)->type == T_REDIRECT)
// 		add_token(&cmd->args, create_arg_token(data, (*tmp)->word, (*tmp)->type));
// 	if ((*tmp)->type == T_ENV && !cmd->cmd)
// 		ft_lstadd_back(&cmd->env_list, ft_lstnew(ft_strdup((*tmp)->word)));
// 	if ((*tmp)->type == T_PIPE)
// 	{
// 		cmd->cmd_type = T_PIPE;
// 		*tmp = (*tmp)->next;
// 		return (0);
// 	}
// 	if ((*tmp)->type == T_SEP)
// 	{
// 		cmd->cmd_type = T_SEP;
// 		*tmp = (*tmp)->next;
// 		return (0);
// 	}
// 	return (1);
// }