/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:34:12 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/25 10:01:27 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		if (isatty(STDIN_FILENO))
		{
			write(1, "\n", 1);
			if (child_pid == 42)
				child_pid = 44;
			if (child_pid != 0 && child_pid != 44)
			{
				kill(child_pid, SIGINT);
				child_pid++;
			}
			else
			{
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
			}
		}
		else
			exit(EXIT_SUCCESS);
	}
}

void	handle_sigtstp_sigquit(int signo)
{
	if (signo == SIGTSTP || signo == SIGQUIT)
	{
		if (isatty(STDIN_FILENO))
		{
			if (child_pid == 0)
			{
				rl_replace_line("", 0);
				rl_redisplay();	
			}
			else
			{
				kill(child_pid, signo);
				child_pid += 2;
			}
		}
	}
}

void	handle_c(int signo)
{
	handle_sigint(signo);
	handle_sigtstp_sigquit(signo);
}

int	handle_d(t_data *data, char *line)
{
	if (line == NULL)
	{
		rl_on_new_line();
		rl_redisplay();
		exit_shell("exit", 0, data);
	}
	if (ft_strlen(line) == 0)
	{
		ft_strdel(&line);
		return (1);
	}
	return (0);
}
