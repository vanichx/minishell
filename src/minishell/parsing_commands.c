#include "minishell.h"

void	parse_commands(t_data *data, char *input)
{
	t_cmdexe	*comm;
	char	**command;
	int		i;

	if (!input || !input[0])
		return ;
	command = ft_split(input, ' ');
	i = 0;
	if (!command)
		return ;
	while (command[i])
	{
		comm = malloc(sizeof(t_cmdexe));
		if (!comm)
		{
			free_cmdexe(comm);
			exit(1);
		}
		comm->cmd = command[i];
		comm->path = find_path(data->env);
		comm->idx = i;
		data->cmd_nbrs = comm->idx + 1;
		comm->flags = init_flags();
		// parse_flags(data, *command);
		ft_cmdadd_back(&data->commands, comm);
		i++;
	}
	// if (command)
	// 	free_2darray(command);
}

char	*find_path(t_envir *env)
{
    while (env)
    {
        if (ft_strcmp(env->var_name, "PATH") == 0)
            return (env->var_value);
        env = env->next;
    }
    return (NULL);
}

void	execute_command(t_data *data)
{
	if (data->commands == NULL)
		return ;
	while (data->commands->next)
	{
		if (ft_is_builtin(data->commands->cmd))
			handle_builtins(data);
		else
		{
			free_data(data);
			perror("command not found");
		}
		data->commands = data->commands->next;
		// else
			// exit(0);
			//child(data);
	}
	if (data->curr_dir)
		free(data->curr_dir);
    return ;
}

// void	child(t_cmdexe *cmdexe)
// {
//     int i = 0;
//     int j = 0;
//     pid_t pid = fork();
//     while (cmdexe->cmd_args[j])
//     {
//          printf("%s\n", cmdexe->cmd_args[j]);
//          j++;
//     }
//     if (!pid)
//     {
//         while (cmdexe->path[i])
//         {
//             cmdexe->cmd = apply_command(cmdexe->cmd_path, cmdexe->cmd_args[0]);
//             execve(cmdexe->cmd, cmdexe->cmd_args, cmdexe->cmd_paths);
//             printf("%s\n", cmdexe->path);
//             i++;
//         }
//     }
//     else
//         wait(NULL);
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
