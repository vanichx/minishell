#include "minishell.h"

int	execute_pipe(t_data *data, t_tree *tree, char *envp[])
{
	int		pipe_fd[2];
	pid_t	pid1, pid2;
	int		status;

	if (pipe(pipe_fd) == -1)
	{
		printf("minishell: pipe error\n");
		return (-1);
	}
	pid1 = fork();
	if (pid1 < 0)
		return (-1);
	else if (pid1 == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		if (evaluate_execution(data, tree->left, envp) == -1)
			exit(127);
		exit(0);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (-1);
	else if (pid2 == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		if (evaluate_execution(data, tree->right, envp) == -1)
			exit(127);
		exit(0);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	return (0);
}