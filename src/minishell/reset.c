#include "minishell.h"

void reset_data(t_data *data)
{
	reset_flags(data->flags);
	reset_cmdexe(data->cmdexe);
}

void reset_cmdexe(t_cmdexe *cmdexe)
{
	cmdexe->cmd = NULL;
	cmdexe->cmd_args = NULL;
	cmdexe->cmd_paths = NULL;
	cmdexe->idx = 0;
	cmdexe->path = NULL;
	cmdexe->cmd_nbrs = 0;
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
	flags->delimiter.delim_found = 0;
	flags->delimiter.content = NULL;
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
