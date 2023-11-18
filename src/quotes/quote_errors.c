/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:17:44 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/18 16:25:41 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(char *str, int *s_quotes, int *d_quotes, int i)
{
    if (str[i] == '\'' && *d_quotes == 0)
        *s_quotes = 1 - *s_quotes;
    else if (str[i] == '\"' && *s_quotes == 0)
        *d_quotes = 1 - *d_quotes;
    return 0;
}

static int	handle_unclosed_quotes(char *str, int *s_quotes, int *d_quotes, int i, t_data *data)
{
    if ((*s_quotes == 1 && str[i] == '\'' && i > 0 && str[i-1] != '\\' && *s_quotes % 2 == 0) || 
        (*d_quotes == 1 && str[i] == '\"' && i > 0 && str[i-1] != '\\' && *d_quotes % 2 == 0))
    {
        printf("%s%s\n", "minishell: handling of unclosed quotes, ", "is not required by subject");
        ft_strdel(&str);
        data->exit_status = 255;
        return (1);
    }
    return 0;
}

static int	handle_remaining_quotes(char *str, int *s_quotes, int *d_quotes, t_data *data)
{
    if (*s_quotes != 0 || *d_quotes != 0)
    {
        ft_strdel(&str);
        printf("%s\n", "minishell: handling of unclosed quotes is not required by subject");
        data->exit_status = 255;
        return (1);
    }
    return 0;
}

int odd_quote(char *str, t_data *data)
{
    int i;
    int s_quotes;
    int d_quotes;

    i = 0;
    s_quotes = 0;
    d_quotes = 0;
    while (str[i])
    {
        check_quotes(str, &s_quotes, &d_quotes, i);
        if (handle_unclosed_quotes(str, &s_quotes, &d_quotes, i, data))
            return 1;
        i++;
    }
    if (handle_remaining_quotes(str, &s_quotes, &d_quotes, data))
        return 1;
    return 0;
}