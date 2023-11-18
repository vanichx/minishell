/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_double_free.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 02:03:07 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/18 02:04:20 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin_double_free(char *s1, char *s2)
{
    size_t len1;
    size_t len2;

    if (!s1 || !s2)
        return NULL;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
    char *result = malloc(sizeof(char) * (len1 + len2 + 1));
    if (!result)
        return NULL;

    ft_memcpy(result, s1, len1);
    ft_memcpy(result + len1, s2, len2 + 1);

    // Free the input strings
    free(s1);
    free(s2);

    return result;
}