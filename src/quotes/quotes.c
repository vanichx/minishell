/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:04:28 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/17 17:24:28 by eseferi          ###   ########.fr       */
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
	for (int i = 0; i < (int)strlen(input); i++) {
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

char *expand_input_line(t_data *data, char *input) {
    char *result = get_quotes(input);
    for (int i = 0; result[i]; i++) {
        if (result[i] == '$' && (i == 0 || result[i-1] != '\'')) {
            int var_start = i + 1;
            int var_length = 0;
            while (result[var_start + var_length] && result[var_start + var_length] != ' ') {
                var_length++;
            }
            char *var_name = malloc(var_length + 1);
            strncpy(var_name, &result[var_start], var_length);
            var_name[var_length] = '\0';
            char *var_value;
            if (strcmp(var_name, "?") == 0) {
                var_value = malloc(12); // Enough to hold all int values
                sprintf(var_value, "%ld", data->exit_status);
            } else {
                t_envir *var_node = find_envir_variable(data, var_name, var_length);
                var_value = var_node ? strdup(var_node->var_value) : NULL;
            }
            free(var_name);
            if (var_value) {
                char *new_result = malloc(strlen(result) - var_length + strlen(var_value) + 1);
                strncpy(new_result, result, i);
                strcpy(&new_result[i], var_value);
                strcpy(&new_result[i + strlen(var_value)], &result[var_start + var_length]);
                free(result);
                result = new_result;
                free(var_value);
            }
        }
    }
    return result;
}