/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_tree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:05:39 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 16:18:41 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_non_tword(t_tree *nontWord, t_tree **fntword, t_tree **lntword)
{
	if (!*fntword)
	{
		*fntword = nontWord;
		*lntword = *fntword;
	}
	else
	{
		(*lntword)->right = nontWord;
		*lntword = nontWord;
	}
}

void	process_word(t_tree *word, t_tree *address)
{
	t_tree	*tmp2;

	address->args_array = join2darrays(address->args_array, word->args_array);
	ft_strdel(&word->value);
	tmp2 = word->right;
	address->right = tmp2;
	free(word);
}

void	find_command(t_tree **tree)
{
	t_tree	*tmp;
	t_tree	*address;
	t_tree	*firstnontword;
	t_tree	*lastnontword;

	tmp = (*tree)->right;
	address = *tree;
	firstnontword = NULL;
	lastnontword = NULL;
	while (tmp)
	{
		if (tmp->type != T_WORD)
		{
			append_non_tword(tmp, &firstnontword, &lastnontword);
			tmp = tmp->right;
		}
		else if (tmp->type == T_WORD)
		{
			process_word(tmp, address);
			tmp = tmp->right;
		}
	}
	if (lastnontword)
		lastnontword->right = NULL;
	address->right = firstnontword;
}
