/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:40:22 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/10 16:10:16 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_word(t_data *data, t_tree *tree)
{
	if (is_builtin(tree->args_array[0]))
	{
		if (execute_builtin(tree))
			return (1);
	}
	// else
	// {
	// 	if (execute_command(data, tree))
	// 		return (1);		
	// }
	return (0);
}
