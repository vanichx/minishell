/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:38:01 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 12:40:53 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_words(const char *str, char c)

{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			k++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
	}
	return (k);
}

char	*ft_wdlen(const char *str, char c)

{
	int		i;
	char	*wd;

	i = 0;
	while (*str && *str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	wd = malloc(sizeof(char) * (i + 1));
	if (!wd)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		wd[i] = str[i];
		i++;
	}
	wd[i] = '\0';
	return (wd);
}

void	ft_free(char **ptr, int i)

{
	while (i > 0)
	{
		free(ptr[i - 1]);
		i--;
	}
	free(*ptr);
}

char	**ft_split(const char *s, char c)

{
	int		i;
	int		words;
	char	**pwords;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	pwords = malloc (sizeof(char *) * (words + 1));
	if (pwords == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s && *s == c)
			s++;
		pwords[i] = ft_wdlen(s, c);
		if (pwords == NULL)
			ft_free(pwords, i);
		while (*s && *s != c)
			s++;
		i++;
	}
	pwords[i] = (NULL);
	return (pwords);
}
