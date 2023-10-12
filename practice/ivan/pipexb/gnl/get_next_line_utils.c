/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:25:52 by ipetruni          #+#    #+#             */
/*   Updated: 2023/09/25 16:57:27 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	if (s && s[i] == '\n')
		i++;
	return (i);
}

int	find_new_line(char *str)
{
	if (str)
	{
		while (*str)
		{
			if (*str == '\n')
				return (1);
			str++;
		}
	}
	return (0);
}

char	*str_join(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	if (s1)
		while (s1[++i])
			s3[i] = s1[i];
	else
		i = 0;
	if (s2)
		while (s2[++j])
			s3[i + j] = s2[j];
	else
		j = 0;
	s3[i + j] = '\0';
	if (s1)
		free(s1);
	return (s3);
}

char	*trim_rem(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	i++;
	while (str[i + j] != '\0')
	{
		str[j] = str[i + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_line(char *str)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	new_line = (char *)malloc(i + 1);
	if (!new_line)
		return (0);
	while (str[j] != '\n' && str[j] != '\0')
	{
		new_line[j] = str[j];
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}
