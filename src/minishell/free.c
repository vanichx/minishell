#include "minishell.h"

void	free_data(t_data *data)
{
	ft_cmdclear(&data->cmd_list);
	free_2darray(data->env_array);
	if (data->curr_dir && data->curr_dir[0] != '\0')
		free(data->curr_dir);
	free(data);
	data = NULL;
}


void	free_cmdexe(void *command)
{
	t_cmdexe *tmp;

	tmp = (t_cmdexe *)command;
	if (!command || !tmp)
		return ;
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
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}