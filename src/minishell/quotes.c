#include "minishell.h"

int	odd_quote(char *str, int ret_arg)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && (i == 0 || !closed_quote(str, i - 1))\
			&& double_quote % 2 == 0)
			single_quote++;
		if (str[i] == '\'' && (i == 0 || !closed_quote(str, i - 1))\
			&& single_quote % 2 == 0)
			double_quote++;
		i++;
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
		return (1);
	if (ret_arg)
		return (last_pipe(str, i - 1));
	else
		return (0);
}

int	closed_quote(char *str, int pos)
{
	int n;

	n = 0;
	while (pos >= 0 && str[pos] == '\\')
	{
		n++;
		pos--;
	}
	return (n % 2);
}

int	last_pipe(char *str, int pos)
{
	while (pos > 0 && (str[pos] == ' ' || str[pos] == '\n'))
		pos--;
	if (pos > 0 && str[pos] == '|' && !closed_quote(str, pos - 1))
	{
		pos = 0;
		while (str[pos] && (str[pos] != ' ' || str[pos] == '\n'))
			pos++;
		if (str[pos] != '|')
		{
			while (str[pos] && (str[pos] != '|' || !closed_quote(str, pos) ||
				inside_paired_quotes(str, pos)))
				pos++;
			if (!str[pos] && str[pos + 1])
				return (1);
			else
				pos++;
			while (str[pos] && (str[pos] == ' ' || str[pos] == '\n'))
				pos++;
			if (str[pos] != '|')
				return (1);
		}
	}
	return (0);
}

int	inside_paired_quotes(char *str, int pos)
{
	int single_quote;
	int double_quote;
	int i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (i <= pos)
	{
		if (str[i] == '\"' && (i == 0 || !closed_quote(str, i - 1))\
			&& double_quote % 2 == 0)
			single_quote
	++;
		if (str[i] == '\'' && (i == 0 || !closed_quote(str, i - 1))\
			&& single_quote
	 % 2 == 0)
			double_quote++;
		i++;
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
		return (1);
	return (0);
}

void next_quote(t_data *data)
{
	char *tmp;

	data->double_quit = 0;
	tmp = readline("> ");
	
	if (tmp)		
	{
		data->input_line = ft_strjoin_free(data->input_line, "\n");
		data->input_line = ft_strjoin_free(data->input_line, tmp);
		free(tmp);
	}
	if (data->single_quit == 2)
	{
		ft_strdel(&data->input_line);
		data->input_line = ft_strjoin("", "");
		data->single_quit = 1;
	}
}
