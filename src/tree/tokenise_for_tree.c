/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_for_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:51:52 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 16:03:27 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_temp_data_and_copy_tokens(t_token *t_parenth)
{
	t_data	*temp_data;
	t_token	*new_tokens;

	temp_data = init_temp_data();
	temp_data->input_line = ft_strdup(t_parenth->word);
	if (lexical_analysis_tree(temp_data, temp_data->input_line))
		return (NULL);
	new_tokens = copy_tokens(temp_data->token_list);
	if (!new_tokens)
	{
		printf("malloc error\n");
		return (NULL);
	}
	free_temp_data(temp_data);
	return (new_tokens);
}

t_token	*find_tail(t_token *head)
{
	t_token	*temp;
	t_token	*tail;

	temp = head;
	while (temp && temp->type != T_NEWLINE)
		temp = temp->next;
	tail = temp->prev;
	ft_strdel(&temp->word);
	free(temp);
	return (tail);
}

void	handle_head(t_token *atach_left, t_token *head, t_data *data)
{
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
}

void	handle_tail(t_token *atach_left, t_token *atach_right, t_token *tail)
{
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
}

int	tokenise_for_tree(t_token *t_parenth, t_data *data)
{
	t_token	*head;
	t_token	*tail;
	t_token	*atach_left;
	t_token	*atach_right;

	atach_left = t_parenth->prev;
	atach_right = t_parenth->next;
	head = init_temp_data_and_copy_tokens(t_parenth);
	if (!head)
		return (1);
	tail = find_tail(head);
	handle_head(atach_left, head, data);
	handle_tail(atach_left, atach_right, tail);
	return (0);
}
