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
	free_commands(data);
	// clear_cmd(data->cmd_list);
	// ft_cmdclear(&data->cmd_list); // need for th future 
	// free_2darray(data->cmd_array);
	// free_2darray(data->path);
	// data->curr_dir = getcwd(NULL, 0);
}

// void	reset_commands(void *command)
// {
// 	t_cmdexe *tmp;

// 	tmp = (t_cmdexe *)command;
// 	if (!tmp)
// 		return ;
// 	if (tmp->path)
// 		tmp->path = NULL;
// 	if (tmp->cmd)
// 	{
// 		free(tmp->cmd);
// 		tmp->cmd = NULL;
// 	}
// 	reset_flags(tmp->flags);
// 	tmp->idx = 0;
// }