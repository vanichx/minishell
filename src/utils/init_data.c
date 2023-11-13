/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:33:01 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/13 18:19:35 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_enviter((*data)->env, print_env_node);
void	init_data(t_data **data, char **envp)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	(*data)->env_list = NULL;
	(*data)->sorted_env_list = NULL;
	(*data)->token_list = NULL;
	(*data)->input_line = NULL;
	(*data)->tree = NULL;
	(*data)->exit_status = 0;
	(*data)->input_minishell = "minishell>> ";
	(*data)->pid = getpid();
	(*data)->curr_dir = getcwd(NULL, 0);
	fill_env(envp, *data);
	incr_shell_lvl(*data);
	// (*data)->sorted_env_list = copy_and_sort_envir_list((*data)->env_list);
	// ft_enviter((*data)->sorted_env_list, print_env_node_sorted);
}
