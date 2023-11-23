/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_tree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:05:39 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 17:37:49 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void find_command(t_tree **tree)
{
	 t_tree *tmp;
	 t_tree *tmp2;
	 t_tree *address;
	 char **command;

	 command = NULL;

	 if (!tree || !*tree)
		  return;

	 tmp2 = NULL;
	 tmp = (*tree)->right;
	 address = (*tree);
	 t_tree *firstNonTWord = NULL;
	 t_tree *lastNonTWord = NULL;

	 while (tmp)
	 {
		  if (tmp->type != T_WORD)
		  {
				if (!firstNonTWord)
				{
					 firstNonTWord = tmp;
					 lastNonTWord = firstNonTWord;
				}
				else
				{
					 lastNonTWord->right = tmp;
					 lastNonTWord = tmp;
				}
				tmp2 = tmp;
				tmp = tmp->right;
		  }
		  else if (tmp->type == T_WORD)
		  {
				address->args_array = join2darrays(address->args_array, tmp->args_array);
				ft_strdel(&tmp->value);
				tmp2 = tmp->right;
				address->right = tmp2;
				free(tmp);
				tmp = tmp2;
		  }
	 }

	 if (lastNonTWord)
		  lastNonTWord->right = NULL; // Terminate the list of non-T_WORD tokens
	address->right = firstNonTWord;
}

