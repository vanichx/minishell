/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 06:40:25 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/25 06:40:45 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_squote(char *s, int *i, char *result)
{
	if (s[*i + 1] == '\'')
	{
		(*i)++;
		result = ft_strdup("");
	}
	else
		result = expand_single_quotes(s, i, result);
	return (result);
}

char	*process_dquote(t_data *data, char *s, int *i, char *result)
{
	if (s[*i + 1] == '\"')
	{
		(*i)++;
		result = ft_strdup("");
	}
	else
		result = expand_double_quotes(data, s, i, result);
	return (result);
}
