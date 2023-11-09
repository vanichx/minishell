/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:58:54 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/09 14:47:12 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	find_envir_line(t_envir *env, char *var_name)
// {
// 	int	i;

// 	i = 0;
// 	while (var_name[i])
// 	{
// 		if (ft_strcmp(&env->var_name[i], var_name) == 0)
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

void	print_env_node(t_envir *env_node)
{
    t_envir	*env;
    int		i;

    env = env_node;
    i = 0;
    printf("envir_name: %s, envir_value: %s", env->var_name, env->var_value);
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
