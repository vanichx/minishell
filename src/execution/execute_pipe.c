/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:11:25 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/25 12:04:37 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	create_pipe_child(t_pipe_info *args)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		close (args->pipe_fd[args->end]);
		dup2(args->pipe_fd[1 - args->end], args->std_fd);
		close(args->pipe_fd[1 - args->end]);
		if (evaluate_execution(args->data, args->tree) == -1)
			exit(127);
		exit(0);
	}
	return (pid);
}

static pid_t	create_and_check_child(t_pipe_info *args)
{
	pid_t	pid;

	pid = create_pipe_child(args);
	if (pid < 0)
	{
		printf("minishell: fork error\n");
		exit(-1);
	}
	return (pid);
}

static void	wait_for_child(pid_t pid, int *status)
{
	child_pid = pid;
	waitpid(pid, status, 0);
	child_pid = 0;
}

int	execute_pipe(t_data *data, t_tree *tree)
{
	int				pipe_fd[2];
	pid_t			pid[2];
	int				status;
	t_pipe_info		args;

	create_pipe_and_check(pipe_fd);
	args.pipe_fd = pipe_fd;
	args.data = data;
	args.tree = tree->left;
	args.end = 0;
	args.std_fd = STDOUT_FILENO;
	pid[0] = create_and_check_child(&args);
	args.tree = tree->right;
	args.end = 1;
	args.std_fd = STDIN_FILENO;
	pid[1] = create_and_check_child(&args);
	close_pipe(pipe_fd);
	wait_for_child(pid[0], &status);
	wait_for_child(pid[1], &status);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	return (0);
}
