/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 07:47:19 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/26 08:31:00 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_fix_com(t_tree **tree)
{
	t_tree	*tmp;
	t_tree	*tmp2;

	tmp = init_tree_root();
	tmp->type = T_WORD;
	tmp2 = *tree;
	tmp->right = tmp2;
	*tree = tmp;
	find_command(&tmp);
	if (!tmp->args_array)
	{
		tmp->value = ft_strdup("");
		tmp->args_array = (char **)malloc(sizeof(char *) * 2);
		tmp->args_array[0] = ft_strdup("");
		tmp->args_array[1] = NULL;
	}
	else
		tmp->value = ft_strdup(tmp->args_array[0]);
}

void	update_non_tword_nodes(t_tree **firstNonTWord, t_tree **lastNonTWord, \
	t_tree **tmp, t_tree **tmp2)
{
	if (!*firstNonTWord)
	{
		*firstNonTWord = *tmp;
		*lastNonTWord = *firstNonTWord;
	}
	else
	{
		(*lastNonTWord)->right = *tmp;
		*lastNonTWord = *tmp;
	}
	*tmp2 = *tmp;
	*tmp = (*tmp)->right;
}

void	update_tword_node(t_tree *address, t_tree **tmp, t_tree **tmp2)
{
	address->args_array = join2darrays(address->args_array, (*tmp)->args_array);
	ft_strdel(&(*tmp)->value);
	*tmp2 = (*tmp)->right;
	address->right = *tmp2;
	free(*tmp);
	*tmp = *tmp2;
}

void	find_command(t_tree **tree)
{
	t_find_command	vars;

	if (!tree || !*tree)
		return ;
	vars.firstNonTWord = NULL;
	vars.lastNonTWord = NULL;
	vars.tmp2 = NULL;
	vars.tmp = (*tree)->right;
	vars.address = (*tree);
	while (vars.tmp)
	{
		if (vars.tmp->type != T_WORD)
			update_non_tword_nodes(&vars.firstNonTWord, \
			&vars.lastNonTWord, &vars.tmp, &vars.tmp2);
		else if (vars.tmp->type == T_WORD)
			update_tword_node(vars.address, &vars.tmp, &vars.tmp2);
	}
	if (vars.lastNonTWord)
		vars.lastNonTWord->right = NULL;
	vars.address->right = vars.firstNonTWord;
}
