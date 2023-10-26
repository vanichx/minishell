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

t_token	*create_token(t_data *data, int i)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit_shell("Error: malloc failed\n", 1, data);
	new->word = ft_substr(data->input_line, i - data->count, data->count);
	data->count = 0;
	return (new);
}

t_token	*create_arg_token(t_data *data, char *word, enum e_token_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		exit_shell("Error: malloc failed\n", 1, data);
	new->word = ft_strdup(word);
	new->type = type;
	return (new);
}

void	set_token_types(t_data *data)
{
	t_token	*head;

	head = data->token_list;
	while (data->token_list)
	{
		set_token_type(data->token_list);
		data->token_list = data->token_list->next;
	}
	data->token_list = head;
}

void	set_token_type(t_token *token)
{
	if (!ft_strcmp(token->word, "<"))
		token->type = T_RED_INP;
	else if (!ft_strcmp(token->word, ">"))
		token->type = T_RED_OUT;
	else if (!ft_strcmp(token->word, ">>"))
		token->type = T_APPEND;
	else if (!ft_strcmp(token->word, "<<"))
		token->type = T_DELIM;
	else if (!ft_strcmp(token->word, "&&"))
		token->type = T_AND;
	else if (!ft_strcmp(token->word, "||"))
		token->type = T_OR;
	else if (!ft_strcmp(token->word, "|"))
		token->type = T_PIPE;
	else if (!ft_strcmp(token->word, "$"))
		token->type = T_DOLLAR;
	else if ((token->type == T_NEWLINE
			|| !ft_strcmp(token->word, "\n")) && !token->next)
		token->type = T_NEWLINE;
	else if (is_valid_env(token->word))
		token->type = T_ENV;
	else if (!ft_strcmp(token->word, "\0"))
		token->type = T_SPACE;
	else
		token->type = T_WORD;
}
