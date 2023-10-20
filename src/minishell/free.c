#include "minishell.h"

void	free_data(t_data *data)
{
	ft_envclear(&data->env);
	data->env = NULL;
	ft_cmdclear(&data->commands);
	data->commands = NULL;
	// if (data->curr_dir && data->curr_dir[0] != '\0')
	// 	free(data->curr_dir);
	// if (data->promt && data->promt[0] != '\0')
	// 	free(data->promt);
	free(data);
	data = NULL;
}

void	free_flags(t_flags *flags)
{
	if (!flags)
		return ;
	if (flags->delimiter)
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

void	free_cmdexe(void *command)
{
	t_cmdexe *tmp;

	tmp = (t_cmdexe *)command;
	if (!command || !tmp)
		return ;
	if (tmp->flags)
		free_flags(tmp->flags);
	if (tmp->path)
		tmp->path = NULL;
	if (tmp->cmd)
	{
		free(tmp->cmd);
		tmp->cmd = NULL;
	}
	free(tmp);
	tmp = NULL;
}

void	free_envir(t_envir *envir)
{
	t_envir	*tmp;

	if (!envir)
		return ;
	tmp = envir;
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


void	free_2darray(char **array)
{
	if (!array)
		return ;
	while (*array)
	{
		free(*array);
		array++;
	}
	free(array);
	array = NULL;
}