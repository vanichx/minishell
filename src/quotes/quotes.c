/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:04:28 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/17 17:05:17 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	odd_quote(char *str, t_data *data)
{
    int		i;
    int		s_quotes;
    int		d_quotes;
    

    i = 0;
    s_quotes = 0;
    d_quotes = 0;
    while (str[i])
    {
        if (str[i] == '\'' && d_quotes == 0)
            s_quotes = 1 - s_quotes; // toggle s_quotes
        else if (str[i] == '\"' && s_quotes == 0)
            d_quotes = 1 - d_quotes; // toggle d_quotes

        if ((s_quotes == 1 && str[i] == '\'' && i > 0 && str[i-1] != '\\' && s_quotes % 2 == 0) || 
            (d_quotes == 1 && str[i] == '\"' && i > 0 && str[i-1] != '\\' && d_quotes % 2 == 0))
        {
            return (printf("%s\n", \
            "minishell: handling of unclosed quotes is not required by subject"), \
			data->exit_status = 255, 1);
        }
        i++;
    }
    if (s_quotes != 0 || d_quotes != 0)
    {
        printf("%s\n", \
        "minishell: handling of unclosed quotes is not required by subject");
        data->exit_status = 255;
        return (1);
    }
    return (0);
}

int	in_quotes(char *s, int pos)
{
    int	s_quotes;
    int	d_quotes;
    int	i;
    int	start_quote_index = -1;

    s_quotes = 0;
    d_quotes = 0;
    i = 0;
    while (i <= pos)
    {
        if (s[i] == 34 && (i == 0 || !is_escaped(s, i - 1))
            && d_quotes % 2 == 0)
        {
            s_quotes++;
            if (s_quotes % 2 != 0) start_quote_index = i;
        }
        if (s[i] == 39 && (i == 0 || d_quotes % 2 != 0 || !is_escaped(s, i - 1))
            && s_quotes % 2 == 0)
        {
            d_quotes++;
            if (d_quotes % 2 != 0) start_quote_index = i;
        }
        i++;
    }
    if ((s_quotes % 2 != 0 || d_quotes % 2 != 0) && (i - start_quote_index > 1))
        return (1);
    return (0);
}

char *get_quotes(char *input) {
	int start = -1;
	int end = -1;
	int in_quotes = 0;
	for (int i = 0; i < strlen(input); i++) {
		if (input[i] == '\'' || input[i] == '\"') {
			if (in_quotes && start != -1) {
				end = i;
				break;
			} else {
				start = i + 1;
				in_quotes = 1;
			}
		}
	}
	if (start != -1 && end != -1) {
		char *result = malloc(end - start + 1);
		strncpy(result, &input[start], end - start);
		result[end - start] = '\0';
		return result;
	} else {
		return NULL;
	}
}