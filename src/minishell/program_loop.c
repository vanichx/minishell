/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:51:13 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/17 17:24:02 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_loop(t_data *data)
{
	char	*line;
	char	*expanded_line;
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
		expanded_line = expand_input_line(data, data->input_line);
		ft_strdel(&data->input_line);
		ft_strdel(&line);
		data->input_line = expanded_line;
		printf("%s\n", data->input_line);
		if ((special_chars(data->input_line))
			|| (lexical_analysis(data, data->input_line)))
			continue ;
		if (init_tree(data, &data->token_list))
			continue ;
		// print_tree(data->tree, 0);
		if (execute(data))
			continue ;
	}
}

// last_input(data->tree);
// last_output(data->tree);
// printf("token length: %d\n", token_len(data->token_list));
