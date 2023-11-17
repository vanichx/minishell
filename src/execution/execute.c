/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:06:51 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/17 10:41:02 by ipetruni         ###   ########.fr       */
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
	if (is_special_root(tree))
		if (execute_special(data, tree))
			return (1);
	if (is_word_root(tree))
		if (execute_word(data, tree))
			return (1);
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
	if (tree != NULL)
	{
		if (tree->type == T_PIPE)
			if (execute_pipe(data, tree))
				return (1);
		if (tree->type == T_RED_INP || tree->type == T_THREE_IN)
			if (execute_redin(data, tree))
				return (1);
		if (tree->type == T_RED_OUT)
			if (execute_redout(data, tree))
				return (1);
		if (tree->type == T_APPEND)
			if (execute_append(data, tree))
				return (1);
		if (tree->type == T_DELIM)
			if (execute_delim(data, tree, tree->right->args_array[0]))
				return (1);
	}
	else
		return (1);
	return (0);
}
