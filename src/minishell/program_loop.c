/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:51:13 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/10 13:44:05 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_loop(t_data *data)
{
	char	*line;
	// t_token *temp;
	
	while (1)
	{
		reset_data(data);
		line = readline(data->input_minishell);
		
		if (handle_d(data, line))
			continue ;
		if (ft_strlen(line) > 0)
			add_history(line);
		if (odd_quote(line, data))
		{
			ft_strdel(&line);
			continue ;
		}
		data->input_line = trim_input(line);
		ft_strdel(&line);
		
		check_exit(data->input_line);
		// // data->input_line = "erik || seferi ||  ivan";
		if ((special_chars(data->input_line))
			|| (lexical_analysis(data, data->input_line)))
			continue ;
		if (init_tree(data, &data->token_list))
			continue ;
		print_tree(data->tree, 0);
		//execute(data);
	}
}
// init_tree(data);
// last_input(data->tree);
// last_output(data->tree);
// printf("token length: %d\n", token_len(data->token_list));
// free(data->input_line);

// int	execute(t_data *data)
// {
// 	if (evaluate_execution(data, data->tree))
// 		return (1);
// 	if (execute(data))
// 		return (1);
// 	if (execute(data))
// 		return (1);
// 	return (0);
// }

// int evaluate_execution(t_data *data, t_tree *tree)
// {
// 	//  based on what is the root node
// 	if (is_llogic_root(tree))
// 	{
// 		if (execut_llogic(data, tree))
// 		return (1);
// 	}
// 	if (is_special_type)
// 	{
// 		if (execut_special(data, tree))
// 		return (1);
// 	}
// 	if (is_word_root(tree))
// 	{
// 		if (execut_word(data, tree))
// 		return (1);
// 	}
// 	return (0);
// }

