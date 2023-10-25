#include "minishell.h"

void add_token(t_token **token, t_token *new)
{
    printf("add_token\n"); // Debug
    if (!new || !token || !*token)
	{
        return;
    }

    t_token *tmp = *token;
    while (tmp->next)
	{
        tmp->next->prev = tmp;
        tmp = tmp->next;
    }

    tmp->next = new;
    new->prev = tmp;
    new->next = NULL;
    printf("CREATED INNER NODE = %s\n", new->word);
}

void	add_token_front(t_token **head, t_token *new)
{
	printf("add_token_front\n");//Debug
	if (*head)
	{
		new->next = *head;
		(*head)->prev = new;
		*head = new;
	}
	else
		*head = new;
}

t_token	*create_token(t_data *data, int i)
{
	printf("create_token\n");//Debug
	t_token *new;

	if (!(new = malloc(sizeof(t_token))))
		exit_shell("Error: malloc failed\n", 1, data);
	new->word = ft_substr(data->input_line, i - data->count, data->count);

	printf("%s\t, %d\t, %d\n", new->word, i - data->count, data->count);
	data->count = 0;
	return (new);
}

t_token	*create_arg_token(t_data *data, char *word, enum e_token_type type)
{
	printf("create_arg_token\n");//Debug
	t_token *new;

	// new = NULL;
	// data->token_list = new;
	if (!(new = ft_calloc(1, sizeof(t_token))))
		exit_shell("Error: malloc failed\n", 1, data);
	new->word = ft_strdup(word);
	printf("Value of new->word = %s\n", new->word);
	new->type = type;
	return (new);
}

char	*set_token_types(t_data *data)
{
	t_token *head;

	head = data->token_list;
	printf("set_token_types\n");

	while (data->token_list)
	{
		if (ft_strchr(data->token_list->word, '>') || ft_strchr(data->token_list->word, '<'))
			data->token_list->type = T_REDIRECT;
		else if (!ft_strcmp(data->token_list->word, ">>"))
			data->token_list->type = T_APPEND;
		else if (!ft_strcmp(data->token_list->word, "<<"))
			data->token_list->type = T_DELIM;
		else if (!ft_strcmp(data->token_list->word, "&&"))
			data->token_list->type = T_AND;
		else if (!ft_strcmp(data->token_list->word, "||"))
			data->token_list->type = T_OR;
		else if (ft_strchr(data->token_list->word, '|'))
			data->token_list->type = T_PIPE;
		else if (ft_strchr(data->token_list->word, ';'))
			data->token_list->type = T_SEP;
		else if (!ft_strchr(data->token_list->word, '\n') && !data->token_list->next)
			data->token_list->type = T_NEWLINE;
		else if (is_valid_env(data->token_list->word))
			data->token_list->type = T_ENV;
		else
		{
			// printf("set_token_types , in ELSE\n");
			data->token_list->type = T_WORD;
		}
		// if (!check_error(data->token_list) && (data->exit_status = 258))
		// {
		// 	return (data->token_list->word);
		// }
		// if (data->token_list->word)
		// 	return (data->token_list->word);
		data->token_list = data->token_list->next;
	}
	data->token_list = head;
	// printf("set_token_types finished and return 0\n");
	return (NULL);
}


int	tokens_len(t_token **head)
{
	printf("tokens_len\n");//Debug
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

void print_tokens(t_data *data)
{
	printf("print_tokens\n");//Debug
	t_token *tmp;

	tmp = data->token_list;
	while (tmp)
	{
		printf("\nword: %s, type: %d\n", tmp->word, tmp->type);
		tmp = tmp->next;
	}
}