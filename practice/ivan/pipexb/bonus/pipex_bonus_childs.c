/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_childs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:32:35 by ipetruni          #+#    #+#             */
/*   Updated: 2023/09/25 17:42:45 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static char	*get_command(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static void	sub_dup2(int zero, int one)
{
	dup2(zero, 0);
	dup2(one, 1);
}

void	child(t_pipexbonus p, char *argv[], char *env[])
{
	p.pid = fork();
	if (!p.pid)
	{
		if (p.idx == 0)
			sub_dup2(p.infile, p.pipe[1]);
		else if (p.idx == p.cmd_nbrs - 1)
			sub_dup2(p.pipe[2 * p.idx - 2], p.outfile);
		else
			sub_dup2(p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]);
		close_pipes(&p);
		p.cmd_args = ft_split(argv[2 + p.here_doc + p.idx], ' ');
		p.cmd = get_command(p.cmd_paths, p.cmd_args[0]);
		if (!p.cmd)
		{
			msg_pipe(p.cmd_args[0]);
			child_free(&p);
			exit(1);
		}
		execve(p.cmd, p.cmd_args, env);
	}
}
