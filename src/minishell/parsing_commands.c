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
		// else
		// {
		// 	free_data(data);
		// 	perror("command not found");
		// }
		// data->commands = data->commands->next;
		else
			child(data->commands);
	}
	if (data->curr_dir)
		free(data->curr_dir);
    return ;
}

void	child(t_cmdexe *cmdexe)
{
    pid_t pid = fork();
    if (!pid)
    {
        while (cmdexe)
        {
			printf("%s\n", cmdexe->cmd);
            execve(NULL, &cmdexe->cmd, &cmdexe->path);
            printf("%s\n", cmdexe->path);
			cmdexe = cmdexe->next;
        }
    }
    else
        wait(NULL);
}

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
