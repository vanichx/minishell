/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:58:54 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/09 17:22:40 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_node(t_envir *env_node)
{
    t_envir	*env;
    int		i;

	if (!env_node)
		return ;
    env = env_node;
    i = 0;
    printf("%s=%s\n", env->var_name, env->var_value);
}

void	print_env_node_sorted(t_envir *env_node)
{
    t_envir	*env;
    int		i;

	if (!env_node)
		return ;
    env = env_node;
    i = 0;
    printf("declare -x %s=%s\n", env->var_name, env->var_value);
}

void	free_envir_array(char **env_array)
{
	int	i;

	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
	env_array = NULL;
}
