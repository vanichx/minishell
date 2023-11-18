/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:04:28 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/18 04:33:10 by eseferi          ###   ########.fr       */
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

int	check_double_quote(char *s, int *i, int pos)
{
	int double_q;
	int j;

	j = *i + 1;
	double_q = 1;
	while (s[j])
	{
		if (s[j] == '\"')
		{
			double_q = 0;
			if (pos > *i && pos < j)
				return 2;
			else
				break;
		}
		else
			j++;
	}
	*i = j + 1;
	return double_q;
}

int	check_single_quote(char *s, int *i, int pos)
{
	int single_q;
	int j;

	j = *i + 1;
	single_q = 1;
	while (s[j])
	{
		if (s[j] == '\'')
		{
			single_q = 0;
			if (pos > *i && pos < j)
				return 1;
			else
				break;
		}
		else
			j++;
	}
	*i = j + 1;
	return single_q;
}

int	in_quotes(char *s, int pos)
{
	int i = -1;
	int result;

	while (s[++i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			if (s[i] == '\"')
			{
				result = check_double_quote(s, &i, pos);
				if (result != 0)
					return (result);
			}
			else if (s[i] == '\'')
			{
				result = check_single_quote(s, &i, pos);
				if (result != 0)
					return (result);
			}
		}
	}
	return (0);
}
// char *get_quotes(char *input) {
// 	int start = -1;
// 	int end = -1;
// 	int in_quotes = 0;
// 	for (int i = 0; i < (int)strlen(input); i++) {
// 		if (input[i] == '\'' || input[i] == '\"') {
// 			if (in_quotes && start != -1) {
// 				end = i;
// 				break;
// 			} else {
// 				start = i + 1;
// 				in_quotes = 1;
// 			}
// 		}
// 	}
// 	if (start != -1 && end != -1) {
// 		char *result = malloc(end - start + 1);
// 		strncpy(result, &input[start], end - start);
// 		result[end - start] = '\0';
// 		return result;
// 	} else {
// 		return NULL;
// 	}
// }

char *expand_input_line(t_data *data, char *s) {
    int i = -1;
    int j = 0;
    char *result = malloc(sizeof(char) * (ft_strlen(s) + 1));
	char *temp = NULL;
    if (!result)
        return NULL;

    while (s[++i]) {
        if (s[i] == '\"') 
		{
            while (s[++i] && s[i] != '\"')
			{
                if (s[i] == '$') 
				{
                    temp = expand_dollar(data, s, &i);
					if (!temp && s[i + 1])
						result[j++] = s[++i];  // Skip the '$' character
					else if (temp)
					{
						result = ft_strjoin_double_free(result, temp);
						j = ft_strlen(result);
					}
                } 
				else 
				{
                    result[j++] = s[i];
					// printf("%d\n", i);
					// printf("%s\n", result);
					// printf("%d\n", j);
                }
        	}
        }
		else if (s[i] == '\'')
		{
            while (s[++i] != '\'')
                result[j++] = s[i];
        }
		else if (s[i] == '$') 
		{
            temp = expand_dollar(data, s, &i);
            if (!temp)
			{
				if (s[i + 1])
                	result[j++] = s[++i];  // Skip the '$' character
			}
            else 
			{
                result = ft_strjoin_double_free(result, temp);
				j = ft_strlen(result);
            }
        } 
		else
		{
            result[j++] = s[i];
        }
    }
    result[j] = '\0';
    return result;
}

char *expand_dollar(t_data *data, char *s, int *i) {
	if (!s[*i + 1] || s[*i + 1] == '\"')
		return (ft_strdup("$"));
	if (s[*i + 1] == '?') {
		*i += 1;
        return ft_itoa(data->exit_status);
    }
	int j = *i + 1;
    while (is_valid_env_char(s[j]))
        j++;

    int len = j - *i - 1;  // Calculate the length of the variable name
    // Simulate finding the environment variable in data
    // Replace this part with your actual implementation
    t_envir *temp = find_envir_variable(data, &s[*i + 1], len);
    if (temp && !ft_strncmp(temp->var_name, &s[*i + 1], len))
	{
		*i = j - 1;
		printf("%d\n", *i);
		return (ft_strdup(temp->var_value));
	}
	else
		*i = j;
    return NULL;
}

int is_valid_env_char(char c) {
    return isalnum(c) || c == '_';
}











char *handle_dollar_question(t_data *data, char **arg) {
    int i = 0, j = 0, k = 0;
    int in_single_quotes = 0;
    char *check = *arg;
    char *temp = ft_itoa(data->exit_status);
    char *buffer = malloc(sizeof(char) * (ft_strlen(check) + ft_strlen(temp) + 1));

    while(check[i]) {
        if (check[i] == '\'') {
            in_single_quotes = !in_single_quotes;
        }
        if (check[i] == '$' && check[i + 1] != '?' && !in_single_quotes) {
            buffer[j++] = check[i++];
        } else if (check[i] == '$' && check[i + 1] == '?' && !in_single_quotes) {
            k = 0;
            while (temp[k] != '\0') {
                buffer[j++] = temp[k++];
            }
            i += 2;
        } else {
            buffer[j++] = check[i++];
        }
    }
    buffer[j] = '\0';

    free(temp);
    return buffer;
}

int handle_env_var(t_data *data, char *string) {
    int i = 0, j = 0;
    int in_single_quotes = 0;
    t_envir *env_var;
    char *variable_name;

    while (string[i]) {
        if (string[i] == '\'') {
            in_single_quotes = !in_single_quotes;
        }
        if (string[i] == '$' && !in_single_quotes) {
            j = i + 1;
            while (string[j] && (isalnum(string[j]) || string[j] == '_') && !isdigit(string[j])) {
                j++;
            }
            variable_name = ft_substr(string, i + 1, j - i - 1);
            env_var = find_envir_variable(data, variable_name, ft_strlen(variable_name));
            if (!env_var) {
                i = j;
                free(variable_name);
                continue;
            }
            if (env_var && env_var->var_value) {
                if(ft_putstr_fd(env_var->var_value, STDOUT_FILENO)) {
                    return 1;
                }
            }
            free(variable_name);
            i = j;
        } else {
            ft_putchar_fd(string[i], STDOUT_FILENO);
            i++;
        }
    }
    return 0;
}