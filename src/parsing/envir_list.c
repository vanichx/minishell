/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:20:21 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/09 14:52:39 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




unsigned int	find_equal_sign(char *str)
{
	unsigned int i;

	i = 0;

	while (str[i] != '=')
		i++;
	return(i);
}

t_envir	*fill_env(char **env, t_data *data)
{
	unsigned int	j;
	size_t			len;
	t_envir			*envir;

	envir = NULL;
	if (!*env)
		return (NULL);
	j = 0;
	len = 0;
	while (*env)
	{
		envir = ft_envnew();
		j = find_equal_sign(*env);
		len = ft_strlen(*env);
		envir->var_name = ft_substr(*env, 0, j);
		envir->var_value = ft_substr(*env, j + 1, len - j);
		env++;
		envir = envir->next;
	}
	ft_enviter(envir, print_env_node);
	printf("hello from ivan\n");
	return (envir);
}




// t_envir *fill_sorted_env(t_envir *sorted_lst, char **env)
// {
	
// }
