/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:17:44 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/23 17:55:39 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(char *str, int *s_quo, int *d_quo, int i)
{
	if (str[i] == '\'' && *d_quo == 0)
		*s_quo = 1 - *s_quo;
	else if (str[i] == '\"' && *s_quo == 0)
		*d_quo = 1 - *d_quo;
	return (0);
}

static int	handle_un_q(char *str, int *s_quo, int *d_quo, int i, t_data *data)
{
	if ((*s_quo == 1 && str[i] == '\''
			&& i > 0 && str[i - 1] != '\\'
			&& *s_quo % 2 == 0)
		|| (*d_quo == 1 && str[i] == '\"'
			&& i > 0 && str[i - 1] != '\\'
			&& *d_quo % 2 == 0))
	{
		printf("%s%s\n", "minishell: handling of unclosed quotes, ",
			"is not required by subject");
		ft_strdel(&str);
		data->exit_status = 255;
		return (1);
	}
	return (0);
}

static int	handle_rem_q(char *str, int *s_quo, int *d_quo, t_data *data)
{
	if (*s_quo != 0 || *d_quo != 0)
	{
		ft_strdel(&str);
		printf("%s", "minishell: handling of unclosed quotes ");
		printf("%s\n", "is not required by subject");
		data->exit_status = 255;
		return (1);
	}
	return (0);
}

int	odd_quote(char *str, t_data *data)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (str[i])
	{
		check_quotes(str, &s_quotes, &d_quotes, i);
		if (handle_un_q(str, &s_quotes, &d_quotes, i, data))
			return (1);
		i++;
	}
	if (handle_rem_q(str, &s_quotes, &d_quotes, data))
		return (1);
	return (0);
}
