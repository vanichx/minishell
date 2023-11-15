#include "minishell.h"

int	execute_redin(t_data *data, t_tree *tree, char *envp[])
{
	int		fd;
	pid_t	pid;
	int		status;
	char	*file_name;

	fd = -1;
	file_name = tree->right->args_array[0];
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
		execute_word(data, tree->left, envp);
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