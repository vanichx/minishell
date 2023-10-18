#include "minishell.h"

void	parse_commands(t_data *data, char *input)
{
	char	**command;
	int		i;

	i = 0;
	data->cmdexe->cmd_nbrs = 0;
	command = ft_split(input, ' ');
	if (command == NULL)
	{
		free (command);
		return ;
	}
	data->commands = command;
	while (data->commands[i])
	{
		data->cmdexe->cmd_nbrs++;
		i++;
	}
}

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

int		execute_command(t_data *data)
{
	data->cmdexe->path = find_path(data->env->env_vars);
	data->cmdexe->cmd_paths = ft_split(data->cmdexe->path, ':');
	data->cmdexe->idx = -1;
	while (++data->cmdexe->idx < data->cmdexe->cmd_nbrs)
		child(data);
	waitpid(-1, NULL, 0);
	return (0);
}

void	child(t_data *data)
{
	int i = 0;
	// int j = 0;
	data->pid = fork();
	// while (data->cmdexe->cmd_args[j])
	// {
	//	 printf("%s\n", data->cmdexe->cmd_args[j]);
	//	 j++;
	// }
	if (!data->pid)
	{
		while (data->commands[i])
		{
			data->cmdexe->cmd = apply_command(data->cmdexe->cmd_paths, data->commands[i]);
			execve(data->cmdexe->cmd, data->commands, data->cmdexe->cmd_paths);
			// printf("%s\n", data->cmdexe.path);
			i++;
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
