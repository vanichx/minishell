#include "../minishell.h"

int	main(void)

{
	char	*buf;

	buf = "minishell>> ";
	while (1)
	{
		readline(buf);
		if (!ft_strncmp("exit", readline(buf), ft_strlen("exit") + 1))
			exit(0);
	}
	// free(buf);
	return (0);
}
