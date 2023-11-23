/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:33:05 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 14:27:53 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tabs(int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("\t");
		i++;
	}
}

void	print_node_info(t_tree *tree, int depth)
{
	print_tabs(depth);
	printf("Node word: :%s:, type: %d\n", tree->value, tree->type);
	if (tree->parenth == 1)
	{
		print_tabs(depth);
		printf("Parenth on\n");
	}
}

void	print_args_array(char **args_array)
{
	int	k;

	k = 0;
	printf("Args array: ");
	while (args_array[k] != NULL)
	{
		printf("arg[%d] = %s ", k, args_array[k]);
		k++;
	}
	printf("\n");
}

void	print_child_node(t_tree *child, int depth, const char *position)
{
	int	i;

	i = 0;
	while (i <= depth)
	{
		printf("\t");
		i++;
	}
	printf("%s child of above node:\n", position);
	print_tree(child, depth + 1);
}

void	print_tree(t_tree *tree, int depth)
{
	if (!tree)
		return ;
	print_tabs(depth);
	print_node_info(tree, depth);
	if (tree->type == T_WORD || tree->type == T_DELIM)
	{
		if (tree->args_array)
			print_args_array(tree->args_array);
	}
	if (tree->left)
		print_child_node(tree->left, depth, "Left");
	if (tree->right)
		print_child_node(tree->right, depth, "Right");
}
