#include "minishell.h"

void	start_loop(t_data *data)
{
	char *line;
	while (1)
	{
		line = readline(data->input_minishell);
		data->input_line = trim_input(line);
		ft_strdel(&line);
		// data->input_line = "erik seferi | | |";
		// line = trim_input(data->input_line);
		if (data->input_line == NULL)
			handle_d(data);
		check_exit(data->input_line);
		if (ft_strlen(data->input_line) > 0)
			add_history(data->input_line);
		if (odd_quote(data->input_line, data))
			continue;
		if (special_chars(data->input_line))
			continue;
		lexical_analysis(data, data->input_line);
		// print_tokens(data);////Debug
		// execute_command(data);
		reset_data(data);
		// free(data->input_line);
	}
}