/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_for_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:51:52 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/07 17:48:23 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenise_for_tree(t_token *t_parenth)
{
    t_token *head;
    t_token *tail;
    t_token *temp;
    t_token *atach_left;
    t_token *atach_right;
    t_data *temp_data;

    atach_left = t_parenth->prev;
    atach_right = t_parenth->next;

    temp_data = init_temp_data();
    // printf("%s", t_parenth->word);
    temp_data->input_line = ft_strdup(t_parenth->word);
	ft_strdel(&t_parenth->word);
    if (lexical_analysis(temp_data, temp_data->input_line))
        return (1);
    head = temp_data->token_list;
    temp = head;
    while (temp && temp->type != T_NEWLINE)
        temp = temp->next;
    tail = temp;
    if (tail)
        tail = tail->prev;
    if (tail && tail->next) {
        ft_strdel(&tail->next->word);
        free(tail->next);
    }
    if (!atach_left && head)
        head->prev = NULL;
    if (!atach_right && tail)
        tail->next = NULL;
    if (atach_left && head)
    {
        atach_left->next = head;
        head->prev = atach_left;
    }
    if (atach_right && tail)
    {
        atach_right->prev = tail;
        tail->next = atach_right;
    }
    ft_strdel(&temp_data->input_line);
    free(temp_data);
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
	temp_data->env_array = NULL;
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