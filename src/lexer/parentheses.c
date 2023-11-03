#include "minishell.h"

int	lexic_with_parenth(t_data *data)
{
	int flag;

	flag = find_parenthesis(data->input_line);
	if (flag)
	{
		if (flag == 2)
			return (1);
		free_tokens(&data->token_list, free);
		data->count = 0;
		tokenise_parenth(data, data->input_line);
		set_token_parenth(data);
		// if (check_parenth(&data->token_list))
		// 	return (1);
	}
	return (0);
}

int find_parenthesis(char *str)
{
	int parenCount;
	int i;
	i = 0;
	int parenth_total;

	parenth_total = 0;
	parenCount = 0;
	while (str[i])
	{
		if (str[i] == '(' && !in_quotes(str, i))
		{
			parenth_total++;
			parenCount++;
		}
		else if (str[i] == ')' && !in_quotes(str, i))
		{
			parenCount--;
			parenth_total++;
		}
		i++;
	}
	if (parenth_total > 0)
	{
		if (parenCount == 0)
			return (1);
		else
			return (printf("minishell: we don't have to handle unclose parenthesis\n"), 2);
	}
	return (0);
}


void	tokenise_parenth(t_data *data, char *str)
{
	int	i;
	t_token **head;

	i = 0;
	head = &data->token_list;
	while (str[i])
	{
		if (str[i] == '(' && !in_quotes(str, i))
		{
			if (!find_parenth_token(data, str, &i, head))
			{
				i++;
				continue ;
			}
		}
		else if (!find_token(data, str, &i, head))
			continue ;
		data->count++;
		if (find_token2(i, str, "|") || find_token2(i, str, ">")
			|| find_token2(i, str, "<") || find_token2(i, str, "&")
			|| find_token2(i, str, "$"))
			add_token(head, create_token(data, i + 1));
		i++;
	}
	// printf("STRING2 = %s\n", str);
	if (i > 0)
	{
		add_token(head, create_token(data, i));
		add_token(head, create_arg_token(data, "newline", T_NEWLINE));
	}
}

int find_parenth_token(t_data *data, char *str, int *i, t_token **head)
{
    int parenCount;
    int start;

    parenCount = 1;
    start = *i;
    (*i)++;
    while (str[*i] && parenCount > 0)
    {
        if (str[*i] == '(' && !in_quotes(str, *i))
            parenCount++;
        else if (str[*i] == ')' && !in_quotes(str, *i))
            parenCount--;
		if (parenCount == 0)
        {
            data->count = *i - start - 1;
            add_token(head, create_parenth_token(data, start, str));
        }
        if (parenCount > 0)
            (*i)++;
    }
    return (parenCount);
}

t_token	*create_parenth_token(t_data *data, int i, char *input)
{
    t_token	*new;

    new = malloc(sizeof(t_token));
    if (!new)
        exit_shell("Error: malloc failed\n", 1, data);
    new->word = ft_substr(input, i + 1, data->count);
    new->type = T_PARENTHESES;
    data->count = 0;
    return (new);
}

int check_parenth(t_token **token)
{
	t_token *head;

	head = *token;
	while (*token)
	{
		if ((*token)->type == T_PARENTHESES)
		{
			if ((*token)->next->type != T_PIPE && (*token)->next->type != T_RED_INP && (*token)->next->type != T_RED_OUT
				&& (*token)->next->type != T_APPEND && (*token)->next->type != T_OR && (*token)->next->type != T_AND && (*token)->next->type != T_DELIM && (*token)->next->type != T_NEWLINE)
				return (printf("minishell: syntax error near unexpected token `%s'\n", (*token)->next->word), 1);
			if ((*token)->prev->type == T_SPACE)
					return (printf("minishell: syntax error near unexpected token `%s'\n", (*token)->word), 1);
		}
		*token = (*token)->next;
	}
	*token = head;
	return (0);
}

int	set_token_parenth(t_data *data)
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
			set_token_parenth2(data->token_list);
		data->token_list = data->token_list->next;
	}
	data->token_list = head;
	clean_null_tokens(&data->token_list);
	fix_tokens(&data->token_list);
	clean_space_tokens(&data->token_list);
	return (0);
}

void	set_token_parenth2(t_token *token)
{
	t_token	*head;

	head = token;
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
	else if (token->type !=  T_NEWLINE && token->type != T_PARENTHESES)
		token->type = T_WORD;
	token = head;
}