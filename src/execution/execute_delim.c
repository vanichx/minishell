#include "minishell.h"

int	execute_delim(char *delemiter)
{
	int		fd;
	char	*buf;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		printf("minishell: %s\n", strerror(errno));
	while (1)
	{
		buf = readline("> ");
		if (!buf || !ft_strncmp(delemiter, buf, ft_strlen(delemiter) + 1))
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	free(buf);
	close(fd);
	unlink(".heredoc_tmp");
	return (0);
}