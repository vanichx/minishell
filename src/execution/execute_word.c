/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:40:22 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/14 13:05:11 by eseferi          ###   ########.fr       */
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
        printf("minishell: %s: command not found\n", tree->args_array[0]);
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
		return 1;
	}
	else if (pid == 0)
	{
		if (execve(exec_path, tree->args_array, envp) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		{
			data->exit_status = 1;
			exit_shell("Error from execve\n", 1, data);
		}
	}
	return 0;
}