/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:17:14 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 17:41:30 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char** join2darrays(char** str1, char** str2)
{
	int		len1;
	int		len2;
	int		i;
	char	**result;

	if (!str1)
	{
		result = dup_2darray(str2);
		free_2darray(str2);
		return (result);
	}
	len1 = len_2darray(str1);
	len2 = len_2darray(str2);
	i = 0;
	result = (char**)malloc((len1 + len2 + 1) * sizeof(char*));
	if (!result)
		return (NULL);
	while (*str1) 
	{
		result[i] = ft_strdup(*str1);
		if (!result[i])
			free_2darray(result);
		i++;
		str1++;
	}
	while (*str2)
	{
		result[i] = ft_strdup(*str2);
		if (!result[i])
		{
			free_2darray(result);
			return (NULL);
		}
		i++;
		str2++;
	}
	result[i] = NULL;
	str1 -= len1;
	str2 -= len2;
	free_2darray(&str1[0]);
	free_2darray(&str2[0]);
	return (result);
}