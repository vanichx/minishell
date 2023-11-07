/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:32:51 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/07 11:19:24 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_data(t_data *data)
{
	data->single_quote = 0;
	data->double_quote = 0;
	data->forked = 0;
	// if (data->curr_dir)
	// 	ft_strdel(&data->curr_dir);
	// if (data->input_line && ft_strlen(data->input_line) > 0)
	// 	ft_strdel(&data->input_line);
	// if (data->tree)
	// 	free_tree(data->tree);
	free_tokens(&data->token_list, free);
}
