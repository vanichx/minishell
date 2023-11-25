/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_delim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 02:29:39 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/25 18:29:30 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_temp_filename(t_heredoc_info *info)
{
	char	*counter_str;
	char	*temp_filename;

	counter_str = ft_itoa(info->heredoc_count);
	temp_filename = ft_strjoin(info->filename, counter_str);
	free(counter_str);
	return (temp_filename);
}

int	process_heredoc(t_heredoc_info *info, t_data *data)
{
	int		fd;
	char	*buf;

	info->filename = create_temp_filename(info);
	fd = open(info->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (printf("minishell: %s\n", strerror(errno)), 1);
	add_heredoc_file(data, info->filename, fd);
	g_child_pid = 42;
	while (1)
	{
		buf = readline("> ");
		if (!buf || !ft_strcmp(info->limiter, buf) || g_child_pid == 44)
			return (g_child_pid = 0, free(buf), close(fd), 0);
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	if (buf)
		free(buf);
	info->heredoc_count++;
	return (g_child_pid = 0, close (fd), 0);
}

int	execute_delim(t_token **head, t_data *data)
{
	t_heredoc_info	info;
	t_token			*current;

	info.heredoc_count = 0;
	current = *head;
	while (current && current->type != T_NEWLINE)
	{
		if (current->type == T_DELIM)
		{
			if (current->next->type == T_SPACE)
				info.filename = current->next->next->word;
			else
				info.filename = current->next->word;
			info.limiter = info.filename;
			if (process_heredoc(&info, data))
				return (ft_strdel(&info.filename), 1);
			if (current->next->type == T_SPACE)
				current->next->next->word = ft_strdup(info.filename);
			else
				current->next->word = ft_strdup(info.filename);
			ft_strdel(&info.filename);
		}
		current = current->next;
	}
	return (0);
}

void	add_heredoc_file(t_data *data, char *filename, int id)
{
	t_heredoc_file	*new_file;

	new_file = malloc(sizeof(t_heredoc_file));
	new_file->filename = ft_strdup(filename);
	new_file->id = id;
	new_file->next = data->heredoc_file;
	data->heredoc_file = new_file;
}
