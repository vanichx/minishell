/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:40:22 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/13 14:12:56 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_word(t_data *data, t_tree *tree, char *envp[])
{
	if (is_builtin(tree->args_array[0]))
	{
		if (execute_builtin(data, tree))
			return (1);
	}
	else
	{
		if (execute_command(data, tree, envp))
			return (1);		
	}
	return (0);
}

int execute_command(t_data *data, t_tree *tree, char *envp[])
{
	char	*exec_path;
	pid_t	pid;
	int		status;
	
	exec_path = find_executable_path(data->path, tree->args_array[0]);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	else if (pid == 0)
	{
		if (execve(exec_path, tree->args_array, envp) == -1)
			return (printf("minishell: %s: command not found\n", tree->args_array[0]), 1);
	}
	else
		waitpid(pid, &status, 0);
	free(exec_path);
	return (0);
}