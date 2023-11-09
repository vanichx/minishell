/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:54:40 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/09 15:35:59 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// else
// 	export(&(*data).env_list, "SHLVL", "1");
void	incr_shell_lvl(t_data *data)
{
	int		level;
	t_envir	*envir;

	level = 0;
	envir = find_envir_variable(data, "SHLVL", ft_strlen("SHLVL"));
	if (envir->var_value)
	{
		level = ft_atoi(envir->var_value);
		level++;
		if (level <= 999)
		{
			ft_strdel(&envir->var_value);
			envir->var_value = ft_itoa(level);
		}
		else if (level == 1000)
		{
			ft_strdel(&envir->var_value);
			envir->var_value = ft_strdup("");
		}
		else
		{
			level = 1;
			ft_strdel(&envir->var_value);
			envir->var_value = ft_strdup("1");
		}
	}
}

// void	export(t_data **data, char *var_name, char *var_value)
// {
// 	t_envir	*new_envir;

// 	new_envir = (t_envir *)malloc(sizeof(t_envir));
// 	if (!new_envir)
// 		return ;
// 	new_envir->var_name = ft_strdup(var_name);
// 	new_envir->var_value = ft_strdup(var_value);
// 	new_envir->count = ft_strlen(var_value);
// 	new_envir->next = NULL;
// 	new_envir->prev = NULL;
// 	if (*env_list)
// 	{
// 		t_envir *last_envir = *env_list;
// 		while (last_envir->next)
// 			last_envir = last_envir->next;
// 		last_envir->next = new_envir;
// 		new_envir->prev = last_envir;
// 	}
// 	else
// 		*env_list = new_envir;
// }