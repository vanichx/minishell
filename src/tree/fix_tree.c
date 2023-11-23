/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:59:11 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 16:29:42 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fix_tree(t_tree **tree)
{
	fix_command(tree);
	fix_redirection(tree);
}

void	connect_nodes(t_tree **temp_redir, t_tree *temp2)
{
	t_tree	*last_redir;

	if (*temp_redir == NULL)
	{
		*temp_redir = temp2;
		(*temp_redir)->right = NULL;
	}
	else
	{
		last_redir = *temp_redir;
		while (last_redir->right)
		{
			last_redir = last_redir->right;
		}
		last_redir->right = temp2;
		temp2->right = NULL;
	}
}

void	handle_word_type(t_tree **tree, t_tree **temp, t_tree **temp_redir)
{
	t_tree	*temp2;

	*temp = *tree;
	*temp_redir = (*tree)->left;
	while (*temp && (*temp)->right && (*temp)->right->type != T_NEWLINE)
	{
		if ((*temp)->right->type == T_DELIM
			|| (*temp)->right->type == T_RED_INP)
		{
			temp2 = (*temp)->right;
			(*temp)->right = temp2->right;
			connect_nodes(temp_redir, temp2);
		}
		else
			*temp = (*temp)->right;
	}
	(*tree)->left = *temp_redir;
}

void	fix_redirection(t_tree **tree)
{
	t_tree	*temp;
	t_tree	*temp_redir;

	temp = NULL;
	temp_redir = NULL;
	if (!tree || !*tree)
		return ;
	if ((*tree)->type == T_WORD)
	{
		handle_word_type(tree, &temp, &temp_redir);
	}
	else
	{
		fix_redirection(&(*tree)->left);
		fix_redirection(&(*tree)->right);
	}
}
