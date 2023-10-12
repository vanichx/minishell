/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:42:15 by ipetruni          #+#    #+#             */
/*   Updated: 2023/09/25 17:18:12 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	child_free(t_pipexbonus *ppxb)
{
	int	i;

	i = 0;
	while (ppxb->cmd_args[i])
	{
		free(ppxb->cmd_args[i]);
		i++;
	}
	free(ppxb->cmd_args);
	free(ppxb->cmd);
}

void	parent_free(t_pipexbonus *ppxb)
{
	int	i;

	i = 0;
	close(ppxb->infile);
	close(ppxb->outfile);
	if (ppxb->here_doc)
		unlink(".heredoc_tmp");
	while (ppxb->cmd_paths[i])
	{
		free(ppxb->cmd_paths[i]);
		i++;
	}
	free(ppxb->cmd_paths);
	free(ppxb->pipe);
}

void	pipe_free(t_pipexbonus *ppxb)
{
	close(ppxb->infile);
	close(ppxb->outfile);
	if (ppxb->here_doc)
		unlink(".heredoc_tmp");
	free(ppxb->pipe);
	msg(ERR_ENV);
	exit(1);
}
