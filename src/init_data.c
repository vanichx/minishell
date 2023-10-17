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
	if (data->flags == NULL)
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