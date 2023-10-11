/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:38:42 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 12:41:18 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen2(const char *s2)

{
	int	i;

	i = 0;
	while (*s2++)
		i++;
	return (i);
}

char	*ft_strrchr(const char *s, int c)

{
	int		i;
	char	*s1;

	s1 = (char *) s;
	i = ft_strlen2(s);
	while (i >= 0)
	{
		if (s1[i] == ((char) c))
		{
			return (&s1[i]);
		}
		i--;
	}
	return (0);
}
