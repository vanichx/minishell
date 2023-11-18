#include "minishell.h"

char *expand_dollar_and_join(t_data *data, char *s, int *i, char *result)
{
    char *temp = expand_dollar(data, s, i);
    if (!temp && s[*i + 1])
    {
        temp = ft_substr(s, *i, 1);
        if (temp)
        {
            result = ft_strjoin_double_free(result, temp);
        }
    }
    else if (temp)
    {
        result = ft_strjoin_double_free(result, temp);
    }
    return result;
}

char *expand_quotes(t_data *data, char *s)
{
    int i = -1;
    char *result = NULL;

    while (s[++i])
    {
        if (s[i] == '\"') 
            result = expand_double_quotes(data, s, &i, result);
        else if (s[i] == '\'')
            result = expand_single_quotes(s, &i, result);
        else if (s[i] == '$') 
            result = expand_dollar_and_join(data, s, &i, result);
        else
        {
            char *temp = ft_substr(s, i, 1);
            if (temp)
            {
                result = ft_strjoin_double_free(result, temp);
            }
        }
    }
    return result;
}

char *expand_double_quotes(t_data *data, char *s, int *i, char *result)
{
    while (s[++(*i)] != '\"')
    {
        if (s[*i] == '$') 
            result = expand_dollar_and_join(data, s, i, result);
        else 
        {
            char *temp = ft_substr(s, *i, 1);
            if (temp)
            {
                result = ft_strjoin_double_free(result, temp);
            }
        }
    }
    return result;
}

char *expand_single_quotes(char *s, int *i, char *result)
{
    char *temp = NULL;
    int j = 0;

    while (s[++(*i)] != '\'')
    {
        temp = ft_substr(s, *i, 1);
        if (temp)
        {
            result = ft_strjoin_double_free(result, temp);
            j = ft_strlen(result);
        }
    }
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

    int len = j - *i - 1;
    t_envir *temp = find_envir_variable(data, &s[*i + 1], len);
    if (temp && !ft_strncmp(temp->var_name, &s[*i + 1], len))
	{
		*i = j - 1;
		// printf("IIIIII inside if %d\n", *i);
		return (ft_strdup(temp->var_value));
	}
	else
		*i = j;
    return NULL;
}
