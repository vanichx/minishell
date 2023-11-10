/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:41:02 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/10 19:13:33 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_pipe(t_data *data, t_tree *tree)
{
	int pipefd[2];
	pid_t pid;

	if (pipe(pipefd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDOUT_FILENO);
		close(pipefd[0]);
		execute_word(data, tree->left);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDIN_FILENO);
		close(pipefd[1]);
		execute_word(data, tree->right);
		waitpid(pid, NULL, 0);
	}
	return (0);
}

// int execute_red_inp(t_data *data, t_tree *tree)
// {
	
// }

// int execute_red_out(t_data *data, t_tree *tree)
// {
	
// }

// int execute_append(t_data *data, t_tree *tree)
// {
	
// }

// int execute_delim(t_data *data, t_tree *tree)
// {
	
// }
