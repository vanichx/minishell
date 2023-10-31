#include "minishell.h"

void	parse_command(t_data *data)
{
	if (data->token_list == NULL)
		return ;
	data->cmd_list = ft_cmdnew(data->token_list->word);
	cmd_array_init(data, data->cmd_list);
	data->cmd_list = cmd_array_fill(data, data->cmd_list);
	data->cmd_list->path = find_command_path(data);
	while (data->cmd_list != NULL)
	{
		if (data->cmd_list == 2)
			handle_builtins(data);
		else
			child(data);
		data->cmd_list = data->cmd_list->next;
	}
	if (data->curr_dir)
		free(data->curr_dir);
	return ;
}

char	*find_command_path(t_data *data)
{
	char	*path;
	char	*command_path;
	int	i;

	i = 0;
	path = find_envir_variable(data, "PATH=", 5);
	if (!path)
		return (NULL);
	data->path = ft_split(path, ':');
	if (!data->path)
		return (NULL);
	command_path = find_executable_path(data->path, data->cmd_list->cmd);
	if (!command_path)
	{
		printf("minishell: %s: command not found\n", data->cmd_list->cmd);
		return (0);
	}
	printf("Executable_path: %s\n", command_path);
	// if (paths)
		// free_2darray(paths);
	return (command_path);
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



void	child(t_data *data)
{
    data->pid = fork();
    if (!data->pid)
    {
		if (execve(data->cmd_list->path, data->cmd_list->args_array, data->path) == -1)
			{
				perror("execve");
				exit(1);
			}
    }
	else
		wait(NULL);
}



void	print_cmdexe(void *cmdexe_node)
{
    t_cmdexe	*cmdexe = (t_cmdexe *)cmdexe_node;

    printf("path: %s\n cmd: %s\n", cmdexe->path, cmdexe->cmd);
}

void   add_cmd(t_cmdexe **head, t_cmdexe *new)
{
	printf("add_cmd\n");//Debug
	t_cmdexe *tmp;

	if (!new || !head)
		return ;
	new->cmd = trim_newlines(new->cmd);
	if (*head)
	{
		tmp = *head;
		while (tmp->next)
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
		*head = new;
}

// void	clear_cmd_list(t_cmdexe **cmd, void (*del)(void*))
// {
// 	t_cmdexe	*tmp;
// 	t_cmdexe	*tmp2;
// 	t_token		*args;
// 	t_token		*args2;

// 	if (!cmd || !del)
// 		return ;
// 	tmp = *cmd;
// 	while (tmp)
// 	{
// 		clear_cmd(tmp);
// 		args = tmp->args;
// 		while (args)
// 		{
// 			ft_strdel(&args->word);
// 			args2 = args->next;
// 			del(args);
// 			args = args2;
// 		}
// 		tmp2 = tmp->next;
// 		free(tmp);
// 		tmp = tmp2;
// 	}
// 	*cmd = NULL;
// }

void	clear_cmd(t_cmdexe *cmd)
{
	// ft_strdel(&cmd->cmd);
	// ft_strdel(&cmd->path);
	free_2darray(cmd->args_array);
	// ft_lstclear(&cmd->env_list, free);
}