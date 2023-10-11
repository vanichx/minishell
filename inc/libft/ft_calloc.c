/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:36:26 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 12:39:24 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)

{
	size_t	i;
	char	*array;

	i = 0;
	array = malloc(count * size);
	if (count * size > SIZE_MAX)
		return (NULL);
	if (array == NULL)
		return (0);
	ft_bzero(array, size * count);
	return (array);
}
