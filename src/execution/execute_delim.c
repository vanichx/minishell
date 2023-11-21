#include "minishell.h"

int	execute_delim(t_data *data, t_tree *tree, char *delemiter)
{
	int		fd;
	char	*buf;
	pid_t	pid;
	//Variable for the signal
	int		status;
	

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		printf("minishell: %s\n", strerror(errno));
	while (1)
	{
		buf = readline("> ");
		//Somewhere her eshould be a check for ctrl + C
		printf("buf: :%s:\n", buf);
		printf("delemiter: :%s:\n", delemiter);
		if (!ft_strncmp(delemiter, buf, ft_strlen(delemiter) + 1))
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	if (buf)
		free(buf);
	close(fd);

	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		fd = open(".heredoc_tmp", O_RDONLY);
		if (fd < 0)
		{
			printf("minishell: %s\n", strerror(errno));
			exit(1);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			printf("minishell: %s\n", strerror(errno));
			exit(1);
		}
		close(fd);
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
	unlink(".heredoc_tmp");
	return (0);
}