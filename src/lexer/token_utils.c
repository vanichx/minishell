#include "minishell.h"

void clean_null_tokens(t_token **head)
{
    t_token *current = *head;
    t_token *tmp;

    while (current != NULL)
    {
        tmp = current;
        if (ft_strlen(tmp->word) == 0)
        {
            if (tmp->prev != NULL)
                tmp->prev->next = tmp->next;
            else
                *head = tmp->next;
            if (tmp->next != NULL)
                tmp->next->prev = tmp->prev;
            current = tmp->next;
			ft_strdel(&tmp->word);
            free(tmp);
        }
        else
            current = current->next;
    }
}

// printing the tokens to debug
void print_tokens(t_data *data)
{
	t_token *tmp = data->token_list;
	while (tmp)
	{
		printf("\nword:%s:type:%d\n", tmp->word, tmp->type);
		tmp = tmp->next;
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