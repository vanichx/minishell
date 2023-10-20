#include "minishell.h"

void	parse_commands(t_data *data, char *input)
{
	t_cmdexe	*comm;
	char	**command;
	int		i;

	if (!input || !input[0])
		return ;
	command = ft_split(input, ' ');
	i = 1;
	if (!command)
	{
		free_2darray(command);
		return ;
	}
	while (*command)
	{
		comm = (t_cmdexe *)malloc(sizeof(t_cmdexe));
		if (!comm)
		{
			free_command(comm);
			return ;
		}
		comm->cmd = *command;
		comm->path = find_path(data->env);
		comm->idx = i;
		comm->flags = init_flags();
		// parse_flags(data, *command);
		ft_lstadd_back_cmd(&data->commands, comm);
		command++;
		i++;
	}
}

char	*find_path(t_list *env)
{
    t_envir	*envir;

    while (env)
    {
        envir = (t_envir *)env->content;
        if (ft_strcmp(envir->var_name, "PATH") == 0)
            return (envir->var_value);
        env = env->next;
    }
    return (NULL);
}

int		execute_command(t_data *data)
{
	if (data->commands == NULL)
		return (0);
	// else if (ft_is_builtin(data->commands[0]))
	handle_builtins(data);
    // data->cmdexe->path = find_path(data->env);
    // data->cmdexe->cmd_paths = ft_split(data->cmdexe->path, ':');
    // data->cmdexe->idx = -1;
    // while (++data->cmdexe->idx < data->cmdexe->cmd_nbrs)
    //     child(data);
    // waitpid(-1, NULL, 0);
	// free_data(data);
    return (0);
}

// void	child(t_data *data)
// {
// 	int i = 0;
// 	// int j = 0;
// 	data->pid = fork();
// 	// while (data->cmdexe->cmd_args[j])
// 	// {
// 	//	 printf("%s\n", data->cmdexe->cmd_args[j]);
// 	//	 j++;
// 	// }
// 	if (!data->pid)
// 	{
// 		while (data->commands[i])
// 		{
// 			data->cmdexe->cmd = apply_command(data->cmdexe->cmd_paths, data->commands[i]);
// 			execve(data->cmdexe->cmd, data->commands, data->cmdexe->cmd_paths);
// 			// printf("%s\n", data->cmdexe.path);
// 			i++;
// 		}
// 	}
// 	else
// 		wait(NULL);
// }

char	*apply_command(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}
