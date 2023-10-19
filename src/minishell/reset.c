#include "minishell.h"

void reset_data(t_data *data)
{
	if (!data) // || !data->cmdexe
        return;
	ft_lstclear(&data->commands, free_command);
	//data->curr_dir = getcwd(NULL, 0);
}

void  reset_flags(t_flags *flags)
{
	flags->pipe[0] = 0;
	flags->pipe[1] = 0;
	flags->single_quote[0] = 0;
	flags->single_quote[1] = 0;
	flags->double_quote[0] = 0;
	flags->double_quote[1] = 0;
	flags->dollar = 0;
	flags->red_inp[0] = 0;
	flags->red_inp[1] = 0;
	flags->red_out[0] = 0;
	flags->red_out[1] = 0;
	flags->delimiter->delim_found = 0;
	flags->delimiter->content = NULL;
	flags->append[0] = 0;
	flags->append[1] = 0;
	flags->wildcard = 0;
	flags->or[0] = 0;
	flags->or[1] = 0;
	flags->and[0] = 0;
	flags->and[1] = 0;
	flags->p_id = 0;
	flags->exit_status = 0;
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