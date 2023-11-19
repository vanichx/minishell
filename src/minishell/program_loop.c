/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:51:13 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/19 17:01:52 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_loop(t_data *data)
{
	char	*line;
	
	while (1)
	{
		reset_data(data);
		line = readline(data->input_minishell);
		if (handle_d(data, line))
			continue ;
		if (ft_strlen(line) > 0)
			add_history(line);
		if (odd_quote(line, data))
			continue ;
		data->input_line = trim_input(line);
		ft_strdel(&line);
		// data->input_line = ft_strdup("(erik << cat ls << cat ls ) && erik << ls cat > erik");
		if ((special_chars(data->input_line))
			|| (lexical_analysis(data, data->input_line)))
			continue ;
		if (init_tree(data, &data->token_list))
			continue ;
		fix_tree(data->tree);
		print_tree(data->tree, 0);
		// if (execute(data))
		// 	continue ;
	}
}

void fix_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->type == T_DELIM || tree->type == T_RED_INP || tree->type == T_RED_OUT || tree->type == T_APPEND)
	{
		tree->value = ft_strdup(tree->right->value);
		
	}
}
