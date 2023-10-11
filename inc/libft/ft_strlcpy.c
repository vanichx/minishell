/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:38:25 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 12:41:07 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *str, size_t dstsize)

{
	size_t	len;

	len = 0;
	if (dstsize == 0 && *str)
	{
		while (*str != '\0')
		{
			str++;
			len++;
		}
		return (len);
	}
	while (*(str + len) && --dstsize)
		*dst++ = *(str + len++);
	*dst = '\0';
	while (*(str + len))
		len++;
	return (len);
}
