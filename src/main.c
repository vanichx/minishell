#include "../minishell.h"

void handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\nminishell>> ", 13);
	}
}

typdef struct data {
	int *signals;
	char *buf;
}

int	main(void)
{
	char	*buf;
	struct sigaction sa;
	sa.sa_handler = handle_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT, &sa, NULL);

	buf = "minishell>> ";
	while (1)
	{
		char *promt;
		promt = readline(buf);
		if (!ft_strncmp("exit", promt, ft_strlen("exit") + 1))
			exit(0);
	}
	free(buf);
	return (0);
}
