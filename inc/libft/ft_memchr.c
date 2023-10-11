/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:37:30 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 12:40:28 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)

{
	size_t	i;
	char	*s2;
	char	letter;

	letter = c;
	i = 0;
	s2 = (char *) s;
	while (i < n)
	{
		if (s2[i] == letter)
		{
			return (&(s2[i]));
		}
		i++;
	}
	return (NULL);
}
