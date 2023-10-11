/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:37:41 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 12:40:34 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)

{
	unsigned char	*char_dst;
	unsigned char	*char_src;

	if (dst == src)
		return (dst);
	char_dst = dst;
	char_src = (unsigned char *) src;
	if (dst < src)
	{
		return (ft_memcpy(dst, src, len));
	}
	while (len--)
		char_dst[len] = char_src[len];
	return (dst);
}
