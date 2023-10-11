/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:38:09 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 12:40:57 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)

{
	char	*array;
	int		i;

	i = 0;
	array = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!array)
		return (NULL);
	while (*s1)
		array[i++] = *s1++;
	array[i] = '\0';
	return (array);
}
