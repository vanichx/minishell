#include "minishell.h"

static char	*find_executable_path(char **paths, char *cmd)
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
void	parse_commands(t_data *data, char *input)
{
	int			i;

	i = 0;
	if (!input || !input[0])
		return ;
	data->cmd_array = ft_split(input, ' ');
	if (!data->cmd_array)
		return ;
	while (data->cmd_array[i])
	{
		if (!data->cmd_list)
		{
			data->cmd_list = ft_cmdnew(data->cmd_array[i]);
			data->cmd_list->path = find_path(data);
		}
		else if (data->cmd_list)
		{
			ft_cmdadd_back(&data->cmd_list, ft_cmdnew(data->cmd_array[i]));
			data->cmd_list->path = find_path(data);
		}
		i++;
	}
	// if (data->cmd_array)
	// 	free_2darray(data->cmd_array);
}

char	*find_path(t_data *data)
{
	char	*path;
	char	*command;
	int	i;

	i = 0;
	path = find_envir_variable(data, "PATH=", 5);
	if (!path)
		return (NULL);
	data->path = ft_split(path, ':');
	if (!data->path)
		return (NULL);
	command = find_executable_path(data->path, data->cmd_list->cmd);
	// if (paths)
	// 	free_2darray(paths);
	return (command);
}

char	*find_envir_variable(t_data *data, char *var_name, int len)
{
	int i = 0;

	while (data->env_array[i])
	{
		if (ft_strncmp(data->env_array[i], var_name, len) == 0)
			return (data->env_array[i] + len);
		i++;
	}
	return (NULL);
}

void	execute_command(t_data *data)
{
	t_cmdexe *cmd_list;

	cmd_list = data->cmd_list;
	if (cmd_list == NULL)
		return ;
	while (cmd_list != NULL)
	{
		if (cmd_list == 2)
			handle_builtins(data);
		else
			child(data);
		cmd_list = cmd_list->next;
	}
	if (data->curr_dir)
		free(data->curr_dir);
    return ;
}

void	child(t_data *data)
{
    data->pid = fork();
    if (!data->pid)
    {
		if (execve(data->cmd_list->path, data->cmd_array, data->path) == -1)
			{
				perror("execve");
				exit(1);
			}
    }
	else
		wait(NULL);
}
