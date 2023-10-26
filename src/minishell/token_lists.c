#include "minishell.h"

void add_token(t_token **head, t_token *new)
{
    printf("add_token\n"); // Debug
    t_token *tmp;
    
    if (!new || !head)
        return;
    
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
        // If the head is not present, create it
        *head = new;
        new->prev = NULL;
        new->next = NULL;
		printf("CREATED HEAD NODE \n");
    }
    
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
	data->count = 0;
	return (new);
}

t_token	*create_arg_token(t_data *data, char *word, enum e_token_type type)
{
	printf("create_arg_token\n");//Debug
	t_token *new;

	if (!(new = ft_calloc(1, sizeof(t_token))))
		exit_shell("Error: malloc failed\n", 1, data);
	new->word = ft_strdup(word);
	new->type = type;
	return (new);
}




void	set_token_types(t_data *data)
{
	t_token *head;

	head = data->token_list;
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
		else if (ft_strchr(data->token_list->word, '$'))
			data->token_list->type = T_DOLLAR;
		else if ((data->token_list->type == T_NEWLINE || ft_strchr(data->token_list->word, '\n')) && !data->token_list->next)
            data->token_list->type = T_NEWLINE;
		else if (is_valid_env(data->token_list->word))
			data->token_list->type = T_ENV;
		else
			data->token_list->type = T_WORD;
		data->token_list = data->token_list->next;
	}
	data->token_list = head;
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
	t_token *tmp = data->token_list;

	while (tmp)
	{
		printf("\nword: %s, type: %d\n", tmp->word, tmp->type);
		tmp = tmp->next;
	}
}