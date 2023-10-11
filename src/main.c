#include "../minishell.h"

int main()

{
	int		file;
	char	*buf;
	t_minsh minish;

	buf = "minishell>> ";
	while (1)
	{
		write(1, "minishell> ", 12);
		if (readline(&buf) < 0)
			exit(1);
		if (!ft_strncmp("exit", buf, ft_strlen("exit") + 1))
			break ;
	}
	free(buf);
	return (0);
}
