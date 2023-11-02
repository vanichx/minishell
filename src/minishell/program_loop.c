#include "minishell.h"

void	start_loop(t_data *data)
{
	char *line;
	while (1)
	{
		reset_data(data);
		line = readline(data->input_minishell);
		if (handle_d(data, line))
			continue;
		data->input_line = trim_input(line);
		data->input_line_errors = trim_input_parenth(data->input_line);
		ft_strdel(&line);
		// printf("input_line = %s\n", data->input_line);//debug
		// printf("input_line_errors = :%s:\n", data->input_line_errors);//debug
		// data->input_line = "(hello my name is school)"; //debug
		// data->input_line_errors = "hello my name is school"; //debug
		check_exit(data->input_line);
		if (ft_strlen(data->input_line) > 0)
			add_history(data->input_line);
		if ((odd_quote(data->input_line_errors, data)) || (special_chars(data->input_line_errors))
			|| (lexical_analysis(data, data->input_line_errors)))
		{
			free_tokens(&data->token_list, free);
			continue ;
		}
		if ((odd_quote(data->input_line, data)) || (special_chars(data->input_line))
			|| (lexical_analysis(data, data->input_line)))
			continue;
		print_tokens(data);//debug
		// init_tree(data->token_list);
		// last_input(data->tree);
		// last_output(data->tree);

		// printf("token length: %d\n", token_len(data->token_list));
		
		// free(data->input_line);
	}
}


// ivan > erik > alex < hello < world > ls


//(echo Hello || echo Erik) || echo Privet


// (cat && ((echo "Hello") &&  (echo "Didn't find 'W'"))) || echo "Failed" || (echo "Failed 2" && echo "Failed 3") || (ls && echo "Failed 4" && echo "Failed 5")