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
		ft_strdel(&line);
		// data->input_line = "1 | 2 | << 3"; //debug
		check_exit(data->input_line);
		if (ft_strlen(data->input_line) > 0)
			add_history(data->input_line);
		if ((odd_quote(data->input_line, data)) || (special_chars(data->input_line))
			|| (lexical_analysis(data, data->input_line)))
			continue;
		print_tokens(data);
		// init_tree(data);
		// last_input(data->tree);
		// last_output(data->tree);

		// printf("token length: %d\n", token_len(data->token_list));
		
		// free(data->input_line);
	}
}


// ivan > erik > alex < hello < world > ls


//(echo Hello || echo Erik) || echo Privet


// (cat && ((echo "Hello") &&  (echo "Didn't find 'W'"))) || echo "Failed" || (echo "Failed 2" && echo "Failed 3") || (ls && echo "Failed 4" && echo "Failed 5")