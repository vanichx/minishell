/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:37:34 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 12:40:30 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)

{
	size_t			i;
	unsigned char	*s1_s;
	unsigned char	*s2_s;

	i = 0;
	s1_s = (unsigned char *) s1;
	s2_s = (unsigned char *) s2;
	while (i < n)
	{
		if (s1_s[i] != s2_s[i])
			return (s1_s[i] - s2_s[i]);
		i++;
	}
	return (0);
}
