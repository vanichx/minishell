#include "minishell.h"


void	lexical_analysis(t_data *data, char *input)
{
	t_token	*tmp;

	tmp = NULL;
	if (!input || !input[0])
		return ;
	if (!is_only_ascii(input))
	{
		ft_putstr_fd("minishell>> ", 2);
		ft_putstr_fd("invalid ascii characters found in string\n", 2);
		return ;
	}
	tokenise(data, input);
	set_token_types(data);
	clean_token_spaces(data);
	print_tokens(data);
	// evaluate_tokens(data);
	tmp = data->token_list;
	// while (tmp)
	// 	token_to_cmd(data, &tmp);
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


char	*find_executable_path(char **paths, char *cmd)
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