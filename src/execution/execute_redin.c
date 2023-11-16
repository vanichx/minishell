#include "minishell.h"

int	execute_redin(t_data *data, t_tree *tree)
{
	int		fd;
	pid_t	pid;
	int		status;
	char	*file_name;
	t_tree	*current;

	fd = -1;
	current = tree;
	while (current->right && current->right->type == T_RED_INP)
		current = current->right;
	if (current->right && current->right->args_array)
		file_name = current->right->args_array[0];
	else
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		if((fd = open(file_name, O_RDONLY)) < 0)
		{
			printf("minishell: %s: %s\n", file_name, strerror(errno));
			exit(1);
		}
		if (dup2(fd, STDIN_FILENO) != STDIN_FILENO) 
		{
			printf("minishell: dup2 error\n");
			exit(-1);
		}
		if (tree->right->type == T_RED_OUT)
			execute_redout(data, tree->right);
		if (tree->right->type == T_PIPE)
			execute_pipe(data, tree->right);
		else
			execute_word(data, tree->left);
		close(fd);
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
	if (fd != -1)
		close(fd);
	return (0);
}