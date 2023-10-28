#include "minishell.h"

void	handle_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_c;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	rl_catch_signals = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
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
	if (signo == SIGTSTP || signo == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}

}

void	handle_d(t_data *data)
{
	rl_on_new_line();
	rl_redisplay();
	exit_shell("exit", 0, data);
}
