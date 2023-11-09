/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_for_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:51:52 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/09 17:37:11 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenise_for_tree(t_token *t_parenth, t_data *data)
{
   	t_token *head;
    t_token *tail;
    t_token *temp;
    t_token *atach_left;
    t_token *atach_right;
    t_data *temp_data;
	t_token *new_tokens;

    atach_left = t_parenth->prev;
    atach_right = t_parenth->next;

    temp_data = init_temp_data();
    temp_data->input_line = ft_strdup(t_parenth->word);
    if (lexical_analysis(temp_data, temp_data->input_line))
        return (1);
	new_tokens = copy_tokens(temp_data->token_list);
	if (!new_tokens)
	{
		printf("malloc error\n");
		return (1);
	}
	free_data(temp_data);
	head = new_tokens;
	temp = head;
	while (temp && temp->type != T_NEWLINE)
		temp = temp->next;
	tail = temp->prev;
	ft_strdel(&temp->word);
	free(temp);
	if (!atach_left && head)
	{
		head->prev = NULL;
		data->token_list = head;
	}
	if (atach_left && head)
	{
		ft_strdel(&atach_left->next->word);
		free(atach_left->next);
		atach_left->next = head;
		head->prev = atach_left;
	}
	if (atach_right->type && tail)
	{
		if (!atach_left)
		{
			ft_strdel(&atach_right->prev->word);
			free(atach_right->prev);
		}
		atach_right->prev = tail;
		tail->next = atach_right;
	}
	else
	{
		ft_strdel(&atach_right->prev->word);
		atach_right->prev = tail;
		tail->next = atach_right;
	}
    return (0);
}

t_data	*init_temp_data(void)
{
	t_data *temp_data;
	temp_data = malloc(sizeof(t_data));
	temp_data->token_list = NULL;
	temp_data->tree = NULL;
	temp_data->env_list = NULL;
	temp_data->sorted_env_list = NULL;
	temp_data->input_line = NULL;
	temp_data->input_minishell = NULL;
	temp_data->curr_dir = NULL;
	temp_data->exit_str = NULL;
	temp_data->path = NULL;
	return (temp_data);
}

t_token *find_token_parenth(t_token **head)
{
	t_token *tmp;
	tmp = *head;
	while (tmp)
	{
		if (tmp->type == T_PARENTHESES)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

t_token *copy_tokens(t_token *head)
{
    t_token *tmp;
    t_token *new_head;
    t_token *new_tmp;

    tmp = head;
    new_head = NULL;
    while (tmp)
    {
        new_tmp = malloc(sizeof(t_token));
        if (!new_tmp)
        {
            free_tokens(&new_head, free);
            return (NULL);
        }
        new_tmp->type = tmp->type;
        new_tmp->word = ft_strdup(tmp->word);
        new_tmp->next = NULL;
        new_tmp->prev = NULL;
        add_token(&new_head, new_tmp);
        tmp = tmp->next;
    }
    return (new_head);
}