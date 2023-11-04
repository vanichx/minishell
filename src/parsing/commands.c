/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:55:53 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/04 20:58:04 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	find_command_path(t_data *data, t_tree *tree)
// {
// 	char	*path;
// 	char	*command_path;
// 	int	i;

// 	i = 0;
// 	path = find_envir_variable(data, "PATH=", 5);
// 	if (!path)
// 		return (1);
// 	data->path = ft_split(path, ':');
// 	if (!data->path)
// 		return (1);
// 	command_path = find_executable_path(data->path, data->tree->args_array[0]);
// 	if (!command_path)
// 	{
// 		printf("minishell: %s: command not found\n", data->tree->args_array[0]);
// 		return (1);
// 	}
// 	printf("Executable_path: %s\n", command_path);
// 	// cmd->path = ft_strdup(command_path);
// 	// if (paths)
// 		// free_2darray(paths);
// 	return (0);
// }
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
	int	i;

	i = 0;
	while (data->env_array[i])
	{
		if (ft_strncmp(data->env_array[i], var_name, len) == 0)
			return (data->env_array[i] + len);
		i++;
	}
	return (NULL);
}
// void	handle_builtins(t_data *data)
// {
// 	// while (data->cmd_list->next != NULL)
// 	// {
// 	// 	printf("%s\n", data->cmd_list->cmd);
// 	// 	data->cmd_list = data->cmd_list->next;
// 	// }
// 	// if (ft_strcmp(data->commands->(), "echo") == 0)
// 	// 	builtin_echo(data->cmdexe->cmd_args);
// 	// else if (ft_strcmp(data->cmdexe->cmd, "cd") == 0)
// 	// 	builtin_cd(data, data->cmdexe->cmd_args[1]);
// 	// else if (ft_strcmp(data->cmdexe->cmd, "pwd") == 0)
// 	// // 	builtin_pwd();
// 	// else if (ft_strcmp(data->cmdexe->cmd, "unset") == 0)
// 	// 	builtin_unset(&data->env, data->cmdexe->cmd_args[1]);
// 	// else if (ft_strcmp(data->cmdexe->cmd, "env") == 0)
// 	// // 	builtin_env(data->env);
// 	// else if (ft_strcmp(data->cmdexe->cmd, "exit") == 0)
// 	// // 	builtin_exit(data);
// 	// else if (ft_strcmp(data->cmdexe->cmd, "export") == 0)
// 	// 	builtin_export(data->env, ); // continue
// }
// void	child(t_data *data)
// {
//     data->pid = fork();
//     if (!data->pid)
//     {
// 		if (execve(data->cmd_list->path, data->cmd_list->args_array,
//		data->path) == -1)
// 			{
// 				perror("execve");
// 				exit(1);
// 			}
//     }
// 	else
// 		wait(NULL);
// }
