#include "minishell.h"

void reset_data(t_data *data)
{
	// ft_cmdclear(&data->cmd_list);

	// free_2darray(data->cmd_array);
	// free_2darray(data->path);
	if (data->curr_dir)
		free(data->curr_dir);
	data->curr_dir = getcwd(NULL, 0);
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