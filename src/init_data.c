#include "../minishell.h"

t_data	*init_data(char *envp[])
{
	t_data *data;
	
	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
	{
		perror("Memory allocation failed for data");
		exit(1);
	}
	data->flags = init_flags();
	data->cmdexe = init_cmdexe();
	if (data->flags == NULL || data->cmdexe == NULL)
	{
		free_data(data);
		exit(1);
	}
	data->env = get_env_vars(envp);
	data->promt = "minishell>> ";
	return (data);
}

t_flags	*init_flags(void)
{
    t_flags *flags = ft_calloc(1, sizeof(t_flags));
    if (flags == NULL)
        return (NULL); // Memory allocation failed
    return (flags);
}

t_cmdexe *init_cmdexe(void)
{
	t_cmdexe *cmdexe = ft_calloc(1, sizeof(t_cmdexe));
	if (cmdexe == NULL)
		return (NULL);
	return (cmdexe);
}

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