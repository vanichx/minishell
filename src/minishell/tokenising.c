#include "minishell.h"

void	tokenise(t_data *data, char *str)
{
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
		if (find_token2(i, str, "|", 1) || find_token2(i, str, "|", 0)
			|| find_token2(i, str, ">", 1) || find_token2(i, str, ">", 0) 
			|| find_token2(i, str, "<", 1) || find_token2(i, str, "<", 0)
			|| find_token2(i, str, "&", 1) || find_token2(i, str, "&", 0))
			add_token(head, create_token(data, i + 1));
		i++;
	}
	if (i > 0)
	{
		add_token(head, create_token(data, i));
		add_token(head, create_arg_token(data, "newline", T_NEWLINE));
	}
}

int	find_token(t_data *data, char *str, int *i, t_token **head)
{
	if (is_chr_str(str[*i], " \t") && !in_quotes(str, *i)
		&& !is_escaped(str, *i - 1))
	{
		add_token(head, create_token(data, *i));
		(*i)++;
		return (0);
	}
	if (is_chr_str(str[*i], "|<>") && !in_quotes(str, *i)
		&& !is_escaped(str, *i - 1) && *i > 0
		&& !is_chr_str(str[*i - 1], "|<>"))
		add_token(head, create_token(data, *i));
	return (1);
}

int		find_token2(int i, char *str, char *splt, int sign)
{
	if (sign == 1 && is_chr_str(str[i], splt) && !is_chr_str(str[i + 1], splt)
		&& !in_quotes(str, i) && !is_escaped(str, i - 1))
		return (1);
	else if (!sign && is_chr_str(str[i], splt) && i > 0
		&& is_chr_str(str[i - 1], splt) && !in_quotes(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	else if (sign == 2 && is_chr_str(str[i], splt)
		&& i > 0 && is_chr_str(str[i - 1], splt) && !in_quotes(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	else if (sign == 3 && is_chr_str(str[i], splt) && !in_quotes(str, i)
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

int		in_quotes(char *s, int pos)
{
	int	quotes1;
	int	quotes2;
	int	i;

	quotes1 = 0;
	quotes2 = 0;
	i = 0;
	while (i <= pos)
	{
		if (s[i] == 34 && (i == 0 || !is_escaped(s, i - 1))
			&& quotes2 % 2 == 0)
			quotes1++;
		if (s[i] == 39 && (i == 0 || quotes2 % 2 != 0 || !is_escaped(s, i - 1))
			&& quotes1 % 2 == 0)
			quotes2++;
		i++;
	}
	if (quotes1 % 2 != 0 || quotes2 % 2 != 0)
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

int print_error(t_token *token)
{
	if (token->type)
		printf("minishell: syntax error near unexpected token %s\n", token->type);
	return (0);
}

int	evaluate_tokens(t_data *data)
{
	while (data->token_list->next)
	{
		if (data->token_list->type >= 9 && data->token_list->next->type != T_WORD)
			return (print_error(data->token_list->type));
		

	}
	return (1);
}

void clean_token_spaces(t_data *data) 
{
    t_token *tmp;
    t_token *current = data->token_list;

    if (data == NULL || data->token_list == NULL)
        return;
    while (current)
    {
        if (current->type == T_SPACE)
        {
            tmp = current;
            if (tmp->prev)
                tmp->prev->next = tmp->next;
            if (tmp->next)
                tmp->next->prev = tmp->prev;
			else
				tmp->next->prev = NULL;
			if (tmp)
            	free(tmp);
        }
        current = current->next;
    }
}