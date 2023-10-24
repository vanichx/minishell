/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 23:35:40 by eseferi           #+#    #+#             */
/*   Updated: 2023/10/24 13:52:22 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		*head = new;
}

void	add_token_front(t_token **head, t_token *new)
{
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
	t_token *new;

	new = NULL;
	data->token_list = new;
	if (!(new = malloc(sizeof(t_token))))
		exit_shell("Error: malloc failed\n", 1, data);
	new->word = ft_substr(data->input_line, 
	i - data->count, data->count);
	data->count = 0;
	return (new);
}

t_token	*create_arg_token(t_data *data, char *word, enum e_token_type type)
{
	t_token *new;

	new = NULL;
	data->token_list = new;
	if (!(new = ft_calloc(1, sizeof(t_token))))
		exit_shell("Error: malloc failed\n", 1, data);
	new->word = ft_strdup(word);
	new->type = type;
	return (new);
}

char	*iter_tokens(t_data *data)
{
	
	while (data->token_list->next)
	{
		if (ft_strchr(data->token_list->word, '>') || ft_strchr(data->token_list->word, '<') || !ft_strcmp(data->token_list->word, ">>") || !ft_strcmp(data->token_list->word, "<<"))
			data->token_list->type = T_REDIRECT;
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
			data->token_list->type = T_WORD;
			printf("I am in type word\n");
		}
		// if (!check_error(data->token_list) && (data->exit_status = 258))
		// {
		// 	printf("I am before check_error\n");
		// 	return (data->token_list->word);
		// 	printf("I am after check_error\n");
		// }
		// printf("I am here\n");
		// if (data->token_list->word)
		// 	return (data->token_list->word);
		printf("Type = %d\n", data->token_list->type);
		data->token_list = data->token_list->next;
	}
	printf("I am after word\n");
	return (NULL);
}

void	clear_token(t_token **token, void (*del)(void*))
{
	t_token *tmp;
	t_token *tmp2;
	
	if (!token || !del)
		return ;
	tmp = *token;
	while (tmp)
	{
		ft_strdel(&tmp->word);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*token = NULL;
}

int	tokens_len(t_token **head)
{
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
	t_token *tmp;

	tmp = data->token_list;
	while (tmp)
	{
		printf("\nword: %s, type: %d\n", tmp->word, tmp->type);
		tmp = tmp->next;
	}
}