/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:38:05 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 12:40:55 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)

{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != ((char) c))
		i++;
	if (s[i] == ((char) c))
		return ((char *)s + i);
	return (NULL);
}
