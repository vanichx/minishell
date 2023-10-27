#include "minishell.h"

int	odd_quote(char *str, t_data *data)
{
	char first_q;
	int	i;

	i = 0;
	first_q = first_quote(str);
	if (first_q == '\'' && closed_singlequotes(str))
		data->single_quote = 1;
	else if (first_q == '\"' && closed_doublequotes(str))
		data->double_quote = 1;
	else if (first_q == '\0')
		return (0);
	else 
	{
		write(2, "We should not handle unclosed quotes\n", 37);
		return (1);
	}
	return (0);
}

char first_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (*str);
		str++;
	}
	return (0);
}

int	special_chars(char *str)
{
	int i;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\\' || str[i] == ';') && !in_quotes(str, i))
		{
			printf("minishell: we should not handle `%c'\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int closed_singlequotes(char *str)
{
	int single_quote;

	single_quote = 0;
	while (*str)
	{
		if (*str == '\'')
			single_quote++;
		str++;
	}
	return (single_quote % 2 == 0);
}

int closed_doublequotes(char *str)
{
	int double_quote;

	double_quote = 0;
	while (*str)
	{
		if (*str == '\"')
			double_quote++;
		str++;
	}
	return (double_quote % 2 == 0);
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
