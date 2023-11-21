#include "minishell.h"

int handle_child_process_redout(t_data *data, t_tree *tree, int file_found)
{
	t_tree *current = tree->right;
	int fd;
	char *file_name;

	fd = -1;
	while (current && current->type != T_NEWLINE)
	{
		// printf("INSIDE handle_child_process_redout\n");
		file_name = ft_strdup(current->value);

		if (current->type == T_RED_OUT)
			fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (current->type == T_APPEND)
			fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);

		if (fd < 0)
		{
			data->exit_status = 1;
			perror(file_name);
			exit(1);
		}

		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			data->exit_status = 1;
			perror("minishell: dup2 error");
			close(fd);
			exit(1);
		}

		close(fd);

		current = current->right;
	}
	// printf("INSIDE handle_child_process_redout lower part of the function\n");
	// printf("XXXXXXXXXXXXXfile_name = %s\n", file_name);
	if (file_found == 1)
	{
		if (execute_word(data, tree))
		{
			exit(1);
			return 1;
		}
		else
		{
			exit(0);
			return 0;
		}
	}
	else
		return 0;
}

int handle_parent_process_redout(t_data *data, pid_t pid, int fd)
{
	// printf("EXECUTE redout PARENT\n");
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);

	if (fd != -1)
		close(fd);
	return (0);
}

int	execute_redout(t_data *data, t_tree *tree, int file_found)
{
	// printf("EXECUTE redout\n");
	int		fd;
	pid_t  pid;

	fd = -1;
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		// printf("EXECUTE redout entring CHILD\n");
		handle_child_process_redout(data, tree, file_found);
	}
	else
	{
		// printf("EXECUTE redout entring PARENT\n");
		handle_parent_process_redout(data, pid, fd);
	}
	if (fd != -1)
        close(fd);
	return (0);
}
