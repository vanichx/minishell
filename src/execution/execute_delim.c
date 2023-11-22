/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_delim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 02:29:39 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/22 17:04:53 by ipetruni         ###   ########.fr       */
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

void	process_heredoc(t_heredoc_info *info, t_data *data)
{
	int		fd;
	char	*buf;

	info->filename = create_temp_filename(info);
	
	fd = open(info->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("minishell: %s\n", strerror(errno));
		return;
	}
	add_heredoc_file(data, info->filename, fd);
	while (1)
	{
		buf = readline("> ");
		if (!buf || !ft_strcmp(info->limiter, buf))
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	if (buf)
		free(buf);
	close(fd);
	info->heredoc_count++;
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
			process_heredoc(&info, data);
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

void add_heredoc_file(t_data *data, char *filename, int id)
{
	t_heredoc_file	*new_file;

	new_file = malloc(sizeof(t_heredoc_file));
	new_file->filename = ft_strdup(filename);
	new_file->id = id;
	new_file->next = data->heredoc_file;
	data->heredoc_file = new_file;
}

void free_heredoc_files(t_heredoc_file *head)
{
    t_heredoc_file *tmp;
	int				ret;
    while (head != NULL)
    {
        tmp = head->next;
		ret = unlink(head->filename);
		if (ret < 0)
			printf("minishell: %s\n", strerror(errno));
        free(head->filename);
        free(head);
		head = tmp;
    }
}
