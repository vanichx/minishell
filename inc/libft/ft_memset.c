/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:37:44 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 12:40:40 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)

{
	size_t	i;
	char	*result;

	i = 0;
	result = (char *) b;
	while (i < len)
	{
		result[i] = c;
		i++;
	}
	return (b);
}
