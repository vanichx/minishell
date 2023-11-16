/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:04:28 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/16 21:02:32 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	odd_quote(char *str)
{
	int		i;
	int		s_quotes;
	int		d_quotes;
	

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && d_quotes % 2 == 0)
			s_quotes++;
		else if (str[i] == '\"' && s_quotes % 2 == 0)
			d_quotes++;
		i++;
	}
	if (s_quotes % 2 != 0 || d_quotes % 2 != 0)
	{
		printf("%s\n", \
		"minishell: handling of unclosed quotes is not required by subject");
		// data->exit_status = 1;
		return (1);
	}
	return (0);
}

int	in_quotes(char *s, int pos)
{
	int	s_quotes;
	int	d_qoutes;
	int	i;

	s_quotes = 0;
	d_qoutes = 0;
	i = 0;
	while (i <= pos)
	{
		if (s[i] == 34 && (i == 0 || !is_escaped(s, i - 1))
			&& d_qoutes % 2 == 0)
			s_quotes++;
		if (s[i] == 39 && (i == 0 || d_qoutes % 2 != 0 || !is_escaped(s, i - 1))
			&& s_quotes % 2 == 0)
			d_qoutes++;
		i++;
	}
	if (s_quotes % 2 != 0 || d_qoutes % 2 != 0)
		return (1);
	return (0);
}

// int	last_pipe(char *str, int pos)
// {
// 	while (pos > 0 && (str[pos] == ' ' || str[pos] == '\n'))
// 		pos--;
// 	if (pos > 0 && str[pos] == '|' && !special_chars(str))
// 	{
// 		pos = 0;
// 		while (str[pos] && (str[pos] != ' ' || str[pos] == '\n'))
// 			pos++;
// 		if (str[pos] != '|')
// 		{
// 			while (str[pos] && (str[pos] != '|' || !special_chars(str) ||
// 				inside_paired_quotes(str, pos)))
// 				pos++;
// 			if (!str[pos] && str[pos + 1])
// 				return (1);
// 			else
// 				pos++;
// 			while (str[pos] && (str[pos] == ' ' || str[pos] == '\n'))
// 				pos++;
// 			if (str[pos] != '|')
// 				return (1);
// 		}
// 	}
// 	return (0);
// }
