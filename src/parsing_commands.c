#include "../minishell.h"

void    parse_commands(t_data *data, char *input)
{
    char **command;

    data->pipex.cmd_nbrs = 0;
    command = ft_split(input, ' ');
    if (command == NULL)
    {
        free (command);
        return ;
    }
    data->commands = command;
    int i = 0;
    while (data->commands[i])
    {
        data->pipex.cmd_nbrs++;
        i++;
    }
}

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

int        execute_command(t_data *data)
{
    data->pipex.path = find_path(data->env->env_vars);
    data->pipex.cmd_paths = ft_split(data->pipex.path, ':');
    data->pipex.idx = -1;
    while (++data->pipex.idx < data->pipex.cmd_nbrs)
        child(data);
    waitpid(-1, NULL, 0);
    return (0);
}

void	child(t_data *data)
{
    int i = 0;
    // int j = 0;
	data->pid = fork();
    // while (data->pipex.cmd_args[j])
    // {
    //     printf("%s\n", data->pipex.cmd_args[j]);
    //     j++;
    // }
	if (!data->pid)
	{
        while (data->commands[i])
        {
	        data->pipex.cmd = apply_command(data->pipex.cmd_paths, data->commands[i]);
		    execve(data->pipex.cmd, data->commands, data->pipex.cmd_paths);
            printf("%s\n", data->pipex.path);
            i++;
        }
       
	}
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
