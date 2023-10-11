#include "../minishell.h"

int	main(void)

{
	char	*buf;
	t_minsh	minish;

	buf = "minishell>> ";
	while (1)
	{
		readline(buf);
		if (!ft_strncmp("exit", buf, ft_strlen("exit") + 1))
			break ;
	}
	free(buf);
	minish.infile = open(".minishell_tmp", O_RDONLY);
	if (minish.infile < 0)
	{
		unlink(".minishell_tmp");
		perror(ERR_MINISHELL);
	}
	return (0);
}
