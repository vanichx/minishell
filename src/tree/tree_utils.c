/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:38:47 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 14:36:31 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_temp_data(void)
{
	t_data	*temp_data;

	temp_data = malloc(sizeof(t_data));
	temp_data->token_list = NULL;
	temp_data->tree = NULL;
	temp_data->env_list = NULL;
	temp_data->sorted_env_list = NULL;
	temp_data->input_line = NULL;
	temp_data->input_minishell = NULL;
	temp_data->curr_dir = NULL;
	temp_data->exit_str = NULL;
	return (temp_data);
}

t_token	*find_token_parenth(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == T_PARENTHESES)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

t_token	*copy_tokens(t_token *head)
{
	t_token	*tmp;
	t_token	*new_head;
	t_token	*new_tmp;

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

t_tree	*init_tree_root(void)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = 0;
	tree->value = NULL;
	tree->args_array = NULL;
	tree->parenth = 0;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

int	is_special_type(t_token *address)
{
	return (address->type == T_RED_INP
		|| address->type == T_RED_OUT
		|| address->type == T_APPEND || address->type == T_DELIM
		|| address->type == T_THREE_IN);
}
