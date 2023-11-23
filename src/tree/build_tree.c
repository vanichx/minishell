/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:41:36 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 16:00:46 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_left_node(t_tree **tmp_tree, t_token **adr, t_data *data, int *flag)
{
	t_token	*tmp_left;

	tmp_left = find_tree_root_left(&(*adr)->prev);
	if (tmp_left && tmp_left->type == T_PARENTHESES)
	{
		if (tokenise_and_find_root(&tmp_left, data))
			return (1);
		*flag = 1;
	}
	else
	{
		*flag = 0;
	}
	if (create_left_node(tmp_tree, adr, data, *flag))
		return (1);
	return (0);
}

int	handle_right_node(t_tree **tmp_tree, t_token **adr, t_data *data, int *flag)
{
	t_token	*tmp_right;

	tmp_right = find_tree_root_right(&(*adr)->next);
	if (tmp_right && tmp_right->type == T_PARENTHESES)
	{
		if (tokenise_and_find_root(&tmp_right, data))
			return (1);
		*flag = 1;
	}
	else
	{
		*flag = 0;
	}
	if (create_right_node(tmp_tree, adr, data, *flag))
		return (1);
	return (0);
}

int	built_tree(t_tree **tree, t_token *adr, t_data *data)
{
	int		flag;
	t_tree	*tmp_tree;

	tmp_tree = *tree;
	if (!adr || adr->type == T_NEWLINE)
		return (0);
	if (handle_left_node(&tmp_tree, &adr, data, &flag))
		return (1);
	if (handle_right_node(&tmp_tree, &adr, data, &flag))
		return (1);
	return (0);
}
