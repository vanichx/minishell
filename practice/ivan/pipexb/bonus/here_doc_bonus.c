/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:51:33 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 14:52:16 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	arguments_check(char *args, t_pipexbonus *ppxb)
{
	if (args && !ft_strncmp("here_doc", args, 9))
	{
		ppxb->here_doc = 1;
		return (6);
	}
	else
	{
		ppxb->here_doc = 0;
		return (5);
	}
}

void	here_doc(char *delemiter, t_pipexbonus *ppxb)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		msg_error(ERR_HEREDOC);
	while (1)
	{
		write(1, "minishell> ", 12);
		if (get_next_line(0, &buf) < 0)
			exit(1);
		if (!ft_strncmp(delemiter, buf, ft_strlen(delemiter) + 1))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	ppxb->infile = open(".heredoc_tmp", O_RDONLY);
	if (ppxb->infile < 0)
	{
		unlink(".heredoc_tmp");
		msg_error(ERR_HEREDOC);
	}
}
