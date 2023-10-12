/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 09:53:15 by ipetruni          #+#    #+#             */
/*   Updated: 2023/09/25 17:39:58 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	create_pipes(t_pipexbonus *ppxb)
{
	int	i;

	i = 0;
	while (i < ppxb->cmd_nbrs - 1)
	{
		if (pipe(ppxb->pipe + 2 * i) < 0)
			parent_free(ppxb);
		i++;
	}
}

void	close_pipes(t_pipexbonus *ppxb)
{
	int	i;

	i = 0;
	while (i < (ppxb->pipe_nbrs))
	{
		close(ppxb->pipe[i]);
		i++;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipexbonus	ppxb;

	if (argc < arguments_check(argv[1], &ppxb))
		return (msg(ERR_INPUT));
	get_infile(argv, &ppxb);
	get_outfile(argv[argc - 1], &ppxb);
	ppxb.cmd_nbrs = argc - 3 - ppxb.here_doc;
	ppxb.pipe_nbrs = 2 * (ppxb.cmd_nbrs - 1);
	ppxb.pipe = (int *)malloc(sizeof(int) * ppxb.pipe_nbrs);
	if (!ppxb.pipe)
		msg_error(ERR_PIPE);
	ppxb.env_paths = find_path(env);
	ppxb.cmd_paths = ft_split(ppxb.env_paths, ':');
	if (!ppxb.cmd_paths)
		pipe_free(&ppxb);
	create_pipes(&ppxb);
	ppxb.idx = -1;
	while (++(ppxb.idx) < ppxb.cmd_nbrs)
		child(ppxb, argv, env);
	close_pipes(&ppxb);
	waitpid(-1, NULL, 0);
	parent_free(&ppxb);
	return (0);
}
