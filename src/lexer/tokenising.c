#include "minishell.h"

void	tokenise(t_data *data, char *str)
{
	int	i;
	t_token **head;

	i = 0;
	head = &data->token_list;
	data->count = 0;//Need to init this value during the initialization of the data structure
	while (str[i])
	{
		if (str[i] == '(')
		{
			if (!find_parenthesis_token(data, str, &i, head))
				continue ;
		}
		else if (!find_token(data, str, &i, head))
			continue ;
		data->count++;
		if (find_token2(i, str, "|") || find_token2(i, str, ">")
			|| find_token2(i, str, "<") || find_token2(i, str, "&"))
			add_token(head, create_token(data, i + 1, str));
		i++;
	}
	
	printf("STRING2 = %s\n", str);
	if (i > 0)
	{
		add_token(head, create_token(data, i, str));
		add_token(head, create_arg_token(data, "newline", T_NEWLINE));
	}
}

int find_parenthesis_token(t_data *data, char *str, int *i, t_token **head)
{
	int parenCount;

	parenCount = 1;
	while (str[*i] && parenCount > 0)
	{
		data->count++;
		(*i)++;
		if (str[*i] == '(')
			parenCount++;
		else if (str[*i] == ')')
			parenCount--;
	}
		
	if (parenCount == 0)
	{
		data->count--;
		add_token(head, create_parenth_token(data,  *i, str));
		(*i)++;
	}
	else
	{
		printf("pls close fucking parenthesis, don't broke our program\n");
		return (1);
	}
	return (parenCount);
}

int	find_token(t_data *data, char *str, int *i, t_token **head)
{
	if (is_chr_str(str[*i], " \t*") && !in_quotes(str, *i)
		&& !is_escaped(str, *i - 1))
	{
		add_token(head, create_token(data, *i, str));
		if (str[*i] == '*')
			add_token(head, create_arg_token(data, "*", T_STAR));
		else
			add_token(head, create_arg_token(data, " ", T_SPACE));
		(*i)++;
		data->count = 0;
		return (0);
	}
	else if (is_chr_str(str[*i], "|<>&") && !in_quotes(str, *i)
		&& !is_escaped(str, *i - 1) && *i > 0
		&& !is_chr_str(str[*i - 1], "|<>&"))
		add_token(head, create_token(data, *i, str));
	return (1);
}

int		find_token2(int i, char *str, char *splt)
{
	if (is_chr_str(str[i], splt) && !in_quotes(str, i) 
		&& !is_escaped(str, i - 1))
		return (1);
	return (0);
}

void	set_token_type2(t_token *token)
{
	if (!ft_strcmp(token->word, "<"))
		token->type = T_RED_INP;
	else if (!ft_strcmp(token->word, ">"))
		token->type = T_RED_OUT;
	else if (!ft_strcmp(token->word, "|"))
		token->type = T_PIPE;
	else if (!ft_strcmp(token->word, "$"))
		token->type = T_DOLLAR;
	else if (!ft_strcmp(token->word, " "))
		token->type = T_SPACE;
	else if (!ft_strcmp(token->word, "*"))
		token->type = T_STAR;
	else if (!ft_strcmp(token->word, "&"))
		token->type = T_AMPER;
	else if (token->type == T_PARENTHESES)
		return ;
	else if (token->type !=  T_NEWLINE)
		token->type = T_WORD;
}




int	set_token_type(t_data *data)
{
	t_token	*head;

	head = data->token_list;
	while (data->token_list)
	{
		if (!ft_strcmp(data->token_list->word, ">>"))
			data->token_list->type = T_APPEND;
		else if (!ft_strcmp(data->token_list->word, "<<"))
			data->token_list->type = T_DELIM;
		else if (!ft_strcmp(data->token_list->word, "&&"))
			data->token_list->type = T_AND;
		else if (!ft_strcmp(data->token_list->word, "||"))
			data->token_list->type = T_OR;
		else
			set_token_type2(data->token_list);
		data->token_list = data->token_list->next;
	}
	data->token_list = head;
	clean_null_tokens(&data->token_list);
	fix_tokens(&data->token_list);
	if (check_token_error1(data->token_list, data))
		return (1);
	clean_space_tokens(&data->token_list);
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

// int print_error(char *str)
// {
// 	if (str)
// 		printf("minishell: syntax error near unexpected token %s\n", str);
// 	return (0);
// }

// int	evaluate_tokens(t_data *data)
// {
// 	while (data->token_list)
// 	{
// 		if (data->token_list->type >= 8 && data->token_list->next->type == T_NEWLINE && data->token_list->prev == NULL)
// 			return (print_error(data->token_list->word));

// 	}
// 	return (1);
// }

// void	check_pipe_tokens(t_token *lst)
// {
// 	if (lst->type == T_OR && lst->next->type == T_PIPE && lst->next->next->type == T_PIPE)
// 		return (print_error("||"));
// 	else if (lst->type == T_OR && lst->next->type == T_PIPE && lst->next->next-type != T_PIPE)
// 	{
// 		if (!lst->prev)
// 			return (print_error("||"));
// 		else
// 			return (print_error("|"));
// 	}
// 	else if (lst->type == T_PIPE && lst->next->type == T_AND)
// 		return (print_error("&&"));
// 	else if (lst->type == T_PIPE && lst->next->type == T_AMPERSAND)
// 		return (print_error("&"));
// 	else if (lst->type == T_PIPE && lst->next->type != T_WORD && lst->prev->type != T_WORD)
// 		return (print_error("|"));
	
// }

// void	check_redir_tokens(t_token *lst)
// {

// }

// void	check_delim_tokens(t_token *lst)
// {

// }

// void	check_and_tokens(t_token *lst)
// {

// }



