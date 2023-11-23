/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_tree_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:24:33 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 16:52:39 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_tree_type(t_tree **tree, t_tree *tmp, t_tree *tmp2)
{
	tmp = init_tree_root();
	tmp->type = T_WORD;
	tmp2 = *tree;
	tmp->right = tmp2;
	*tree = tmp;
	find_command(&tmp);
	if (!tmp->args_array)
	{
		tmp->value = ft_strdup("");
		tmp->args_array = (char **) malloc(sizeof(char *) * 2);
		tmp->args_array[0] = ft_strdup("");
		tmp->args_array[1] = NULL;
	}
	else
		tmp->value = ft_strdup(tmp->args_array[0]);
}

void	fix_command(t_tree **tree)
{
	t_tree	*tmp;
	t_tree	*tmp2;

	if (!tree || !*tree)
		return ;
	tmp = NULL;
	tmp2 = NULL;
	if ((*tree)->type == T_APPEND || (*tree)->type == T_DELIM
		|| (*tree)->type == T_RED_INP
		|| (*tree)->type == T_RED_OUT || (*tree)->type == T_WORD)
	{
		handle_tree_type(tree, tmp, tmp2);
	}
	else
	{
		fix_command(&(*tree)->left);
		fix_command(&(*tree)->right);
	}
}
