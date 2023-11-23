/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:17:14 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 15:29:52 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dup_and_free_if_null(char **str1, char **str2)
{
	char	**result;

	if (!str1)
	{
		result = dup_2darray(str2);
		free_2darray(str2);
		return (result);
	}
	return (NULL);
}

char	**allocate_result_array(char **str1, char **str2)
{
	int		len1;
	int		len2;

	len1 = len_2darray(str1);
	len2 = len_2darray(str2);
	return ((char **) malloc((len1 + len2 + 1) * sizeof(char *)));
}

void	copy_2darray_to_result(char **src, char **result, int *index)
{
	while (*src)
	{
		result[*index] = ft_strdup(*src);
		if (!result[*index])
		{
			free_2darray(result);
			return ;
		}
		(*index)++;
		src++;
	}
}

void	free_original_2darrays(char **str1, char **str2, int len1, int len2)
{
	str1 -= len1;
	str2 -= len2;
	free_2darray(&str1[0]);
	free_2darray(&str2[0]);
}

char	**join2darrays(char **str1, char **str2)
{
	int		i;
	char	**result;
	int		len1;
	int		len2;

	result = dup_and_free_if_null(str1, str2);
	if (result)
		return (result);
	result = allocate_result_array(str1, str2);
	if (!result)
		return (NULL);
	i = 0;
	copy_2darray_to_result(str1, result, &i);
	copy_2darray_to_result(str2, result, &i);
	result[i] = NULL;
	len1 = len_2darray(str1);
	len2 = len_2darray(str2);
	free_original_2darrays(str1, str2, len1, len2);
	return (result);
}
