/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:26:05 by ipetruni          #+#    #+#             */
/*   Updated: 2023/09/26 13:27:21 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	get_infile(char **argv, t_pipexbonus *ppxb)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
		here_doc(argv[2], ppxb);
	else
	{
		ppxb->infile = open(argv[1], O_RDONLY);
		if (ppxb->infile < 0)
			msg_error(ERR_INFILE);
	}
}

void	get_outfile(char *argv, t_pipexbonus *ppxb)
{
	if (ppxb->here_doc)
		ppxb->outfile = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		ppxb->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (ppxb->outfile < 0)
		msg_error(ERR_OUTFILE);
}
