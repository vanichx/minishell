#include "minishell.h"

int handle_child_process(t_data *data, t_tree *tree)
{
	int fd = -1;
	char *file_name;
	t_tree *current = tree->right;

	while (current && current->type != T_NEWLINE) 
	{
		if(current->type == T_RED_OUT)
		{
			file_name = ft_strdup(current->value);
			if((fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
			{
				printf("minishell: %s: %s\n", file_name, strerror(errno));
				exit(1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1) 
			{
				printf("minishell: dup2 error\n");
				exit(-1);
			}
			
		}
		current = current->right;
	}

	if (execute_word(data, tree))
	{
		close(fd);
		exit(1);
		return(1);
	}
	else
	{
		close(fd);
		exit(0);
		return(0);
	}
}

int handle_parent_process(t_data *data, pid_t pid, int fd)
{
	printf("EXECUTE REDOUT PARENT\n");
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);

	if (fd != -1)
		close(fd);
	return (0);
}

int	execute_redout(t_data *data, t_tree *tree)
{
	printf("EXECUTE REDOUT\n");
	int		fd;
	pid_t  pid;

	fd = -1;
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
		handle_child_process(data, tree);
	else
		handle_parent_process(data, pid, fd);
	return (0);
}
