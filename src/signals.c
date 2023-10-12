#include "../minishell.h"

void	handle_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_c;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	rl_catch_signals = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}

void	handle_c(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_d(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(1, "exit\n", 5);
	exit(0);
}
