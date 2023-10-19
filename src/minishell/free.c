#include "minishell.h"

void	free_data(t_data *data)
{
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
	free_delimiter(flags->delimiter);
	reset_flags(flags);
    free(flags);
	flags = NULL;
}

void	free_delimiter(t_delim *delimiter)
{
	if (!delimiter)
		return ;
	if (delimiter->content)
	{
		free(delimiter->content);
		delimiter->content = NULL;
	}
	free(delimiter);
	delimiter = NULL;
}

void	free_envir(void *envir)
{
    t_envir	*tmp;

    if (!envir)
        return ;
    tmp = (t_envir *)envir;
	if (tmp->var_name)
	{
		free(tmp->var_name);
		tmp->var_name = NULL;
	}
	if (tmp->var_value)
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
	if (tmp->path)
	{
		free(tmp->path);
		tmp->path = NULL;
	}
	if (tmp->cmd)
	{
		free(tmp->cmd);
		tmp->cmd = NULL;
	}
	if (tmp->flags)
		free_flags(tmp->flags);
	free(tmp);
	tmp = NULL;
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