#include "../minishell.h"

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
}

void	free_cmdexe(t_cmdexe *cmdexe)
{
	int	i;

	i = -1;
	if (cmdexe)
	{
		free(cmdexe->path);
		if (cmdexe->cmd_paths)
			while (cmdexe->cmd_paths[++i])
				free(cmdexe->cmd_paths[i]);
		free(cmdexe->cmd_paths);
		i = -1;
		if (cmdexe->cmd_args)
			while (cmdexe->cmd_args[++i])
				free(cmdexe->cmd_args[i]);
		free(cmdexe->cmd_args);
		free(cmdexe->cmd);
		free(cmdexe);
	}
}
