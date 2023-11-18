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
	*i = j;
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
	*i = j;
	return single_q;
}

int	in_quotes(char *s, int pos)
{
	int i = 0;
	int result;

	while (s[i] != '\0')
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
		i++;
	}
	return (0);
}

char *expand_quotes(t_data *data, char *s) {
    int i = -1;
    int j = 0;
    char *result = NULL;
	char *temp = NULL;

    while (s[++i])
	{
        if (s[i] == '\"') 
		{
            while (s[++i] != '\"')
			{
                if (s[i] == '$') 
				{
                    temp = expand_dollar(data, s, &i);
					if (!temp && s[i + 1])
					{
						temp = ft_substr(s, i, 1);
						if (temp)
						{
							result = ft_strjoin_double_free(result, temp);
							j = ft_strlen(result);
						}
					}
					else if (temp)
					{
						result = ft_strjoin_double_free(result, temp);
						j = ft_strlen(result);
					}
                } 
				else 
				{
					temp = ft_substr(s, i, 1);
					printf("%d , %s\n", i, temp);
					if (temp)
					{
						result = ft_strjoin_double_free(result, temp);
                   		j = ft_strlen(result);
					}
				}
        	}
        }
		else if (s[i] == '\'')
		{
            while (s[++i] != '\'')
            {
				temp = ft_substr(s, i, 1);
				if (temp)
				{
					result = ft_strjoin_double_free(result, temp);
					j = ft_strlen(result);
				}
			}
        }
		else if (s[i] == '$') 
		{
            temp = expand_dollar(data, s, &i);
            if (!temp)
			{
				if (s[i + 1])
                {
					temp = ft_substr(s, i, 1);
					if (temp)
					{
						result = ft_strjoin_double_free(result, temp);
                   		j = ft_strlen(result);
					}
				}
			}
            else 
			{
                result = ft_strjoin_double_free(result, temp);
				j = ft_strlen(result);
            }
        } 
		else
        {
			temp = ft_substr(s, i, 1);
			if (temp)
			{
				result = ft_strjoin_double_free(result, temp);
				j = ft_strlen(result);
			}
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

int is_valid_env_char(char c) {
    return isalnum(c) || c == '_';
}

void	find_quotes(char **str, t_data *data)
{
	char *temp;

	temp = NULL;
	while (*str)
	{
		if (has_quotes(*str) || has_dollar(*str))
		{
			temp = expand_quotes(data, *str);
			if (!temp)
				return ;
			ft_strdel(&(*str));
			*str = ft_strdup(temp);
			ft_strdel(&temp);
		}
		str++;
	}
}

int has_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\"' ||*str == '\'')
			return (1);
		str++;
	}
	return (0);
}

int has_dollar(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (1);
		str++;
	}
	return (0);
}