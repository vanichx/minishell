/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:00:34 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 16:02:38 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_left_node(t_tree **t, t_token **address, t_data *data, int flag)
{
	t_token	*tmp_left;

	tmp_left = find_tree_root_left(&(*address)->prev);
	if (tmp_left && ft_strcmp(tmp_left->word, "boundary"))
	{
		(*t)->left = init_tree_root();
		(*t)->left->parenth = flag;
		if (tmp_left->type)
			(*t)->left->type = tmp_left->type;
		if (tmp_left->word)
			(*t)->left->value = ft_strdup(tmp_left->word);
		ft_strdel(&tmp_left->word);
		tmp_left->word = ft_strdup("boundary");
		if ((*t)->left->type == T_WORD)
		{
			(*t)->left->args_array = ft_split_args((*t)->left->value, ' ');
			find_quotes((*t)->left->args_array, data);
		}
		if (built_tree(&(*t)->left, tmp_left, data))
			return (1);
	}
	else
		(*t)->left = NULL;
	return (0);
}

int	create_right_node(t_tree **t, t_token **address, t_data *data, int flag)
{
	t_token	*tmp_right;

	tmp_right = find_tree_root_right(&(*address)->next);
	if (tmp_right && ft_strcmp(tmp_right->word, "boundary"))
	{
		(*t)->right = init_tree_root();
		(*t)->right->parenth = flag;
		(*t)->right->type = tmp_right->type;
		if (tmp_right->word)
		{
			(*t)->right->value = ft_strdup(tmp_right->word);
			ft_strdel(&tmp_right->word);
		}
		tmp_right->word = ft_strdup("boundary");
		if ((*t)->right->type == T_WORD)
		{
			(*t)->right->args_array = ft_split_args((*t)->right->value, ' ');
			find_quotes((*t)->right->args_array, data);
		}
		if (built_tree(&(*t)->right, tmp_right, data))
			return (1);
	}
	else
		(*t)->right = NULL;
	return (0);
}

int	tokenise_and_find_root(t_token **address, t_data *data)
{
	if (tokenise_for_tree(*address, data))
		return (1);
	*address = find_tree_root_left(&(*address)->prev);
	return (0);
}
