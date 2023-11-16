/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:40:22 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/16 13:15:12 by ipetruni         ###   ########.fr       */
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
    char *exec_path;

    exec_path = find_executable_path(data->path, tree->args_array[0]);
    if (exec_path == NULL)
    {
		ft_putstr_fd("minishell: ", 0);
		ft_putstr_fd(tree->args_array[0], 0);
		ft_putstr_fd(": command not found\n", 0);
        data->exit_status = 127;
        return 1;
    }
    return (fork_command(data, tree, exec_path, envp));
}

int	fork_command(t_data *data, t_tree *tree, char *exec_path, char *envp[])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (ft_strdel(&exec_path), 1);
	}
	else if (pid == 0)
	{
		if (execve(exec_path, tree->args_array, envp) == -1)
		{
			ft_strdel(&exec_path);
			exit(EXIT_FAILURE);
		}
		if (exec_path)
			ft_strdel(&exec_path);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		{
			data->exit_status = 1;
			ft_strdel(&exec_path);
		}
		else
			ft_strdel(&exec_path);
	}
	return 0;
}