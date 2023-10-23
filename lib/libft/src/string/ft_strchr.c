/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:45:14 by eseferi           #+#    #+#             */
/*   Updated: 2023/10/23 18:54:29 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s || !c)
		return (NULL);
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c || !c)
		return ((char *)s);
	return (NULL);
}
