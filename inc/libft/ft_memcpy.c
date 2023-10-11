/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:37:37 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 12:40:32 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)

{
	size_t	i;
	char	*char_dst;
	char	*char_src;

	if (dst == src)
		return (dst);
	char_dst = (char *) dst;
	char_src = (char *) src;
	i = 0;
	while (i < n)
	{
		char_dst[i] = char_src[i];
		i++;
	}
	dst = (void *)char_dst;
	src = (void *)char_src;
	return (dst);
}
