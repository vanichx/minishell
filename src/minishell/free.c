#include "minishell.h"

void	free_data(t_data *data)
{
    if (!data)
        return ;
	ft_lstclear(&data->env, free_envir);
	data->env = NULL;
    ft_lstclear(&data->commands, free_command);
	data->commands = NULL;
	if (data->curr_dir && data->curr_dir[0] != '\0')
		free(data->curr_dir);
	// if (data->promt && data->promt[0] != '\0')
	// 	free(data->promt);
	free(data);
	data = NULL;
}

void	free_flags(t_flags *flags)
{
    if (!flags)
        return ;
	free_delimiter(flags->delimiter);
	reset_flags(flags);
    free(flags);
	flags = NULL;
}

void	free_delimiter(t_delim *delimiter)
{
	if (!delimiter)
		return ;
	if (delimiter->content && delimiter->content[0] != '\0')
	{
		free(delimiter->content);
		delimiter->content = NULL;
	}
	if (delimiter->delim_found)
		delimiter->delim_found = 0;
	delimiter = NULL;
}

void	free_envir(void *envir)
{
    t_envir	*tmp;

    if (!envir)
        return ;
    tmp = (t_envir *)envir;
	if (tmp->var_name && tmp->var_name[0] != '\0')
	{
		free(tmp->var_name);
		tmp->var_name = NULL;
	}
	if (tmp->var_value && tmp->var_value[0] != '\0')
	{
		free(tmp->var_value);
		tmp->var_value = NULL;
	}
    free(tmp);
}

void	free_command(void *command)
{
    t_cmdexe *tmp;

	tmp = (t_cmdexe *)command;
	if (!command || !tmp)
		return ;
	if (tmp->path && tmp->path[0] != '\0')
	{
		free(tmp->path);
		tmp->path = NULL;
	}
	if (tmp->cmd && tmp->cmd[0] != '\0')
	{
		free(tmp->cmd);
		tmp->cmd = NULL;
	}
	if (tmp->flags && tmp->flags->pipe[0] != 0 && tmp->flags->pipe[1] != 0)
		free_flags(tmp->flags);
	tmp->idx = 0;
	free(tmp);
}

void	free_2darray(char **array)
{
    int	i;

    if (!array)
        return ;
    i = 0;
    while (array[i] != NULL)
    {
        free(array[i]);
        array[i] = NULL;
        i++;
    }
    free(array);
	array = NULL;
}