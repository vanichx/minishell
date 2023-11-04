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
		if (set_token_parenth(data))
			return (1);
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
		if (!find_token3(data, str, &i, head))
			if (str[i] != '(')
				continue ;
		if (str[i] == '(' && !in_quotes(str, i))
		{
			if (!find_parenth_token(data, str, &i, head))
			{
				i++;
				continue ;
			}
		}
		data->count++;
		if (find_token2(i, str, "|") || find_token2(i, str, ">")
			|| find_token2(i, str, "<") || find_token2(i, str, "&")
			|| find_token2(i, str, "$"))
			add_token(head, create_token(data, i + 1));
		i++;
	}
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
	if (!new->word)
		new->word = ft_strdup("");
    new->type = T_PARENTHESES;
    data->count = 0;
    return (new);
}

int syntax_error_parenth(t_token **token)
{
    t_token *head;

    head = *token;
    while (*token)
    {
        if ((*token)->type == T_PARENTHESES)
        {
			if (only_parenth((*token)->word))
				return (operand_error_parenth(only_parenth((*token)->word)));
			if ((!ft_strcmp((*token)->word, "") && (!(*token)->prev || (*token)->prev->type != T_DOLLAR))
				|| ((*token)->prev && (*token)->prev->type == T_SPACE && (*token)->prev->prev->type != T_OR
				&& (*token)->prev->prev->type != T_AND && (*token)->prev->prev->type != T_PIPE && (*token)->prev->prev->type != T_WORD))
				return (printf("minishell: syntax error near unexpected token `)'\n"), 1);
			if ((*token)->next->type == T_PARENTHESES || ((*token)->next->type == T_SPACE && (*token)->next->next->type == T_PARENTHESES))
				return (printf("minishell: syntax error near unexpected token `)'\n"), 1);
            if (((*token)->prev->type == T_SPACE && (*token)->prev->prev->type == T_WORD)
				|| ((*token)->prev->type == T_WORD))
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
		set_token_parenth2(data->token_list);
		data->token_list = data->token_list->next;
	}
	data->token_list = head;
	clean_null_tokens(&data->token_list);
	fix_tokens(&data->token_list);
	if (syntax_error_parenth(&data->token_list))
		return (1);
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

int	only_parenth(char *str)
{
	int count;
	int flag;

	count = 0;
	flag = 0;
	if (only_spaces_parenth(str))
		flag = 1;
	while (*str)
	{
		if (*str == '(')
			count++;
		str++;
	}
	if (count == 1)
		return (0);
	else if (flag == 1 )
		return (count);
	else
		return (0);
}

int	operand_error_parenth(int i)
{
	int j;
	int z;

	i -= 2;
	j = i;
	z = i;
	printf("minishell: ((: ");
	while (i-- >= 0)
		printf("%c", '(');
	while (z-- >= 0)
		printf("%c", ')');
	printf(": syntax error: operand expected (error token is \"");
	while (j-- >= 0)
		printf("%c", ')');
	printf("\")\n");
	return (1);
}

int	find_token3(t_data *data, char *str, int *i, t_token **head)
{
    if (is_chr_str(str[*i], " \t*(") && !in_quotes(str, *i)
        && !is_escaped(str, *i - 1))
    {
        add_token(head, create_token(data, *i));
        if (str[*i] == '*')
            add_token(head, create_arg_token(data, "*", T_STAR));
        else if (str[*i] == ' ' || str[*i] == '\t')
            add_token(head, create_arg_token(data, " ", T_SPACE));
		else if (str[*i] == '(')
			(*i)--;
        (*i)++;
        data->count = 0;
        return (0);
    }
    else if (is_chr_str(str[*i], "|<>&$") && !in_quotes(str, *i)
        && !is_escaped(str, *i - 1) && *i > 0
        && !is_chr_str(str[*i - 1], "|<>&$"))
        add_token(head, create_token(data, *i));
    return (1);
}