#include "minishell.h"

void	free_data(t_data *data)
{
	if (data->flags)
		free(data->flags);
	if (data->env)
		free_envir(data->env);  // Free the environment variables
	if (data->cmdexe)
		free_cmdexe(data->cmdexe);
	free(data);
}


void	free_envir(t_envir *env)
{
	int i;

	i = 0;
	while (i < env->count)
	{
		free(env->env_vars[i]);
		env->env_vars[i] = NULL; // Set the pointer to NULL after freeing
		i++;
	}
	env->count = 0;
	free(env); // Free the memory allocated for env itself
	env = NULL; // Set the pointer to NULL after freeing
}

void	free_cmdexe(t_cmdexe *cmdexe)
{
    int	i;

    if (cmdexe)
    {
        cmdexe->path = NULL;
        if (cmdexe->cmd_paths)
        {
            i = 0;
            while (cmdexe->cmd_paths[i])
            {
                free(cmdexe->cmd_paths[i]);
                cmdexe->cmd_paths[i] = NULL;
                i++;
            }
            free(cmdexe->cmd_paths);
            cmdexe->cmd_paths = NULL;
        }
        if (cmdexe->cmd_args)
        {
            i = 0;
            while (cmdexe->cmd_args[i])
            {
                free(cmdexe->cmd_args[i]);
                cmdexe->cmd_args[i] = NULL;
                i++;
            }
            free(cmdexe->cmd_args);
            cmdexe->cmd_args = NULL;
        }
        cmdexe->cmd = NULL;
        free(cmdexe);
        cmdexe = NULL;
    }
}