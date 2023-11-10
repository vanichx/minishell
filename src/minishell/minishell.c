/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:50:43 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/10 16:55:38 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	// int fd;
	// if (read(0, NULL, 0) == -1)
	// 	return (0);
	// if ((fd = dup(0)) == -1)
	// 	return (0);
	// close(fd);
	(void)argc;
	(void)argv;
	init_data(&(data), envp);
	handle_signal();
	start_loop(data);
	free_data(data);
	return (0);
}
