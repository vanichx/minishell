/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:20:21 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/09 15:27:42 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	find_equal_sign(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

t_envir	*fill_env(char **env, t_data *data)
{
	unsigned int	i;
	size_t			len;
	t_envir			*envir;
	t_envir			*head;

	if (!*env)
		return (NULL);
	i = 0;
	len = 0;
	envir = ft_envnew();
	head = envir;
	while (*env)
	{
		i = find_equal_sign(*env);
		len = ft_strlen(*env);
		envir->var_name = ft_substr(*env, 0, i);
		envir->var_value = ft_substr(*env, i + 1, len - i);
		env++;
		if (*env)
		{
			envir->next = ft_envnew();
			envir->next->prev = envir;
			envir = envir->next;
		}
	}
	data->env_list = head;
	return (head);
}

// t_envir *fill_sorted_env(t_envir *sorted_lst, char **env)
// {
// }
