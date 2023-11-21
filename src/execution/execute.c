/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:06:51 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/21 12:41:08 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_data *data)
{
	if (evaluate_execution(data, data->tree))
		return (1);
	data->exit_status = 0;
	return (data->exit_status);
}

int evaluate_execution(t_data *data, t_tree *tree)
{	
	if (is_logic_root(tree))
		if (execute_logic(data, tree))
		return (1);	
	// if (tree->type == T_PIPE)
	// 	if (execute_pipe(data, tree))
	// 		return (1);
	if (is_word_root(tree))
	{
		if ((tree->right->type == T_NEWLINE || tree->right == NULL) && tree->left == NULL )
		{
			if (execute_word(data, tree))
				return (1);	
		}
		else 
		{
			if (tree->left && is_special_root(tree->left))
			{
				// printf("FUNC evaluate_execution\n");
				if (execute_special_left(data, tree))
					return (1);
			}	
			else if (tree->right && is_special_root(tree->right))
			{
				if (execute_special(data, tree))
					return (1);
			}
		}
	}
	return (0);
}
				
int	execute_logic(t_data *data, t_tree *tree)
{
	if (tree->type == T_AND)
		if (execute_and(data, tree))
			return (1);		
	if (tree->type == T_OR)
		if (execute_or(data, tree))
			return (1);
	return (0);
}


int execute_special(t_data *data, t_tree *tree)
{
	t_tree *root;

	root = tree;
	if (tree != NULL)
	{
		
		if (tree->right->type == T_RED_INP || tree->right->type == T_THREE_IN || tree->right->type == T_DELIM)
		{
			if (execute_redin(data, tree, root))
				return (1);
		}
		if (tree->right->type == T_RED_OUT || tree->right->type == T_APPEND)
		{
			if (execute_redout(data, tree))
				return (1);
		}
		
	}
	else
		return (1);
	return (0);
}

int execute_special_left(t_data *data, t_tree *tree)
{
	t_tree *left_top_node;
	t_tree *root;

	root = tree;
	// printf("t_tree *root->type = %d *root->value = %s\n", root->type, root->value);
	left_top_node = tree->left;
	
	if (left_top_node != NULL)
	{
		// printf("FUNC execute_special_left\n");
		if (left_top_node->type == T_RED_INP || left_top_node->type == T_THREE_IN || left_top_node->type == T_DELIM)
			if (execute_redin(data, left_top_node, root))
				return (1);
		if (left_top_node->type == T_RED_OUT || left_top_node->type == T_APPEND)
		{
			if (execute_redout(data, left_top_node))
				return (1);
		}
	}
	else
		return (1);
	return (0);
}