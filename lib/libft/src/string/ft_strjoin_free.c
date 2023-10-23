/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:29:35 by eseferi           #+#    #+#             */
/*   Updated: 2023/10/23 14:00:39 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;

	if (!s2)
	{
		str = ft_strdup(s1);
		free((void*)s1);
		return (str);
	}
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
		+ 1))))
		return (NULL);
	ft_strcpy(str, s1);
	free((void*)s1);
	ft_strcat(str, s2);
	return (str);
}
