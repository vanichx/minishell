#include "minishell.h"

void reset_data(t_data *data)
{
	data->single_quote = 0;
	data->double_quote = 0;
	data->forked = 0;
	if (data->curr_dir)
		ft_strdel(&data->curr_dir);
	if (data->input_line && ft_strlen(data->input_line) > 0)
		ft_strdel(&data->input_line);
	free_tokens(&data->token_list, free);
	
	// data->curr_dir = getcwd(NULL, 0);
}
