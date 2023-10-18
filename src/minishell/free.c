#include "minishell.h"

void	free_data(t_data *data)
{
    if (!data)
        return ;
	while (data->env)
	{
   		free_envir((t_envir *)data->env);
		data->env = data->env->next;
	}
    free(data->promt);
    free_flags(data->flags);
    free_2darray(data->commands);
    free_cmdexe(data->cmdexe);
    free(data);
}

void	free_flags(t_flags *flags)
{
    if (!flags)
        return ;
    free(flags->delimiter.content);
    free(flags);
}

void	free_envir(t_envir *env)
{
    int	i;

    if (!env)
        return ;
    i = 0;
    while (env[i].var_name)
    {
        free(env[i].var_name);
        free(env[i].var_value);
        i++;
    }
    free(env);
}

void	free_cmdexe(t_cmdexe *cmdexe)
{
    if (!cmdexe)
        return ;
    free(cmdexe->path);
    free_2darray(cmdexe->cmd_paths);
    free_2darray(cmdexe->cmd_args);
    free(cmdexe->cmd);
    free(cmdexe);
}

void	free_2darray(char **array)
{
	int	i;

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