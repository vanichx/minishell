/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:51:13 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/09 17:39:23 by ipetruni         ###   ########.fr       */
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

// void	execute(t_data *data)
// {
	// find a general rules for execution
			// delim
			// pipe
			// redirection
			// builtin
	// if built in, execute_builtin
	// else execute_command
// }