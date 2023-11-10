/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:06:51 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/10 16:09:47 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_data *data)
{
	if (evaluate_execution(data, data->tree))
		return (1);
	if (execute(data))
		return (1);
	if (execute(data))
		return (1);
	data->exit_status = 0;
	return (data->exit_status);
}

int evaluate_execution(t_data *data, t_tree *tree)
{
	//  based on what is the root node

	// COMMENTED FOR THE MOMENT XXXXXXXXXXXXXXXXXXX
	
	// if (is_logic_root(tree))
	// 	if (execute_logic(data, tree))
	// 	return (1);

	// COMMENTED FOR THE MOMENT XXXXXXXXXXXXXXXXXXX

	
	if (is_special_root(tree))
		if (execute_special(data, tree))
			return (1);
	if (is_word_root(tree))
		if (execute_word(data, tree))
		return (1);
	return (0);
}

// int	execute_logic(t_data *data, t_tree *tree)
// {
// 	// if (tree->type == T_AND)
// 	// 	if (execute_and(data, tree))
// 	// 		return (1);
// 	// if (tree->type == T_OR)
// 	// 	if (execute_or(data, tree))
// 	// 		return (1);
// 	return (0);
// }

int execute_special(t_data *data, t_tree *tree)
{
	if (tree->type == T_PIPE)
		if (execute_pipe(data, tree))
			return (1);
	// if (tree->type == T_RED_INP || tree->type == T_THREE_IN)
	// 	if (execute_red_inp(data, tree))
	// 		return (1);
	// if (tree->type == T_RED_OUT)
	// 	if (execute_red_out(data, tree))
	// 		return (1);
	// if (tree->type == T_APPEND)
	// 	if (execute_append(data, tree))
	// 		return (1);
	// if (tree->type == T_DELIM)
	// 	if (execute_delim(data, tree))
	// 		return (1);
	return (0);
}

// int	execute_command(t_data *data, t_tree *tree)
// {
	// pid_t	pid;
	// int		status;

	// pid = fork();
	// if (pid == -1)
	// 	return (1);
	// if (pid == 0)
	// {
	// 	if (execve(tree->args_array[0], tree->args_array, data->envp) == -1)
	// 	{
	// 		printf("minishell: %s: %s\n", tree->args_array[0], strerror(errno));
	// 		exit(1);
	// 	}
	// }
	// else
	// {
	// 	waitpid(pid, &status, 0);
	// 	if (WIFEXITED(status))
	// 		data->exit_status = WEXITSTATUS(status);
	// }
	// return (0);
// }
