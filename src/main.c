#include "../minishell.h"

int main()

{
	int		file;
	char	*buf;
	t_minsh minish;

	file = open(".minishell_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		perror(ERR_MINISHELL);
	while (1)
	{
		write(1, "minishell> ", 12);
		if (get_next_line(0, &buf) < 0)
			exit(1);
		if (!ft_strncmp("exit", buf, ft_strlen("exit") + 1))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	minish.infile = open(".minishell_tmp", O_RDONLY);
	if (minish.infile < 0)
	{
		unlink(".minishell_tmp");
		perror(ERR_MINISHELL);
	}
    return (0);
}
