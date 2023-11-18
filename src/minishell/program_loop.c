/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:51:13 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/18 15:02:59 by ipetruni         ###   ########.fr       */
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
		{
			ft_strdel(&line);
			continue ;
		}
		// line = ft_strdup("echo ":           '$USER':" ':             "":'");
		// line = ft_strdup("echo "'"'"'"$USER"'"'"'"");
		data->input_line = trim_input(line);
		ft_strdel(&line);
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