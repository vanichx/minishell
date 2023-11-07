/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:51:13 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/07 16:17:13 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_loop(t_data *data)
{
	// char	*line;
	// t_token *temp;
	
	while (1)
	{
git s		reset_data(data);
		// line = readline(data->input_minishell);
		// if (handle_d(data, line))
		// 	continue ;
		// if (ft_strlen(line) > 0)
		// 	add_history(line);
		// data->input_line = trim_input(line);
		// ft_strdel(&line);
		
		// check_exit(data->input_line);
		data->input_line = "erik || seferi ||  ivan";
		if ((odd_quote(data->input_line, data))
			|| (special_chars(data->input_line))
			|| (lexical_analysis(data, data->input_line)))
			continue ;
		// temp = find_token_parenth(&data->token_list);
		// if (tokenise_for_tree(temp))
		// 	continue ;
		// print_tokens(data);
		
		if (init_tree(data, &data->token_list))
			continue ;
		// print_tree(data->tree);
	}
}
// init_tree(data);
// last_input(data->tree);
// last_output(data->tree);
// printf("token length: %d\n", token_len(data->token_list));
// free(data->input_line);
